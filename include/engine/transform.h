//
// Created by michiel on 8/16/25.
//

#ifndef ENGINE_TRANSFORM_H
#define ENGINE_TRANSFORM_H

#include <vector>
#include <engine/math/vec3.h>

namespace engine {
	class Entity;
	
	class Transform
	{
	public:
		Transform(math::vec3 position, math::vec3 rotation, math::vec3 scale);
		
		void translate(const math::vec3& offset);
		
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
		
		glm::mat4 positionMatrix() const;
		
		glm::mat4 rotationMatrix() const;
		
		glm::mat4 scaleMatrix() const;
		
		glm::mat4 modelMatrix() const;
		
		glm::mat4 localPositionMatrix() const;
		
		glm::mat4 localRotationMatrix() const;
		
		glm::mat4 localScaleMatrix() const;
		
		void set_parent(Transform *p);
		
		void set_parent(Entity *p);
		
		math::vec3 globalPosition() const;
		
		math::vec3 globalRotation() const;
		
		math::vec3 globalSize() const;
		
		math::vec3 position;
		math::vec3 rotation;
		math::vec3 size;
		
		Transform *parent {nullptr};
		Entity *entity {nullptr};
	private:
		
		friend Entity;
		std::vector<Transform *> m_children;
	};
	
} // engine

#endif //ENGINE_TRANSFORM_H
