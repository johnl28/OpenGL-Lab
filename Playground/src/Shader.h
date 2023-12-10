#pragma once
#include <vector>
#include <string>

#include "glad/glad.h"


class Shader
{
public:
	Shader(const std::string& file, GLenum shaderType);
	~Shader();

	void Compile();


	// getters
	GLint GetID() { return m_shaderId; }
	GLenum GetType() { return m_shaderType; }

	bool IsCompiled() { return m_compiled; }
 
private:
	void ReadShaderFile();

private:
	GLuint m_shaderId = 0;
	GLenum m_shaderType = 0;

	std::string m_shaderFile = "";
	std::string m_shaderCode = "";

	bool m_compiled = false;

};

