//
// Created by michiel on 8/16/25.
//

#ifndef ENGINE_TRANSFORM_H
#define ENGINE_TRANSFORM_H

#include <glm/glm.hpp>
#include <vector>

namespace engine {
	class Entity;
	
	class Transform
	{
	public:
		Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
		
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
		
		glm::mat4 positionMatrix() const;
		
		glm::mat4 rotationMatrix() const;
		
		glm::mat4 scaleMatrix() const;
		
		glm::mat4 modelMatrix() const;
		
		glm::mat4 localPositionMatrix() const;
		
		glm::mat4 localRotationMatrix() const;
		
		glm::mat4 localScaleMatrix() const;
		
		void set_parent(Transform *p);
		
		void set_parent(Entity *p);
		
		glm::vec3 globalPosition() const;
		
		glm::vec3 globalRotation() const;
		
		glm::vec3 globalSize() const;
		
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 size;
		
		Transform *parent {nullptr};
		Entity *entity {nullptr};
	private:
		
		friend Entity;
		std::vector<Transform *> m_children;
	};
	
} // engine

#endif //ENGINE_TRANSFORM_H
