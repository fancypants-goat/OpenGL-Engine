#include "shader.h"

using namespace std;

namespace engine {
	Shader::Shader(const char *vertexPath, const char *fragPath)
			: m_vertexShader(glCreateShader(GL_VERTEX_SHADER)),
			  m_fragmentShader(glCreateShader(GL_FRAGMENT_SHADER)),
			  m_id(glCreateProgram())
	{
		compileShader(m_vertexShader, readShaderFromFile(vertexPath));
		compileShader(m_fragmentShader, readShaderFromFile(fragPath));
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
	
	const char *Shader::readShaderFromFile(const char *path)
	{
		string sourceString;
		string s;
		
		ifstream f(path);
		
		if (!f.is_open())
			cerr << "Error opening file: " << path << endl;
		
		while (getline(f, s))
			sourceString += s + '\n';
		
		f.close();
		
		int n = sourceString.length();
		
		char *source = new char[n + 1];
		
		strcpy(source, sourceString.c_str());
		
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
	
	
	void Shader::uniformf(const char *name, float value)
	{ glUniform1f(glGetUniformLocation(m_id, name), value); }
	
	void Shader::uniform2f(const char *name, float a, float b)
	{ glUniform2f(glGetUniformLocation(m_id, name), a, b); }
	
	void Shader::uniform3f(const char *name, float a, float b, float c)
	{ glUniform3f(glGetUniformLocation(m_id, name), a, b, c); }
	
	void Shader::uniform4f(const char *name, float a, float b, float c, float d)
	{ glUniform4f(glGetUniformLocation(m_id, name), a, b, c, d); }
	
	void Shader::uniformi(const char *name, int value)
	{ glUniform1i(glGetUniformLocation(m_id, name), value); }
	
	void Shader::uniform2i(const char *name, int a, int b)
	{ glUniform2i(glGetUniformLocation(m_id, name), a, b); }
	
	void Shader::uniform3i(const char *name, int a, int b, int c)
	{ glUniform3i(glGetUniformLocation(m_id, name), a, b, c); }
	
	void Shader::uniform4i(const char *name, int a, int b, int c, int d)
	{ glUniform4i(glGetUniformLocation(m_id, name), a, b, c, d); }
	
	void Shader::uniformui(const char *name, unsigned int value)
	{ glUniform1ui(glGetUniformLocation(m_id, name), value); }
	
	void Shader::uniform2ui(const char *name, unsigned int a, unsigned int b)
	{ glUniform2ui(glGetUniformLocation(m_id, name), a, b); }
	
	void Shader::uniform3ui(const char *name, unsigned int a, unsigned int b, unsigned int c)
	{ glUniform3ui(glGetUniformLocation(m_id, name), a, b, c); }
	
	void Shader::uniform4ui(const char *name,
							unsigned int a,
							unsigned int b,
							unsigned int c,
							unsigned int d)
	{ glUniform4ui(glGetUniformLocation(m_id, name), a, b, c, d); }
	
	void Shader::uniformb(const char *name, bool value)
	{ glUniform1i(glGetUniformLocation(m_id, name), (int) value); }
	
	void Shader::uniformmat2(const char *name, bool transpose, glm::mat2 value)
	{ glUniformMatrix2fv(glGetUniformLocation(m_id, name), 1, transpose, glm::value_ptr(value)); }
	
	void Shader::uniformmat3(const char *name, bool transpose, glm::mat3 value)
	{ glUniformMatrix3fv(glGetUniformLocation(m_id, name), 1, transpose, glm::value_ptr(value)); }
	
	void Shader::uniformmat4(const char *name, bool transpose, glm::mat4 value)
	{ glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, transpose, glm::value_ptr(value)); }
	
	void Shader::uniformmat2x3(const char *name, bool transpose, glm::mat2x3 value)
	{ glUniformMatrix2x3fv(glGetUniformLocation(m_id, name), 1, transpose, glm::value_ptr(value)); }
	
	void Shader::uniformmat3x2(const char *name, bool transpose, glm::mat3x2 value)
	{ glUniformMatrix3x2fv(glGetUniformLocation(m_id, name), 1, transpose, glm::value_ptr(value)); }
	
	void Shader::uniformmat2x4(const char *name, bool transpose, glm::mat2x4 value)
	{ glUniformMatrix2x4fv(glGetUniformLocation(m_id, name), 1, transpose, glm::value_ptr(value)); }
	
	void Shader::uniformmat4x2(const char *name, bool transpose, glm::mat4x2 value)
	{ glUniformMatrix4x2fv(glGetUniformLocation(m_id, name), 1, transpose, glm::value_ptr(value)); }
	
	void Shader::uniformmat3x4(const char *name, bool transpose, glm::mat3x4 value)
	{ glUniformMatrix3x4fv(glGetUniformLocation(m_id, name), 1, transpose, glm::value_ptr(value)); }
	
	void Shader::unifomrmat4x3(const char *name, bool transpose, glm::mat4x3 value)
	{ glUniformMatrix4x3fv(glGetUniformLocation(m_id, name), 1, transpose, glm::value_ptr(value)); }
	
	void Shader::vertexAttribPointer(int index, int size, GLenum type, bool normalized, int stride,
									 const GLvoid *offset)
	{
		glVertexAttribPointer(index, size, type, normalized, stride, offset);
		glEnableVertexAttribArray(index);
	}
}
