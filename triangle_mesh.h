// header files:
// declaration for everything
#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include "texture.h"
#include "vertex.h"
#include "shader.h"

namespace engine
{
    class TriangleMesh
    {
        public:
            TriangleMesh(std::vector<Vertex> vertices, Texture *texture, Shader *shader, std::vector<unsigned int> indices = {});
            TriangleMesh(std::vector<Vertex> vertices, Shader *shader, std::vector<unsigned int> indices = {});
            
            void vertexAttribPointer(int index, int size, GLenum type, bool normalized, int stride, const GLvoid *offset);
            
            void draw();
            
            Shader *get_shader();
            
        private:
            void initialise();
        
            unsigned int m_VAO;
            unsigned int m_VBO;
            unsigned int m_EBO;
        
            std::vector<Vertex> m_vertices;
            Texture *m_texture = nullptr;
            Shader *m_shader;
            std::vector<unsigned int> m_indices;
    };
}

#endif
