//
// Created by michiel on 8/25/25.
//

#ifndef ENGINE_RIGIDBODY_H
#define ENGINE_RIGIDBODY_H

#include "component.h"

#include "math/vec3.h"


namespace engine {
	class BoxCollider;
	class Rigidbody : public Component
	{
	public:
		explicit Rigidbody(float mass, float gravity = DEFAULT_GRAVITY);
		
		static Component *create(const std::vector<std::string>& args);
		static bool registered;
		
		void update(GLFWwindow *window) override;
		
		void addVelocity(math::vec3 v);
		void addVelocity(float x, float y, float z);
		void addVelocity(float strength, math::vec3 direction);
		void setVelocity(math::vec3 v);
		void setVelocity(float scalar);
		void setVelocity(float x, float y, float z);
		void setVelocity(float strength, math::vec3 direction);
		
		void translate(math::vec3 offset);
		void translate(float x, float y, float z);
		void translate(float scale, math::vec3 axis);
		
		void teleport(math::vec3 offset);
		void teleport(float x, float y, float z);
		
		void rotate(math::vec3 rot);
		void rotate(float x, float y, float z);
		void rotateTo(math::vec3 rot);
		void rotateTo(float x, float y, float z);
		void rotateAxis(float degrees, math::vec3 axis);
		void rotateToAxis(float degrees, math::vec3 axis);
		
		void scale(math::vec3 scale);
		void scale(float x, float y, float z);
		void scale(float scale);
		void scaleBy(math::vec3 scale);
		void scaleBy(float x, float y, float z);
		void scaleBy(float scale);
		
		math::vec3 velocity;
		float gravity;
		float mass;
	private:
		BoxCollider *boxCollider { nullptr };
		void applyHalfGravity();
		
		
		static float DEFAULT_GRAVITY;
	};
} // engine

#endif //ENGINE_RIGIDBODY_H
