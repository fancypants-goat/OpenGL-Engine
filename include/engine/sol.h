//
// Created by michiel on 8/20/25.
//

#ifndef ENGINE_SIMPLEOBJECTLOADER_H
#define ENGINE_SIMPLEOBJECTLOADER_H

#include <bits/stdc++.h>
#include <engine/vertex.h>
#include <engine/mesh.h>

namespace engine {
	class Object
	{
	public:
		Object(std::string source);
		
		
	private:
		std::string source;
	};
	
	static void
	ReadFile(std::string source, std::vector<Vertex> *vertices, std::vector<unsigned int> *indices);
	
	static void
	ReadObj(std::string source, std::vector<Vertex> *vertices, std::vector<unsigned int> *indices);
	
	static Mesh ReadFileToMesh(std::string source);
}

#endif // ENGINE_SIMPLEOBJECTLOADER_H
