#include <engine/shader.h>

using namespace std;

namespace engine {
	Shader::Shader(std::string vertexPath, std::string fragPath)
			: m_vertexShader(glCreateShader(GL_VERTEX_SHADER)),
			  m_fragmentShader(glCreateShader(GL_FRAGMENT_SHADER)),
			  m_id(glCreateProgram())
	{
		compileShader(m_vertexShader, readShaderFromFile(vertexPath).c_str());
		compileShader(m_fragmentShader, readShaderFromFile(fragPath).c_str());
		compileProgram();
	}
	
	void Shader::use()
	{
		glUseProgram(m_id);
	}
	
	int Shader::get_id()
	{
		return m_id;
	}
	
	void Shader::compileProgram()
	{
		glAttachShader(m_id, m_vertexShader);
		glAttachShader(m_id, m_fragmentShader);
		glLinkProgram(m_id);
		
		int success;
		char infoLog[512];
		glGetProgramiv(m_id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
			cerr << "ERROR:PROGRAM::LINKING_FAILED\n" << infoLog << endl;
		}
		
		glDeleteShader(m_vertexShader);
		glDeleteShader(m_fragmentShader);
	}
	
	std::string Shader::readShaderFromFile(std::string path)
	{
		string source;
		string s;
		
		ifstream f(path);
		
		if (!f.is_open())
			cerr << "Error opening file: " << path << endl;
		
		while (getline(f, s))
			source += s + '\n';
		
		f.close();
		
		return source;
	}
	
	void Shader::compileShader(unsigned int shader, const char *source)
	{
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);
		
		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			cerr << "ERROR:SHADER::COMPILATION_FAILED\n" << infoLog << endl;
		}
	}
	
	
	void Shader::uniformf(std::string name, float value)
	{ glUniform1f(glGetUniformLocation(m_id, name.c_str()), value); }
	
	void Shader::uniform2f(std::string name, float a, float b)
	{ glUniform2f(glGetUniformLocation(m_id, name.c_str()), a, b); }
	
	void Shader::uniform3f(std::string name, float a, float b, float c)
	{ glUniform3f(glGetUniformLocation(m_id, name.c_str()), a, b, c); }
	
	void Shader::uniform4f(std::string name, float a, float b, float c, float d)
	{ glUniform4f(glGetUniformLocation(m_id, name.c_str()), a, b, c, d); }
	
	void Shader::uniform2fv(std::string name, float *value)
	{ glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 2, value); }
	
	void Shader::uniform3fv(std::string name, float *value)
	{ glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 3, value); }
	
	void Shader::uniform4fv(std::string name, float *value)
	{ glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 4, value); }
	
	void Shader::uniformi(std::string name, int value)
	{ glUniform1i(glGetUniformLocation(m_id, name.c_str()), value); }
	
	void Shader::uniform2i(std::string name, int a, int b)
	{ glUniform2i(glGetUniformLocation(m_id, name.c_str()), a, b); }
	
	void Shader::uniform3i(std::string name, int a, int b, int c)
	{ glUniform3i(glGetUniformLocation(m_id, name.c_str()), a, b, c); }
	
	void Shader::uniform4i(std::string name, int a, int b, int c, int d)
	{ glUniform4i(glGetUniformLocation(m_id, name.c_str()), a, b, c, d); }
	
	void Shader::uniformui(std::string name, unsigned int value)
	{ glUniform1ui(glGetUniformLocation(m_id, name.c_str()), value); }
	
	void Shader::uniform2ui(std::string name, unsigned int a, unsigned int b)
	{ glUniform2ui(glGetUniformLocation(m_id, name.c_str()), a, b); }
	
	void Shader::uniform3ui(std::string name, unsigned int a, unsigned int b, unsigned int c)
	{ glUniform3ui(glGetUniformLocation(m_id, name.c_str()), a, b, c); }
	
	void Shader::uniform4ui(std::string name,
							unsigned int a,
							unsigned int b,
							unsigned int c,
							unsigned int d)
	{ glUniform4ui(glGetUniformLocation(m_id, name.c_str()), a, b, c, d); }
	
	void Shader::uniformb(std::string name, bool value)
	{ glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int) value); }
	
	void Shader::uniformmat2(std::string name, bool transpose, glm::mat2 value)
	{
		glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, transpose,
						   glm::value_ptr(value));
	}
	
	void Shader::uniformmat3(std::string name, bool transpose, glm::mat3 value)
	{
		glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, transpose,
						   glm::value_ptr(value));
	}
	
	void Shader::uniformmat4(std::string name, bool transpose, glm::mat4 value)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, transpose,
						   glm::value_ptr(value));
	}
	
	void Shader::uniformmat2x3(std::string name, bool transpose, glm::mat2x3 value)
	{
		glUniformMatrix2x3fv(glGetUniformLocation(m_id, name.c_str()), 1, transpose,
							 glm::value_ptr(value));
	}
	
	void Shader::uniformmat3x2(std::string name, bool transpose, glm::mat3x2 value)
	{
		glUniformMatrix3x2fv(glGetUniformLocation(m_id, name.c_str()), 1, transpose,
							 glm::value_ptr(value));
	}
	
	void Shader::uniformmat2x4(std::string name, bool transpose, glm::mat2x4 value)
	{
		glUniformMatrix2x4fv(glGetUniformLocation(m_id, name.c_str()), 1, transpose,
							 glm::value_ptr(value));
	}
	
	void Shader::uniformmat4x2(std::string name, bool transpose, glm::mat4x2 value)
	{
		glUniformMatrix4x2fv(glGetUniformLocation(m_id, name.c_str()), 1, transpose,
							 glm::value_ptr(value));
	}
	
	void Shader::uniformmat3x4(std::string name, bool transpose, glm::mat3x4 value)
	{
		glUniformMatrix3x4fv(glGetUniformLocation(m_id, name.c_str()), 1, transpose,
							 glm::value_ptr(value));
	}
	
	void Shader::unifomrmat4x3(std::string name, bool transpose, glm::mat4x3 value)
	{
		glUniformMatrix4x3fv(glGetUniformLocation(m_id, name.c_str()), 1, transpose,
							 glm::value_ptr(value));
	}
	
	void Shader::vertexAttribPointer(int index, int size, GLenum type, bool normalized, int stride,
									 const GLvoid *offset)
	{
		glVertexAttribPointer(index, size, type, normalized, stride, offset);
		glEnableVertexAttribArray(index);
	}
	
}
