#pragma once
#include "glad/glad.h"

#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram();

	void AttachShader(Shader *shader);
	void LinkProgram();
	void UseProgram();

private:
	GLuint m_programId = 0;

	bool m_linked = false;
};

