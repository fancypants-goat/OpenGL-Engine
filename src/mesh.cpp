//
// Created by michiel on 8/14/25.
//

#include <engine/mesh.h>

#include <iostream>

namespace engine {
	
	Mesh::Mesh(std::vector<Vertex> vertices,
			   std::vector<unsigned int> indices,
			   Mesh::StorageType storageType)
			: m_vertices(vertices), m_indices(indices), m_storageType(storageType), m_vao(-1),
			  m_vbo(-1), m_ebo(-1)
	{
	}
	
	void Mesh::initialize()
	{
		if (m_vao == -1)
			glGenVertexArrays(1, &m_vao);
		if (m_vbo == -1)
			glGenBuffers(1, &m_vbo);
		if (m_ebo == -1)
			glGenBuffers(1, &m_ebo);
		
		upload(); // binds VAO -> uploads DATA -> unbinds VAO
	}
	
	void Mesh::upload()
	{
		use();
		
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
		
		glBindVertexArray(0);
	}
	
	void Mesh::use() const
	{
		glBindVertexArray(m_vao);
	}
	
	std::vector<unsigned int> Mesh::get_indices()
	{
		return m_indices;
	}
	
	std::vector<Vertex> Mesh::get_vertices()
	{
		return m_vertices;
	}
	
	void Mesh::updateVertices(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	{
		m_vertices = vertices;
		m_indices = indices;
		
		upload();
	}
	
	Mesh::StorageType Mesh::get_storageType()
	{
		return m_storageType;
	}
	
	void Mesh::set_storageType(Mesh::StorageType storageType)
	{
		m_storageType = storageType;
		
		upload();
	}
} // engine