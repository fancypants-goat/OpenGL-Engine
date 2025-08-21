//
// Created by michiel on 8/14/25.
//

#include <engine/mesh.h>

#include <iostream>

namespace engine {
	
	Mesh::Mesh()
	: m_subMeshes(), m_vao(-1)
	{
	}
	
	Mesh::Mesh(SubMesh subMesh)
			: m_subMeshes(std::vector<SubMesh> {subMesh}), m_vao(-1)
	{
	}
	
	Mesh::Mesh(Material material, std::vector<Vertex> vertices, std::vector<unsigned int> indices)
			: m_subMeshes(std::vector<SubMesh> {SubMesh(material, vertices, indices)}), m_vao(-1)
	{
	}
	
	void Mesh::initialize()
	{
		if (m_vao == -1)
			glGenVertexArrays(1, &m_vao);
		
		for (SubMesh subMesh : m_subMeshes)
		{
			subMesh.initialize();
		}
		
		upload(); // binds VAO -> uploads DATA -> unbinds VAO
	}
	
	void Mesh::upload()
	{
		use();
		
		for (SubMesh subMesh : m_subMeshes)
		{
			subMesh.upload();
		}
		
		glBindVertexArray(0);
	}
	
	void Mesh::use() const
	{
		glBindVertexArray(m_vao);
	}
	
	void Mesh::addSubMesh(SubMesh subMesh)
	{
		subMesh.initialize();
		subMesh.parentMesh = this;
		m_subMeshes.push_back(subMesh);
		upload();
	}
	
	void Mesh::addSubMeshSilent(SubMesh subMesh)
	{
		if (subMesh.get_vertices().empty())
			return;
		
		subMesh.initialize();
		subMesh.parentMesh = this;
		m_subMeshes.push_back(subMesh);
	}
	
	void Mesh::singleUpload(SubMesh *subMesh) const
	{
		use();
		
		subMesh->upload();
		
		glBindVertexArray(0);
	}
	
	std::vector<SubMesh> Mesh::get_SubMeshes()
	{
		return m_subMeshes;
	}
} // engine