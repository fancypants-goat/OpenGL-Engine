//
// Created by michiel on 8/28/25.
//
#include <engine/box_collider.h>
#include <engine/transform.h>
#include <engine/component_factory.h>
#include <engine/sol.h>
#include <engine/camera.h>

namespace engine
{
    float BoxCollider::LOD_THRESHOLD = 20;
    std::vector<BoxCollider*> BoxCollider::boxColliders{};

    BoxCollider::BoxCollider(glm::vec3 size, glm::vec3 offset)
        : size(size), offset(offset)
    {
        boxColliders.push_back(this);
    }

    Component* BoxCollider::create(const std::vector<std::string> args)
    {
        glm::vec3 size = SOL::parseVec3(args[0]);
        glm::vec3 offset = SOL::parseVec3(args[1]);
        return new BoxCollider(size, offset);
    }

    bool BoxCollider::registered = []
    {
        ComponentFactory::registerType("boxcollider", &BoxCollider::create);
        return true;
    }();


    void BoxCollider::update(GLFWwindow* window)
    {
        calculateBounds();
    }

    void BoxCollider::calculateBounds()
    {
        if (transform == nullptr) return;

        globalSize = transform->globalSize() * size;
        center = transform->globalPosition() + offset;
        float squareSize = std::max(std::max(globalSize.x, globalSize.y), globalSize.z);
        minAABB = center - globalSize / 2.f;
        maxAABB = center + globalSize / 2.f;
        doubledMinAABB = center - squareSize;
        doubledMaxAABB = center + squareSize;


        const glm::vec3 worldUp(0, 1, 0);

        glm::vec3 forwards = glm::vec3(sin(glm::radians(transform->globalRotation().y)) *
                                       cos(glm::radians(transform->globalRotation().x)),
                                       sin(glm::radians(transform->globalRotation().x)),
                                       -cos(glm::radians(transform->globalRotation().y)) *
                                       cos(glm::radians(transform->globalRotation().x)));

        forwards = glm::normalize(forwards);

        glm::vec3 right = glm::normalize(glm::cross(forwards, worldUp));
        glm::vec3 up = glm::normalize(glm::cross(right, forwards));

        obbInfo.axisX = right;
        obbInfo.axisY = up;
        obbInfo.axisZ = forwards;
        obbInfo.halfSize = globalSize / 2.f;
    }

    void BoxCollider::resolveCollisions()
    {
        if (requireComponent(rigidbody, true) == nullptr)
            return;

        for (auto& other : boxColliders)
        {
            if (other == this) continue;

            CollisionInfo info;
            if (collisionMode == Simple || glm::distance(
                Camera::get_main()->transform.globalPosition(),
                transform->globalPosition()) > LOD_THRESHOLD)
                info = collidesWithOBB(other);
            else if (collisionMode == Advanced)
                info = collidesWithOBB(other);

            if (info.collided)
            {
                if (glm::vec3(0, 1, 0) == info.normal)
                    rigidbody->setVelocity(0);

                rigidbody->translate(info.depth, info.normal);
            }
        }
    }

    CollisionInfo BoxCollider::collidesWithAABB(BoxCollider*& other)
    {
        glm::vec3 axes[]
        {
            glm::vec3(1, 0, 0),
            glm::vec3(0, 1, 0),
            glm::vec3(0, 0, 1),
        };


        bool collided = true;
        float minOverlap = std::numeric_limits<float>::max();
        glm::vec3 minAxis;

        for (glm::vec3& axis : axes)
        {
            float dist = checkOverlapOnPlane(axis, other);
            if (-1 == dist)
            {
                collided = false;
                break;
            }

            if (dist < minOverlap)
            {
                minOverlap = dist;
                minAxis = glm::normalize(axis);
            }
        }

        if (collided && glm::dot(minAxis, other->center - center) > 0)
            minAxis = -minAxis;


        return CollisionInfo{collided, this, other, minAxis, minOverlap};
    }

    CollisionInfo BoxCollider::collidesWithOBB(BoxCollider*& other)
    {
        if (!(doubledMinAABB.x < other->doubledMaxAABB.x && doubledMaxAABB.x > other->doubledMinAABB.x
            && doubledMinAABB.y < other->doubledMaxAABB.y && doubledMaxAABB.y > other->doubledMinAABB.y
            && doubledMinAABB.z < other->doubledMaxAABB.z && doubledMaxAABB.z > other->doubledMinAABB.z))
        {
            return CollisionInfo{false, this, other};
        }

        bool collided = true;
        float minOverlap = std::numeric_limits<float>::max();
        glm::vec3 minAxis;

        glm::vec3 axes[]{
            obbInfo.axisX,
            obbInfo.axisY,
            obbInfo.axisZ,
            other->obbInfo.axisX,
            other->obbInfo.axisY,
            other->obbInfo.axisZ,
            glm::cross(obbInfo.axisX, other->obbInfo.axisX),
            glm::cross(obbInfo.axisX, other->obbInfo.axisY),
            glm::cross(obbInfo.axisX, other->obbInfo.axisZ),
            glm::cross(obbInfo.axisY, other->obbInfo.axisX),
            glm::cross(obbInfo.axisY, other->obbInfo.axisY),
            glm::cross(obbInfo.axisY, other->obbInfo.axisZ),
            glm::cross(obbInfo.axisZ, other->obbInfo.axisX),
            glm::cross(obbInfo.axisZ, other->obbInfo.axisY),
            glm::cross(obbInfo.axisZ, other->obbInfo.axisZ),
        };


        for (glm::vec3& axis : axes)
        {
            float dist = checkOverlapOnPlane(axis, other);
            if (-1 == dist)
            {
                collided = false;
                break;
            }

            if (dist < minOverlap)
            {
                minOverlap = dist;
                minAxis = glm::normalize(axis);
            }
        }

        if (collided && glm::dot(minAxis, other->center - center) > 0)
            minAxis = -minAxis;


        return CollisionInfo{collided, this, other, minAxis, minOverlap};
    }

    float BoxCollider::checkOverlapOnPlane(glm::vec3 plane, BoxCollider*& other) const
    {
        // checks if the boxes are overlapping on a certain plain

        glm::vec3 direction = other->center - center;

        if (glm::length(plane) < 1e-6f)
            return std::numeric_limits<float>::max(); // skip axis

        plane = glm::normalize(plane);

        float projection = std::fabs(glm::dot(direction, plane));

        float radiusThis = abs(glm::dot(obbInfo.axisX * obbInfo.halfSize.x, plane)) +
            abs(glm::dot(obbInfo.axisY * obbInfo.halfSize.y, plane)) +
            abs(glm::dot(obbInfo.axisZ * obbInfo.halfSize.z, plane));

        float radiusOther = abs(glm::dot(other->obbInfo.axisX * other->obbInfo.halfSize.x, plane)) +
            abs(glm::dot(other->obbInfo.axisY * other->obbInfo.halfSize.y, plane)) +
            abs(glm::dot(other->obbInfo.axisZ * other->obbInfo.halfSize.z, plane));

        float overlap = (radiusThis + radiusOther) - projection;

        if (overlap > 0)
            return overlap;
        else
            return -1;
    }
}
