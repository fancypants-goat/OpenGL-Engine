//
// Created by michiel on 8/20/25.
//

#ifndef ENGINE_SIMPLEOBJECTLOADER_H
#define ENGINE_SIMPLEOBJECTLOADER_H

#include <bits/stdc++.h>
#include <engine/vertex.h>
#include <engine/mesh.h>
#include <engine/material.h>

namespace engine {
	class SOL
	{
	public:
		SOL() = delete;
		
		static Mesh
		ReadFile(std::string source);
		
		static Mesh
		ReadObj(std::string source);
		
		static std::unordered_map<std::string, Material> ReadMTL(std::string source);
	};
}

#endif // ENGINE_SIMPLEOBJECTLOADER_H
