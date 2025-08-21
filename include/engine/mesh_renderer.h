//
// Created by michiel on 8/14/25.
//

#ifndef ENGINE_MESH_RENDERER_H
#define ENGINE_MESH_RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "mesh.h"
#include "transform.h"
#include "shader.h"
#include "texture.h"

namespace engine {
	
	class MeshRenderer
	{
	public:
		MeshRenderer(Mesh mesh, Shader *shader, Texture *texture, std::vector<Transform> transforms);
		
		MeshRenderer(Mesh mesh, Shader *shader, Texture *texture, Transform transform);
		
		explicit MeshRenderer(Mesh mesh, Shader *shader, Texture *texture);
		
		MeshRenderer(Mesh mesh, Shader *shader, std::vector<Transform> transforms);
		
		MeshRenderer(Mesh mesh, Shader *shader, Transform transform);
		
		explicit MeshRenderer(Mesh mesh, Shader *shader);
		
		void upload();
		
		void draw(GLFWwindow *window);
		
		void addTransform(Transform transform);
		
		std::vector<Transform> get_transforms();
		
		Mesh mesh;
		Shader *shader;
		Texture *texture;
		glm::vec3 color = glm::vec3(1);
	private:
		void initialize();
		
		std::vector<Transform> m_transforms;
		
		unsigned int m_vbo;
	};
	
} // engine

#endif //ENGINE_MESH_RENDERER_H
