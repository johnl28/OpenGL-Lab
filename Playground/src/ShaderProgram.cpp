#include "ShaderProgram.h"
#include <iostream>

ShaderProgram::ShaderProgram()
{
	m_programId =  glCreateProgram();
}

void ShaderProgram::AttachShader(Shader* shader)
{
	if (!shader)
	{
		std::cout << "Failed to attach shader to program " << m_programId << "";
		return;
	}
	else if (!shader->IsCompiled())
	{
		std::cout << "Failed to attach uncompiled shader to program " << m_programId << std::endl;
		return;
	}

	glAttachShader(m_programId, shader->GetID());
}

void ShaderProgram::LinkProgram()
{
	glLinkProgram(m_programId);

	GLint success = 0;

	glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		char errBuff[500];
		glGetProgramInfoLog(m_programId, sizeof(errBuff), nullptr, errBuff);

		std::cout << "Failed to link shader program with ID: " << m_programId << "Error: " << errBuff << std::endl;
		return;
	}

	m_linked = true;
	std::cout << "Shader program linked" << std::endl;
}

void ShaderProgram::Bind() const
{
	glUseProgram(m_programId);
}

void ShaderProgram::Unbind() const
{
	glUseProgram(0);
}

void ShaderProgram::SetUniform1i(const std::string& uniform, GLint v0)
{
	glUniform1i(GetUniformLocation(uniform), v0);
}

void ShaderProgram::SetUniform4f(const std::string& uniform, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	glUniform4f(GetUniformLocation(uniform), v0, v1, v2, v3);
}

void ShaderProgram::SetUniform3f(const std::string& uniform, GLfloat v0, GLfloat v1, GLfloat v2)
{
	glUniform3f(GetUniformLocation(uniform), v0, v1, v2);
}

GLuint ShaderProgram::GetUniformLocation(const std::string& uniform)
{
	auto it = m_unifromLocation.find(uniform);
	if (it != m_unifromLocation.end())
	{
		return it->second;
	}

	auto location = glGetUniformLocation(GetID(), uniform.c_str());
	if (location == -1) 
	{
		std::cout << "Shader unifrom " << uniform << "not found" << std::endl;
	}

	m_unifromLocation[uniform] = location;
	return location;
}
