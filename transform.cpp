//
// Created by michiel on 8/16/25.
//

#include "transform.h"

#include <glm/gtc/matrix_transform.hpp>

namespace engine {
	Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
			: position(position), rotation(rotation), scale(scale)
	{
	}
	
	glm::mat4 Transform::positionMatrix()
	{
		return glm::translate(glm::mat4(1), position);
	}
	
	glm::mat4 Transform::rotationMatrix()
	{
		glm::mat4 rot (1);
		rot = glm::rotate(rot, rotation.x, glm::vec3(1,0,0));
		rot = glm::rotate(rot, rotation.y, glm::vec3(0,1,0));
		rot = glm::rotate(rot, rotation.z, glm::vec3(0,0,1));
		return rot;
	}
	
	glm::mat4 Transform::scaleMatrix()
	{
		return glm::scale(glm::mat4(1), scale);
	}
	
	glm::mat4 Transform::modelMatrix()
	{
		return positionMatrix() * rotationMatrix() * scaleMatrix();
	}
	
} // engine