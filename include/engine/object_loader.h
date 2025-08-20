//
// Created by michiel on 8/19/25.
//

#ifndef ENGINE_OBJECT_LOADER_H
#define ENGINE_OBJECT_LOADER_H

#include <bits/stdc++.h>
#include "vertex.h"
#include "mesh.h"

namespace engine {
	
	class ObjectLoader
	{
	public:
		explicit ObjectLoader(std::string);
		
		void LoadVertices();
		Mesh LoadAsMesh();
		
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
	private:
		std::string source;
		
		const char *VERTEX_POSITION_INDICATOR = "v";
		const char *VERTEX_NORMAL_INDICATOR = "vn";
		const char *VERTEX_TEXTURE_COORDINATE_INDICATOR = "vt";
		const char *VERTEX_FACES_INDICATOR = "f";
	};
	
} // engine

#endif //ENGINE_OBJECT_LOADER_H
