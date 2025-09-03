//
// Created by michiel on 8/28/25.
//
#include <engine/box_collider.h>
#include <engine/transform.h>
#include <engine/component_factory.h>
#include <engine/sol.h>

namespace engine {
	std::vector<BoxCollider *> BoxCollider::boxColliders {};
	
	glm::vec3 	BoxCollider::DEFAULT_SIZE		= glm::vec3(1);
	glm::vec3 	BoxCollider::DEFAULT_OFFSET		= glm::vec3(0);
	bool 		BoxCollider::DEFAULT_IS_TRIGGER	= false;
	
	Component *BoxCollider::create(const std::vector<std::string> args)
	{
		glm::vec3 size = DEFAULT_SIZE;
		glm::vec3 offset = DEFAULT_OFFSET;
		bool isTrigger = DEFAULT_IS_TRIGGER;
		
		if (args.size() >= 1) // size argument
			size = SOL::parseVec3(args[0]);
		if (args.size() >= 2) // offset argument
			offset = SOL::parseVec3(args[1]);
		if (args.size() >= 3) // isTrigger argument
			isTrigger = SOL::parseBool(args[2]);
		
		return new BoxCollider(size, offset, isTrigger);
	}
	
	bool BoxCollider::registered = [] {
		ComponentFactory::registerType("boxcollider", &BoxCollider::create);
		return true;
	}();
	
	
	
	BoxCollider::BoxCollider(glm::vec3 size, glm::vec3 offset, bool isTrigger)
			: size(size), offset(offset), isTrigger(isTrigger)
	{
		boxColliders.push_back(this);
	}
	
	
	void BoxCollider::update(GLFWwindow *window)
	{
		calculateBounds();
		
		if (!isTrigger)
			resolveCollisions();
	}
	
	void BoxCollider::calculateBounds()
	{
		if (transform == nullptr) return;
		
		globalSize = transform->globalSize() * size;
		center = transform->globalPosition() + offset;
		
		// AABB
		// don't use halfsize
		// if halfsize would be used, the rotated box could stick out with the corners, causing 'hacky' results
		minAABB = center - globalSize;
		maxAABB = center + globalSize;
		
		// OBB
		glm::vec3 worldUp(0, 1, 0);
		
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
		obbInfo.halfSize = globalSize * 0.5f;
	}
	
	void BoxCollider::resolveCollisions()
	{
		if (requireComponent(rigidbody, true) == nullptr)
			return;
		
		for (auto &other : boxColliders)
		{
			if (other == this) continue;
			
			if (collidesWithAABB(other))
			{
				CollisionInfo obbCollision = collidesWithOBB(other);
				if (obbCollision.collided)
				{
					if (glm::vec3(0,1,0) == glm::abs(obbCollision.normal))
						rigidbody->setVelocity(0);
					
					rigidbody->translate(obbCollision.depth, obbCollision.normal);
				}
			}
		}
	}
	
	bool BoxCollider::collidesWithAABB(BoxCollider *&other) const
	{
		bool collided = (minAABB.x < other->maxAABB.x && maxAABB.x > other->minAABB.x
						 && minAABB.y < other->maxAABB.y && maxAABB.y > other->minAABB.y
						 && minAABB.z < other->maxAABB.z && maxAABB.z > other->minAABB.z);
		
		return collided;
	}
	
	CollisionInfo BoxCollider::collidesWithOBB(BoxCollider *&other)
	{
		bool collided = true;
		float minOverlap = std::numeric_limits<float>::max();
		glm::vec3 minAxis;
		
		const std::vector<glm::vec3> axes {
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
		
		
		for (const glm::vec3 &axis : axes)
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
		
		
		return CollisionInfo {.collided=collided, .a=this, .b=other, .normal=minAxis, .depth=minOverlap};
	}
	
	float BoxCollider::checkOverlapOnPlane(glm::vec3 plane, BoxCollider *&other)
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
