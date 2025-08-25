//
// Created by michiel on 8/14/25.
//

#include <engine/mesh.h>

#include <iostream>

namespace engine {
	
	Mesh::Mesh()
	: m_subMeshes()
	{
	}
	
	Mesh::Mesh(SubMesh subMesh)
			: m_subMeshes(std::vector<SubMesh> {subMesh})
	{
	}
	
	Mesh::Mesh(Material material, std::vector<Vertex> vertices, std::vector<unsigned int> indices)
			: m_subMeshes(std::vector<SubMesh> {SubMesh(material, vertices, indices)})
	{
	}
	
	void Mesh::initialize()
	{
		for (SubMesh subMesh : m_subMeshes)
		{
			subMesh.initialize();
		}
		
		upload();
	}
	
	void Mesh::upload()
	{
		for (SubMesh subMesh : m_subMeshes)
		{
			subMesh.upload();
		}
	}
	
	void Mesh::addSubMesh(SubMesh subMesh)
	{
		if (subMesh.get_vertices().empty())
			return;
		
		subMesh.initialize();
		m_subMeshes.push_back(subMesh);
	}
	
	std::vector<SubMesh> Mesh::get_SubMeshes()
	{
		return m_subMeshes;
	}
} // engine