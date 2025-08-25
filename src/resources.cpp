//
// Created by michiel on 8/13/25.
//

#include <engine/resources.h>
#include <iostream>

namespace engine {
	std::string Resources::get(const char *path)
	{
		return (std::filesystem::path(PROJECT_DIR) / "Resources" / path).string();
	}
} // engine