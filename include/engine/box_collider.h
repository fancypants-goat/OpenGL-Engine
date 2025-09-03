//
// Created by michiel on 8/28/25.
//

#ifndef ENGINE_BOX_COLLIDER_H
#define ENGINE_BOX_COLLIDER_H

#include <glm/glm.hpp>
#include <vector>
#include "component.h"
#include "rigidbody.h"

namespace engine {
	struct CollisionInfo; // little forwards cast cus BoxCollider uses CollisionInfo :D
	
	
	struct OBBInfo
	{
		glm::vec3 axisX = glm::vec3(1, 0, 0);
		glm::vec3 axisY = glm::vec3(0, 1, 0);
		glm::vec3 axisZ = glm::vec3(0, 0, 1);
		glm::vec3 halfSize = glm::vec3(0);
	};
	
	
	class BoxCollider : public Component
	{
	public:
		
		explicit BoxCollider(glm::vec3 size = DEFAULT_SIZE, glm::vec3 offset = DEFAULT_OFFSET, bool isTrigger = DEFAULT_IS_TRIGGER);
		
		static Component *create(std::vector<std::string> args);
		
		static bool registered;
		
		void update(GLFWwindow *window) override;
		
		void calculateBounds();
		
		void resolveCollisions();
		
		bool collidesWithAABB(BoxCollider *&other) const;
		
		CollisionInfo collidesWithOBB(BoxCollider *&other);
		
		glm::vec3 size;
		glm::vec3 offset;
		glm::vec3 globalSize {glm::vec3(0)};
		glm::vec3 center {glm::vec3(0)};
		
		bool isTrigger;
		
		Rigidbody *rigidbody {nullptr};
	private:
		float checkOverlapOnPlane(glm::vec3 plane, BoxCollider *&other);
		
		glm::vec3 minAABB {glm::vec3(0)};
		glm::vec3 maxAABB {glm::vec3(0)};
		
		OBBInfo obbInfo;
		
		static std::vector<BoxCollider *> boxColliders;
		
		static glm::vec3 DEFAULT_SIZE;
		static glm::vec3 DEFAULT_OFFSET;
		static bool DEFAULT_IS_TRIGGER;
	};
	
	struct CollisionInfo
	{
		bool collided = false;
		BoxCollider *a;
		BoxCollider *b;
		glm::vec3 collisionPoint;
		glm::vec3 normal;
		float depth;
	};
}

#endif //ENGINE_BOX_COLLIDER_H
