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

void ShaderProgram::UseProgram()
{
	glUseProgram(m_programId);
}
