//
// Created by michiel on 8/20/25.
//

#ifndef ENGINE_SIMPLEOBJECTLOADER_H
#define ENGINE_SIMPLEOBJECTLOADER_H

#include <bits/stdc++.h>
#include <engine/vertex.h>
#include <engine/mesh.h>
#include <engine/material.h>
#include <engine/scene.h>

namespace engine {
	class SOL
	{
	public:
		struct RawSceneData
		{
			std::string name;
			
			std::unordered_map<std::string, Entity *> tokenizedEntities;
			std::unordered_map<std::string, MeshRenderer *> tokenizedDrawables;
			
			std::vector<Entity *> rootEntities;
			std::vector<MeshRenderer *> drawables;
		};
		
		SOL() = delete;
		
		static Mesh
		readMeshFile(std::string source);
		
		static Mesh
		readObj(std::string source);
		
		static std::unordered_map<std::string, Material> readMTL(std::string source);
		
		
		static Scene *readScene(std::string source);
		static RawSceneData readSceneRaw(std::string source);
		static std::vector<std::string> tokenizeArgs(std::string line);
		static glm::vec3 parseVec3(std::string toParse);
		static bool parseBool(std::string toParse);
	private:
		
		static glm::vec3 readVec3(std::istringstream &ss);
		static std::string readStringLiteral(std::istringstream &ss);
	};
}

#endif // ENGINE_SIMPLEOBJECTLOADER_H
