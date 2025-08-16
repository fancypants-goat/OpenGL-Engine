//
// Created by michiel on 8/14/25.
//

#include "mesh_group.h"

#include <utility>

namespace engine {
	MeshGroup::MeshGroup(Mesh *mesh)
			: m_mesh(mesh), m_transforms()
	{
		initialize();
	}
	
	MeshGroup::MeshGroup(Mesh *mesh, std::vector<Transform> transforms)
			: m_mesh(mesh), m_transforms(std::move(transforms))
	{
		initialize();
	}
	
	void MeshGroup::addTransform(Transform transform)
	{
		m_transforms.push_back(transform);
	}
	
	void MeshGroup::upload()
	{
		if (m_transforms.empty()) std::cout << "Canceled upload! No transforms to upload." << std::endl;
		
		std::vector<glm::mat4> models;
		models.reserve(m_transforms.size());
		for (Transform t : m_transforms)
		{
			models.push_back(t.modelMatrix());
		}
		
		m_mesh->use();
		glBufferData(GL_ARRAY_BUFFER, models.size() * sizeof(glm::mat4), models.data(),
					 GL_DYNAMIC_DRAW);
	}
	
	void MeshGroup::initialize()
	{
		m_mesh->use();
		
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		
		upload();
		
		m_mesh->shader->vertexAttribPointerMatrix<glm::mat4>(4, false);
		
		glBindVertexArray(0);
	}
	
	void MeshGroup::draw()
	{
		if (m_mesh->texture != nullptr)
			m_mesh->texture->use();
		m_mesh->shader->uniformb("useTexture", m_mesh->texture != nullptr);
		m_mesh->shader->use();
		m_mesh->use();
		
		if (!m_mesh->get_indices().empty())
			glDrawElementsInstanced(GL_TRIANGLES, m_mesh->get_indices().size(), GL_UNSIGNED_INT, 0, m_transforms.size());
//		else
//			glDrawArraysInstanced(GL_TRIANGLES, 0, m_transforms.size());
	}
} // engine