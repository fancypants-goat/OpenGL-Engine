//
// Created by michiel on 8/13/25.
//

#include "resources.h"

namespace engine {
	std::string Resources::Get(const char *path)
	{
		return (std::filesystem::path(PROJECT_DIR) / "Resources" / path).string();
	}
} // engine