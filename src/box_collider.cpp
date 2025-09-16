//
// Created by michiel on 8/28/25.
//
#include <engine/box_collider.h>

#include <engine/transform.h>
#include <engine/component_factory.h>
#include <engine/sol.h>
#include <engine/camera.h>
#include <engine/math/math.h>

namespace engine {
	std::vector<BoxCollider *> BoxCollider::boxColliders {};

	const float BoxCollider::LOD_THRESHOLD = 20;

	const math::vec3 BoxCollider::DEFAULT_SIZE = math::vec3const::one;
	const math::vec3 BoxCollider::DEFAULT_OFFSET = math::vec3const::zero;
	const bool BoxCollider::DEFAULT_IS_TRIGGER = false;
	
	BoxCollider::BoxCollider(math::vec3 size, math::vec3 offset, bool isTrigger)
			: size(size), offset(offset), isTrigger(isTrigger)
	{
		boxColliders.push_back(this);
	}
	
	Component *BoxCollider::create(const std::vector<std::string> args)
	{
		auto size = DEFAULT_SIZE;
		auto offset = DEFAULT_OFFSET;
		bool isTrigger = DEFAULT_IS_TRIGGER;

		if (args.size() >= 1)
			size = math::strv3(args[0]);
		if (args.size() >= 2)
			offset = math::strv3(args[1]);
		if (args.size() >= 3)
			isTrigger = SOL::parseBool(args[2]);

		return new BoxCollider(size, offset, isTrigger);
	}
	
	bool BoxCollider::registered = [] {
		ComponentFactory::registerType("boxcollider", &BoxCollider::create);
		return true;
	}();
	
	
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
		float squareSize = std::max(std::max(globalSize.x, globalSize.y), globalSize.z);
		minAABB = center - globalSize / 2.f;
		maxAABB = center + globalSize / 2.f;
		doubledMinAABB = center - squareSize;
		doubledMaxAABB = center + squareSize;
		
		auto forwards = math::vec3(sin(math::radians(transform->globalRotation().y)) *
										 cos(math::radians(transform->globalRotation().x)),
										 sin(math::radians(transform->globalRotation().x)),
										 -cos(math::radians(transform->globalRotation().y)) *
										 cos(math::radians(transform->globalRotation().x)));

		forwards.normalize();
		
		math::vec3 right = math::vec3::cross(forwards, math::vec3(0, 1, 0)).normalized();
		math::vec3 up = math::vec3::cross(right, forwards).normalized();
		
		obbInfo.axisX = right;
		obbInfo.axisY = up;
		obbInfo.axisZ = forwards;
		obbInfo.halfSize = globalSize / 2.f;
	}
	
	void BoxCollider::resolveCollisions()
	{
		if (requireComponent(rigidbody, true) == nullptr)
			return;
		
		for (auto &other : boxColliders)
		{
			if (other == this) continue;
			
			float distToCamera = math::distance(Camera::get_main()->transform.globalPosition(),
												transform->globalPosition());
			CollisionInfo info = collisionMode == Simple || distToCamera > LOD_THRESHOLD
												  ? collidesWithAABB(other)
												  : collidesWithOBB(other);
			
			if (info.collided)
			{
				if (math::vec3const::up == info.normal.abs())
				{
				// ReSharper disable CppDFAUnreachableCode
					rigidbody->setVelocity(0);
				}

				rigidbody->translate(info.depth, info.normal);
			}
		}
	}
	
	CollisionInfo BoxCollider::collidesWithAABB(BoxCollider *&other)
	{
		math::vec3 axes[]
				{
						math::vec3(0, 1, 0),
						math::vec3(1, 0, 0),
						math::vec3(0, 0, 1),
				};
		
		
		bool collided = true;
		float minOverlap = std::numeric_limits<float>::max();
		math::vec3 minAxis;
		
		for (math::vec3 &axis : axes)
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
				minAxis = axis.normalized();
			}
		}
		
		if (collided && math::dot(minAxis, other->center - center) > 0)
			minAxis = minAxis *= -1;
		
		
		return CollisionInfo {collided, this, other, minAxis, minOverlap};
	}
	
	CollisionInfo BoxCollider::collidesWithOBB(BoxCollider *&other)
	{
		if (!(doubledMinAABB.x < other->doubledMaxAABB.x &&
			  doubledMaxAABB.x > other->doubledMinAABB.x
			  && doubledMinAABB.y < other->doubledMaxAABB.y &&
			  doubledMaxAABB.y > other->doubledMinAABB.y
			  && doubledMinAABB.z < other->doubledMaxAABB.z &&
			  doubledMaxAABB.z > other->doubledMinAABB.z))
		{
			return CollisionInfo {false, this, other};
		}
		
		bool collided = true;
		float minOverlap = std::numeric_limits<float>::max();
		math::vec3 minAxis;
		
		math::vec3 axes[] {
				obbInfo.axisX,
				obbInfo.axisY,
				obbInfo.axisZ,
				other->obbInfo.axisX,
				other->obbInfo.axisY,
				other->obbInfo.axisZ,
				math::cross(obbInfo.axisX, other->obbInfo.axisX),
				math::cross(obbInfo.axisX, other->obbInfo.axisY),
				math::cross(obbInfo.axisX, other->obbInfo.axisZ),
				math::cross(obbInfo.axisY, other->obbInfo.axisX),
				math::cross(obbInfo.axisY, other->obbInfo.axisY),
				math::cross(obbInfo.axisY, other->obbInfo.axisZ),
				math::cross(obbInfo.axisZ, other->obbInfo.axisX),
				math::cross(obbInfo.axisZ, other->obbInfo.axisY),
				math::cross(obbInfo.axisZ, other->obbInfo.axisZ),
		};
		
		
		for (math::vec3 &axis : axes)
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
				minAxis = axis.normalized();
			}
		}
		
		if (collided && math::dot(minAxis, other->center - center) > 0)
			minAxis = -minAxis;
		
		
		return CollisionInfo {collided, this, other, minAxis, minOverlap};
	}
	
	float BoxCollider::checkOverlapOnPlane(math::vec3 plane, BoxCollider *&other) const
	{
		// checks if the boxes are overlapping on a certain plain
		
		math::vec3 direction = other->center - center;
		
		if (plane.magnitude() < 1e-6f)
			return std::numeric_limits<float>::max(); // skip axis
		
		plane.normalize();
		
		float projection = std::fabs(math::dot(direction, plane));
		
		float radiusThis = abs(math::dot(obbInfo.axisX * obbInfo.halfSize.x, plane)) +
						   abs(math::dot(obbInfo.axisY * obbInfo.halfSize.y, plane)) +
						   abs(math::dot(obbInfo.axisZ * obbInfo.halfSize.z, plane));
		
		float radiusOther = abs(math::dot(other->obbInfo.axisX * other->obbInfo.halfSize.x, plane)) +
							abs(math::dot(other->obbInfo.axisY * other->obbInfo.halfSize.y, plane)) +
							abs(math::dot(other->obbInfo.axisZ * other->obbInfo.halfSize.z, plane));
		
		float overlap = (radiusThis + radiusOther) - projection;
		
		if (overlap > 0)
			return overlap;


		return -1;
	}
}
