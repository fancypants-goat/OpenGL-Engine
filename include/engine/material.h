//
// Created by michiel on 8/20/25.
//

#ifndef ENGINE_MATERIAL_H
#define ENGINE_MATERIAL_H

#include <glm/glm.hpp>

namespace engine {
	struct Material
	{
		glm::vec3 ambientColor = glm::vec3(-1);
		glm::vec3 diffuseColor = glm::vec3(-1);
		glm::vec3 specularColor = glm::vec3(-1);
		float specularExponent = 32;
	};
} // engine

#endif //ENGINE_MATERIAL_H
