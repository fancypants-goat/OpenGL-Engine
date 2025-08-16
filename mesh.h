//
// Created by michiel on 8/14/25.
//

#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H

#include <vector>
#include "vertex.h"
#include "texture.h"
#include "shader.h"

namespace engine {
	
	class Mesh
	{
	public:
		Mesh(Shader *shader, Texture *texture, std::vector<Vertex> vertices,
			 std::vector<unsigned int> indices = {});
		
		void draw();
		void use() const;
		std::vector<unsigned int> get_indices();
		
		Texture *texture;
		Shader *shader;
		
		
	private:
		unsigned int m_vao, m_vbo, m_ebo;
		
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
	};
	
} // engine

#endif //ENGINE_MESH_H
