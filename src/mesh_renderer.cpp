//
// Created by michiel on 8/14/25.
//

#include <engine/mesh_renderer.h>

#include <glm/glm.hpp>
#include <engine/camera.h>
#include <engine/entity.h>

namespace engine {
	MeshRenderer::MeshRenderer()
			: mesh(), shader(nullptr), texture(nullptr), m_vbo(-1)
	{
	
	}
	
	MeshRenderer::MeshRenderer(Mesh mesh, Shader *shader, Texture *texture)
			: mesh(mesh), shader(shader), texture(texture), m_vbo(-1)
	{
		mesh.initialize();
		initialize();
	}
	
	void MeshRenderer::initialize()
	{
		if (m_vbo == -1)
			glGenBuffers(1, &m_vbo);
		
		upload();
	}
	
	void MeshRenderer::upload()
	{
		if (m_entities.empty())
			return;
		
		std::vector<EntityRenderData> bufferData;
		bufferData.reserve(m_entities.size());
		
		for (Entity *e : m_entities)
		{
			bufferData.push_back((*e).renderData);
		}
		
		for (SubMesh &subMesh : mesh.get_SubMeshes())
		{
			subMesh.use();
			
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(EntityRenderData) * bufferData.size(),
						 bufferData.data(), GL_DYNAMIC_DRAW);
			
			shader->vertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(EntityRenderData),
										offsetof(EntityRenderData, color));
			shader->vertexAttribPointerMatrix<glm::mat4>(4, false, sizeof(EntityRenderData),
														 offsetof(EntityRenderData, model));
			
			glVertexAttribDivisor(3, 1);
		}
		
		glBindVertexArray(0);
	}
	
	void MeshRenderer::draw(GLFWwindow *window)
	{
		glm::ivec2 viewport;
		glfwGetWindowSize(window, &viewport.x, &viewport.y);
		
		if (texture != nullptr)
			texture->use();
		
		shader->use();
		shader->uniformb("useTexture", texture != nullptr);
		shader->uniformmat4("camera", false, Camera::get_main()->cameraProjection(viewport));
		shader->uniform3f("cameraPos", Camera::get_main()->transform.position.x,
						  Camera::get_main()->transform.position.y, Camera::get_main()->transform.position.z);
		shader->uniform3f("lightPos", 4562, 6452, 5425423);
		shader->uniform3f("lightColor", 1, 1, 1);
		
		for (SubMesh subMesh : mesh.get_SubMeshes())
		{
			subMesh.use();
			
			glm::vec3 ambientColor = glm::vec3(1);
			glm::vec3 diffuseColor = glm::vec3(1);
			glm::vec3 specularColor = glm::vec3(1);
			if (subMesh.material.ambientColor != glm::vec3(-1))
				ambientColor = subMesh.material.ambientColor;
			if (subMesh.material.diffuseColor != glm::vec3(-1))
				diffuseColor = subMesh.material.diffuseColor;
			if (subMesh.material.specularColor != glm::vec3(-1))
				specularColor = subMesh.material.specularColor;
			
			shader->uniform3f("objAmbient", ambientColor.x,
							  ambientColor.y, ambientColor.z);
			shader->uniform3f("objDiffuse", diffuseColor.x,
							  diffuseColor.y, diffuseColor.z);
			shader->uniform3f("objSpecular", specularColor.x,
							  specularColor.y, specularColor.z);
			shader->uniformf("specularExp", subMesh.material.specularExponent);
			shader->uniformf("alpha", subMesh.material.alpha);
			
			if (!subMesh.get_indices().empty())
				glDrawElementsInstanced(GL_TRIANGLES, subMesh.get_indices().size(), GL_UNSIGNED_INT,
										nullptr, m_entities.size());
			else
				glDrawArraysInstanced(GL_TRIANGLES, 0, subMesh.get_vertices().size(),
									  m_entities.size());
		}
	}
	
	void MeshRenderer::addEntity(Entity *entity)
	{
		addEntitySilent(entity);
		entity->renderer = this;
	}
	
	void MeshRenderer::addEntitySilent(Entity *entity)
	{
		m_entities.push_back(entity);
		// add the entity to the entities list if it's not in there yet
		if (std::find(Entity::entities.begin(), Entity::entities.end(), entity) == Entity::entities.end())
			Entity::entities.push_back(entity);
	}
	
	std::vector<Entity *> MeshRenderer::get_entities()
	{
		return m_entities;
	}
} // engine