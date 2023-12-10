#include <fstream>
#include <iostream>
#include <sstream>

#include "Shader.h"


Shader::Shader(const std::string& filePath, GLenum shaderType)
{
	m_shaderType = shaderType;
	m_shaderFile = filePath;

	ReadShaderFile();
}

Shader::~Shader()
{
	glDeleteShader(m_shaderId);
}

void Shader::ReadShaderFile()
{
	std::ifstream file(m_shaderFile, std::ios::binary);
	std::stringstream shaderStream;

	if (!file.is_open())
	{
		std::cout << "Failed to open shader file. " << m_shaderFile << std::endl;
		return;
	}

	shaderStream << file.rdbuf();
	file.close();

	m_shaderCode = shaderStream.str();
}

void Shader::Compile()
{
	if (m_shaderCode.empty())
	{
		std::cout << "Cannot compile shader with ID " << m_shaderId << ". Shader code is empty." << std::endl;
		return;
	}


	const char* source = m_shaderCode.c_str();

	m_shaderId = glCreateShader(m_shaderType);

	glShaderSource(m_shaderId, 1, &source, NULL);
	glCompileShader(m_shaderId);

	GLint success = 0;
	glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(m_shaderId, 512, nullptr, infoLog);

		std::cout << infoLog << std::endl;
		return;
	}

	m_compiled = true;
	std::cout << "Shader compiled " << m_shaderId << std::endl;
}


