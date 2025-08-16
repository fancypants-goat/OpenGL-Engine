//
// Created by michiel on 8/14/25.
//

#include "mesh.h"

#include <utility>

namespace engine {
	Mesh::Mesh(Shader *shader, Texture *texture, std::vector<Vertex> vertices,
			   std::vector<unsigned int> indices)
			: shader(shader), texture(texture), m_vertices(std::move(vertices)),
			  m_indices(std::move(indices)),
			  m_vao(0), m_vbo(0), m_ebo(0)
	{
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ebo);
		
		use();
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(),
					 GL_STATIC_DRAW);
		
		if (!m_indices.empty())
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int),
						 m_indices.data(),
						 GL_STATIC_DRAW);
		}
		
		shader->vertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex),
									(void *) offsetof(Vertex, position));
		shader->vertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex),
									(void *) offsetof(Vertex, normal));
		shader->vertexAttribPointer(2, 4, GL_FLOAT, false, sizeof(Vertex),
									(void *) offsetof(Vertex, color));
		shader->vertexAttribPointer(3, 2, GL_FLOAT, false, sizeof(Vertex),
									(void *) offsetof(Vertex, texCoords));
		
		glBindVertexArray(0); // unbind
	}
	
	void Mesh::draw()
	{
		if (texture != nullptr)
			texture->use();
		shader->uniformb("useTexture", texture != nullptr);
		shader->use();
		use();
		
		if (!m_indices.empty())
			glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
		else
			glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
	}
	
	void Mesh::use() const
	{
		glBindVertexArray(m_vao);
	}
	
	std::vector<unsigned int> Mesh::get_indices()
	{
		return m_indices;
	}
} // engine