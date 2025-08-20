#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <bits/stdc++.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace engine {
	class Shader
	{
	public:
		Shader(std::string vertexPath, std::string fragPath);
		
		void use();
		
		int get_id();
		
		void uniformf(std::string name, float value);
		
		void uniform2f(std::string name, float a, float b);
		
		void uniform3f(std::string name, float a, float b, float c);
		
		void uniform4f(std::string name, float a, float b, float c, float d);
		
		void uniform2fv(std::string name, float *value);
		
		void uniform3fv(std::string name, float *value);
		
		void uniform4fv(std::string name, float *value);
		
		void uniformi(std::string name, int value);
		
		void uniform2i(std::string name, int a, int b);
		
		void uniform3i(std::string name, int a, int b, int c);
		
		void uniform4i(std::string name, int a, int b, int c, int d);
		
		void uniformui(std::string name, unsigned int value);
		
		void uniform2ui(std::string name, unsigned int a, unsigned int b);
		
		void uniform3ui(std::string name, unsigned int a, unsigned int b, unsigned int c);
		
		void uniform4ui(std::string name,
						unsigned int a,
						unsigned int b,
						unsigned int c,
						unsigned int d);
		
		void uniformb(std::string name, bool value);
		
		void uniformmat2(std::string name, bool transpose, glm::mat2 value);
		
		void uniformmat3(std::string name, bool transpose, glm::mat3 value);
		
		void uniformmat4(std::string name, bool transpose, glm::mat4 value);
		
		void uniformmat2x3(std::string name, bool transpose, glm::mat2x3 value);
		
		void uniformmat3x2(std::string name, bool transpose, glm::mat3x2 value);
		
		void uniformmat2x4(std::string name, bool transpose, glm::mat2x4 value);
		
		void uniformmat4x2(std::string name, bool transpose, glm::mat4x2 value);
		
		void uniformmat3x4(std::string name, bool transpose, glm::mat3x4 value);
		
		void unifomrmat4x3(std::string name, bool transpose, glm::mat4x3 value);
		
		void vertexAttribPointer(int index,
								 int size,
								 GLenum type,
								 bool normalized,
								 int stride,
								 const GLvoid *offset);
		
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
				glVertexAttribDivisor(startIndex + i, 1);
			}
		}
	
	
	private:
		unsigned int m_id;
		unsigned int m_vertexShader;
		unsigned int m_fragmentShader;
		
		void compileProgram();
		
		static std::string readShaderFromFile(std::string path);
		
		static void compileShader(unsigned int shader, const char *source);
	};
}


#endif
