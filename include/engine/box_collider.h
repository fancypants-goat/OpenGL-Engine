//
// Created by michiel on 8/28/25.
//

#ifndef ENGINE_BOX_COLLIDER_H
#define ENGINE_BOX_COLLIDER_H

#include <vector>
#include <engine/math/math.h>
#include "component.h"
#include "rigidbody.h"

namespace engine {
	struct CollisionInfo; // little forwards cast cus BoxCollider uses CollisionInfo :D
	
	
	struct OBBInfo
	{
		math::vec3 axisX;
		math::vec3 axisY;
		math::vec3 axisZ;
		math::vec3 halfSize;
	};
	
	
	class BoxCollider : public Component
	{
	public:
		enum CollisionMode
		{
			Simple,
			Advanced
		};


		explicit BoxCollider(math::vec3 size = DEFAULT_SIZE, math::vec3 offset = DEFAULT_OFFSET, bool isTrigger = DEFAULT_IS_TRIGGER);
		
		static Component *create(std::vector<std::string> args);
		static bool registered;
		
		void update(GLFWwindow *window) override;
		
		void calculateBounds();
		
		void resolveCollisions();
		CollisionInfo collidesWithFirst();
		std::vector<CollisionInfo> collidesWithAny();
		CollisionInfo collidesWithAABB(BoxCollider *&other);
		CollisionInfo collidesWithOBB(BoxCollider *&other);

		math::vec3 size;
		math::vec3 offset;
		math::vec3 globalSize;
		math::vec3 center;

		CollisionMode collisionMode = Advanced;
		
		bool isTrigger;
		
		Rigidbody *rigidbody { nullptr };
	private:
		float checkOverlapOnPlane(math::vec3 plane, BoxCollider *&other) const;

		math::vec3 minAABB;
		math::vec3 maxAABB;
		math::vec3 doubledMinAABB;
		math::vec3 doubledMaxAABB;

		OBBInfo obbInfo;
		
		static std::vector<BoxCollider *> boxColliders;

		static const float LOD_THRESHOLD;

		static const math::vec3 DEFAULT_SIZE;
		static const math::vec3 DEFAULT_OFFSET;
		static const bool DEFAULT_IS_TRIGGER;
	};
	
	struct CollisionInfo
	{
		bool collided = false;
		BoxCollider *a;
		BoxCollider *b;
		math::vec3 normal;
		float depth;
	};
}

#endif //ENGINE_BOX_COLLIDER_H
