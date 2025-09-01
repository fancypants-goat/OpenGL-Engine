//
// Created by michiel on 8/13/25.
//

#ifndef ENGINE_RESOURCES_H
#define ENGINE_RESOURCES_H

#include <filesystem>

namespace engine {
	
	class Resources
	{
	public:
		static std::string get(const char *path);
		static std::string get(std::string path);
		
		Resources() = delete;
	};
	
} // engine

#endif //ENGINE_RESOURCES_H
