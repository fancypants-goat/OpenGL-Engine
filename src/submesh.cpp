//
// Created by michiel on 8/20/25.
//
#include <engine/submesh.h>

#include <engine/mesh.h>

namespace engine {
	
	SubMesh::SubMesh(Material material, std::vector<Vertex> vertices,
					 std::vector<unsigned int> indices,
					 SubMesh::StorageType storageType)
			: material(material), m_vertices(vertices), m_indices(indices),
			  m_storageType(storageType), m_vbo(-1), m_ebo(-1)
	{
	}
	
	void SubMesh::initialize()
	{
		if (m_vbo == -1)
			glGenBuffers(1, &m_vbo);
		if (m_ebo == -1)
			glGenBuffers(1, &m_ebo);
	}
	
	void SubMesh::upload()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(),
					 (int) m_storageType);
		
		if (!m_indices.empty())
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int),
						 m_indices.data(), (int) m_storageType);
		}
		
		// because no shader is present in this class,
		// as it is sent through to mesh_renderer.hpp,
		// use the raw gl methods to set the vertex attributes
		
		std::size_t vertexSize(sizeof(Vertex));
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize,
							  (void *) offsetof(Vertex, position));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize,
							  (void *) offsetof(Vertex, normal));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize,
							  (void *) offsetof(Vertex, texCoord));
		
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
	}
	
	std::vector<unsigned int> SubMesh::get_indices()
	{
		return m_indices;
	}
	
	std::vector<Vertex> SubMesh::get_vertices()
	{
		return m_vertices;
	}
	
	void SubMesh::updateVertices(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	{
		m_vertices = vertices;
		m_indices = indices;
		parentMesh->singleUpload(this);
	}
	
	SubMesh::StorageType SubMesh::get_storageType()
	{
		return m_storageType;
	}
	
	void SubMesh::set_storageType(SubMesh::StorageType storageType)
	{
		m_storageType = storageType;
		parentMesh->singleUpload(this);
	}
}

