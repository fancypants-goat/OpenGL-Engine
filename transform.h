//
// Created by michiel on 8/16/25.
//

#ifndef ENGINE_TRANSFORM_H
#define ENGINE_TRANSFORM_H

#include <glm/glm.hpp>

namespace engine {
	
	class Transform
	{
	public:
		Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
		
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		
		glm::mat4 positionMatrix();
		glm::mat4 rotationMatrix();
		glm::mat4 scaleMatrix();
		glm::mat4 modelMatrix();
	};
	
} // engine

#endif //ENGINE_TRANSFORM_H
