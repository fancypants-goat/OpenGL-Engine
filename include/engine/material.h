//
// Created by michiel on 8/20/25.
//

#ifndef ENGINE_MATERIAL_H
#define ENGINE_MATERIAL_H

#include <engine/math/vec3.h>

namespace engine {
	struct Material
	{
		math::vec3 ambientColor = math::vec3(-1);
		math::vec3 diffuseColor = math::vec3(-1);
		math::vec3 specularColor = math::vec3(-1);
		float specularExponent = 32;
		float alpha = 1;
	};
} // engine

#endif //ENGINE_MATERIAL_H
