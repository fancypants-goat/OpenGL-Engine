//
// Created by michiel on 8/14/25.
//

#include <engine/mesh_renderer.h>

#include <glm/glm.hpp>
#include <engine/camera.h>

namespace engine {
	
	MeshRenderer::MeshRenderer(Mesh _mesh,
							   Shader *shader,
							   Texture *texture,
							   std::vector<Transform> transforms)
			: mesh(_mesh), shader(shader), texture(texture), m_transforms(transforms), m_vbo(-1)
	{
		mesh.initialize();
		initialize();
	}
	
	MeshRenderer::MeshRenderer(Mesh _mesh, Shader *shader, Texture *texture, Transform transform)
			: mesh(_mesh), shader(shader), texture(texture),
			  m_transforms(std::vector<Transform> {transform}), m_vbo(-1)
	{
		mesh.initialize();
		initialize();
	}
	
	MeshRenderer::MeshRenderer(Mesh _mesh, Shader *shader, Texture *texture)
			: mesh(_mesh), shader(shader), texture(texture), m_transforms(), m_vbo(-1)
	{
		mesh.initialize();
		initialize();
	}
	
	MeshRenderer::MeshRenderer(Mesh _mesh,
							   Shader *shader,
							   std::vector<Transform> transforms)
			: mesh(_mesh), shader(shader), texture(), m_transforms(transforms), m_vbo(-1)
	{
		mesh.initialize();
		initialize();
	}
	
	MeshRenderer::MeshRenderer(Mesh _mesh, Shader *shader, Transform transform)
			: mesh(_mesh), shader(shader), texture(),
			  m_transforms(std::vector<Transform> {transform}), m_vbo(-1)
	{
		mesh.initialize();
		initialize();
	}
	
	MeshRenderer::MeshRenderer(Mesh _mesh, Shader *shader)
			: mesh(_mesh), shader(shader), texture(), m_transforms(), m_vbo(-1)
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
		mesh.use();
		
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		
		std::vector<glm::mat4> models;
		models.reserve(m_transforms.size());
		
		for (Transform t : m_transforms)
		{
			models.push_back(t.modelMatrix());
		}
		
		glBufferData(GL_ARRAY_BUFFER, models.size() * sizeof(glm::mat4), models.data(),
					 GL_DYNAMIC_DRAW);
		
		shader->vertexAttribPointerMatrix<glm::mat4>(3, false);
		
		glBindVertexArray(0);
	}
	
	void MeshRenderer::draw(GLFWwindow *window)
	{
		glm::ivec2 viewport;
		glfwGetWindowSize(window, &viewport.x, &viewport.y);
		
		mesh.use();
		
		if (texture != nullptr)
			texture->use();
		
		shader->use();
		shader->uniformb("useTexture", texture != nullptr);
		shader->uniformmat4("camera", false, Camera::get_main()->cameraProjection(viewport));
		shader->uniform3f("cameraPos", Camera::get_main()->position.x,
						  Camera::get_main()->position.y, Camera::get_main()->position.z);
		shader->uniform3f("lightPos", -1.19842,0.560531,4.0903);
		shader->uniform3f("lightColor", 1, 1, 1);
		shader->uniform3f("objColor", color.x, color.y, color.z);
		
		for (SubMesh subMesh : mesh.get_SubMeshes())
		{
			glm::vec3 ambientColor = color;
			glm::vec3 diffuseColor = color;
			glm::vec3 specularColor = color;
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
			
			if (!subMesh.get_indices().empty())
				glDrawElementsInstanced(GL_TRIANGLES, subMesh.get_indices().size(), GL_UNSIGNED_INT,
										nullptr, m_transforms.size());
			else
				glDrawArraysInstanced(GL_TRIANGLES, 0, subMesh.get_vertices().size(),
									  m_transforms.size());
		}
	}
	
	void MeshRenderer::addTransform(Transform transform)
	{
		m_transforms.push_back(transform);
		upload();
	}
	
	std::vector<Transform> MeshRenderer::get_transforms()
	{
		return m_transforms;
	}
} // engine