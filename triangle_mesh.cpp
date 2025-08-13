#include "triangle_mesh.h"

namespace engine
{
    TriangleMesh::TriangleMesh(std::vector<Vertex> vertices, Texture *texture, Shader *shader, std::vector<unsigned int> indices)
        : m_texture(texture)
        , m_vertices(vertices)
        , m_shader(shader)
        , m_indices(indices)
    {
        initialise();
    }

    TriangleMesh::TriangleMesh(std::vector<Vertex> vertices, Shader *shader, std::vector<unsigned int> indices)
        : m_vertices(vertices)
        , m_shader(shader)
        , m_indices(indices)
    {
        initialise();
    }

    void TriangleMesh::vertexAttribPointer(int index, int size, GLenum type, bool normalized, int stride, const GLvoid *offset)
    {
        glVertexAttribPointer(index, size, type, normalized, stride, offset);
        glEnableVertexAttribArray(index);
    }

    void TriangleMesh::draw()
    {
        if (m_texture)
            m_texture->bind();
        m_shader->uniformb("useTexture", m_texture != nullptr);
        m_shader->use();
        glBindVertexArray(m_VAO);
        
        if (!m_indices.empty())
        {
            glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
        }
        else
            glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    }

    Shader *TriangleMesh::get_shader()
    {
        return m_shader;
    }

    void TriangleMesh::initialise()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        
        glBindVertexArray(m_VAO);
        
        // I LOVE CONTINUOUS STORAGE (AND STRUCTS)
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);
        
        if (!m_indices.empty())
        {
            glGenBuffers(1, &m_EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
        }
        
        vertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, position)); // position
        vertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, normal)); // normal
        vertexAttribPointer(2, 4, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, color)); // color
        vertexAttribPointer(3, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, texCoords)); // texCoords
        
        // unbind
        glBindVertexArray(0);
    }
}
