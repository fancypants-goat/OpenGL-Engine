//
// Created by michiel on 8/16/25.
//

#ifndef ENGINE_TRANSFORM_H
#define ENGINE_TRANSFORM_H

#include <glm/glm.hpp>
#include <vector>
#include <engine/component.h>

namespace engine {
	
	class Transform : Component
	{
	public:
		Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
		
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
		
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 size;
		
		glm::mat4 positionMatrix() const;
		glm::mat4 rotationMatrix() const;
		glm::mat4 scaleMatrix() const;
		glm::mat4 modelMatrix() const;
		
		glm::mat4 localPositionMatrix() const;
		glm::mat4 localRotationMatrix() const;
		glm::mat4 localScaleMatrix() const;
		
		glm::vec3 globalPosition() const;
		glm::vec3 globalRotation() const;
		glm::vec3 globalScale() const;
		
		void set_parent(Transform *p);
		void set_parent(Entity p);
		
		Transform *parent;
	private:
		std::vector<Transform *> children;
	};
	
} // engine

#endif //ENGINE_TRANSFORM_H
