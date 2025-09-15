//
// Created by michiel on 8/14/25.
//

#ifndef ENGINE_MESH_RENDERER_H
#define ENGINE_MESH_RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "math/vec3.h"

namespace engine {
	struct EntityRenderData
	{
		glm::mat4 model;
		math::vec3 color;
	};
	
	class Entity;
	class MeshRenderer
	{
	public:
		MeshRenderer();
		MeshRenderer(Mesh mesh, Shader *shader, Texture *texture = nullptr);

		void upload();

		void draw(GLFWwindow *window);

		void addEntity(Entity *entity);

		void addEntitySilent(Entity *entity);

		std::vector<Entity *> get_entities();

		Mesh mesh;
		Shader *shader;
		Texture *texture;
		bool enabled = true;
	private:
		friend class SOL;
		void initialize();
		
		std::vector<Entity *> m_entities;
		unsigned int m_vbo = -1;
	};
	
} // engine

#endif //ENGINE_MESH_RENDERER_H
