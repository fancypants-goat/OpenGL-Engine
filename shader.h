#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <bits/stdc++.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace engine
{
    class Shader
    {
        public:
            Shader(const char* vertexPath, const char* fragPath);
            
            void use();
            int get_id();
            
            void uniformf(const char *name, float value);
            void uniform2f(const char *name, float a, float b);
            void uniform3f(const char *name, float a, float b, float c);
            void uniform4f(const char *name, float a, float b, float c, float d);
            
            void uniformi(const char *name, int value);
            void uniform2i(const char *name, int a, int b);
            void uniform3i(const char *name, int a, int b, int c);
            void uniform4i(const char *name, int a, int b, int c, int d);
            
            void uniformui(const char *name, unsigned int value);
            void uniform2ui(const char *name, unsigned int a, unsigned int b);
            void uniform3ui(const char *name, unsigned int a, unsigned int b, unsigned int c);
            void uniform4ui(const char *name, unsigned int a, unsigned int b, unsigned int c, unsigned int d);
            
            void uniformb(const char *name, bool value);
        
            void uniformmat2(const char *name, bool transpose, glm::mat2 value);
            void uniformmat3(const char *name, bool transpose, glm::mat3 value);
            void uniformmat4(const char *name, bool transpose, glm::mat4 value);
            void uniformmat2x3(const char *name, bool transpose, glm::mat2x3 value);
            void uniformmat3x2(const char *name, bool transpose, glm::mat3x2 value);
            void uniformmat2x4(const char *name, bool transpose, glm::mat2x4 value);
            void uniformmat4x2(const char *name, bool transpose, glm::mat4x2 value);
            void uniformmat3x4(const char *name, bool transpose, glm::mat3x4 value);
            void unifomrmat4x3(const char *name, bool transpose, glm::mat4x3 value);
		
			void vertexAttribPointer(int index, int size, GLenum type, bool normalized, int stride, const GLvoid *offset);
			
			template<typename MatType>
			void vertexAttribPointerMatrix(int startIndex, bool normalized)
			{
				const int cols = MatType::length();
				const int colSize = cols * sizeof(float);
				const int rows = sizeof(MatType) / colSize;
				
				for (int i = 0; i < rows; i++)
				{
					vertexAttribPointer(startIndex + i, cols, GL_FLOAT, normalized, sizeof(MatType),
										(void *) (i * colSize));
					glVertexAttribDivisor(4 + i, 1);
				}
			}
			
            
            
        private:
            unsigned int m_id;
            unsigned int m_vertexShader;
            unsigned int m_fragmentShader;
            
            void compileProgram();
            
            static const char *readShaderFromFile(const char *path);
            static void compileShader(unsigned int shader, const char* source);
    };
}


#endif
