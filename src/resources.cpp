//
// Created by michiel on 8/13/25.
//

#include <engine/resources.h>
#include <bits/stdc++.h>

namespace engine {
	std::string Resources::get(const char *path)
	{
		std::ifstream f(path);
		if (f.good())
			return path;
		
		return (std::filesystem::path(PROJECT_DIR) / "Resources" / path).string();
	}
	
	std::string Resources::get(std::string path)
	{
		std::ifstream f(path);
		if (f.good())
			return path;
		
		return (std::filesystem::path(PROJECT_DIR) / "Resources" / path).string();
	}
} // engine