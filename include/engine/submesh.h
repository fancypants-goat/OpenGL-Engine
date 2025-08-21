//
// Created by michiel on 8/20/25.
//

#ifndef ENGINE_SUBMESH_H
#define ENGINE_SUBMESH_H

#include <glad/glad.h>
#include <vector>
#include <engine/vertex.h>
#include <engine/material.h>

namespace engine {
	class Mesh;
	class SubMesh
	{
	public:
		enum class StorageType
		{
			Static = GL_STATIC_DRAW,
			Dynamic = GL_DYNAMIC_DRAW
		};
		
		SubMesh(Material material, std::vector<Vertex> vertices,
				std::vector<unsigned int> indices = {},
				StorageType storageType = StorageType::Static);
		
		void initialize();
		
		void upload();
		
		std::vector<unsigned int> get_indices();
		
		std::vector<Vertex> get_vertices();
		
		void updateVertices(std::vector<Vertex> vertices, std::vector<unsigned int> indices = {});
		
		SubMesh::StorageType get_storageType();
		
		void set_storageType(SubMesh::StorageType storageType);
		
		Material material;
		
		Mesh *parentMesh;
	
	private:
		unsigned int m_vbo, m_ebo;
		
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		SubMesh::StorageType m_storageType;
	};
}

#endif //ENGINE_SUBMESH_H
