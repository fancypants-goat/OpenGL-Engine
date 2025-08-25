//
// Created by michiel on 8/25/25.
//

#ifndef ENGINE_RIGIDBODY_H
#define ENGINE_RIGIDBODY_H

#include "component.h"

#include <glm/glm.hpp>

namespace engine {
	class Rigidbody : public Component
	{
	public:
		Rigidbody(float mass, float gravity = 9.81);
		
		void update() override;
		
		void translate(glm::vec3 offset);
		void translate(float x, float y, float z);
		
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
		void applyHalfGravity();
	};
} // engine

#endif //ENGINE_RIGIDBODY_H
