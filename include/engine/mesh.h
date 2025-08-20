//
// Created by michiel on 8/14/25.
//

#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H

#include <glad/glad.h>
#include <vector>
#include "vertex.h"

namespace engine {
	
	class Mesh
	{
	public:
		enum class StorageType
		{
			Static = GL_STATIC_DRAW,
			Dynamic = GL_DYNAMIC_DRAW
		};
		
		Mesh(std::vector<Vertex> vertices,
			 std::vector<unsigned int> indices = {}, StorageType storageType = StorageType::Static);
		
		void initialize();
		
		void upload();
		
		void use() const;
		
		std::vector<unsigned int> get_indices();
		
		std::vector<Vertex> get_vertices();
		
		void updateVertices(std::vector<Vertex> vertices, std::vector<unsigned int> indices = {});
		
		StorageType get_storageType();
		
		void set_storageType(StorageType storageType);
	
	
	private:
		unsigned int m_vao, m_vbo, m_ebo;
		
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		StorageType m_storageType;
	};
	
} // engine

#endif //ENGINE_MESH_H
