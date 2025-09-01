//
// Created by michiel on 8/25/25.
//

#ifndef ENGINE_RIGIDBODY_H
#define ENGINE_RIGIDBODY_H

#include "component.h"

#include <glm/glm.hpp>

namespace engine {
	class BoxCollider;
	class Rigidbody : public Component
	{
	public:
		Rigidbody(float mass, float gravity = -9.81);
		
		static Component *create(const std::vector<std::string> args);
		static bool registered;
		
		void update(GLFWwindow *window) override;
		
		void addVelocity(glm::vec3 v);
		void addVelocity(float x, float y, float z);
		void addVelocity(float strength, glm::vec3 direction);
		void setVelocity(glm::vec3 v);
		void setVelocity(float scalar);
		void setVelocity(float x, float y, float z);
		void setVelocity(float strength, glm::vec3 direction);
		
		void translate(glm::vec3 offset);
		void translate(float x, float y, float z);
		void translate(float scale, glm::vec3 axis);
		
		void teleport(glm::vec3 offset);
		void teleport(float x, float y, float z);
		
		void rotate(glm::vec3 rot);
		void rotate(float x, float y, float z);
		void rotateTo(glm::vec3 rot);
		void rotateTo(float x, float y, float z);
		void rotateAxis(float degrees, glm::vec3 axis);
		void rotateToAxis(float degrees, glm::vec3 axis);
		
		void scale(glm::vec3 scale);
		void scale(float x, float y, float z);
		void scale(float scale);
		void scaleBy(glm::vec3 scale);
		void scaleBy(float x, float y, float z);
		void scaleBy(float scale);
		
		glm::vec3 velocity;
		float gravity;
		float mass;
	private:
		BoxCollider *boxCollider { nullptr };
		void applyHalfGravity();
	};
} // engine

#endif //ENGINE_RIGIDBODY_H
