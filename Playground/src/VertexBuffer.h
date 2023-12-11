#pragma once
#include "glad/glad.h"

class VertexBuffer
{
public:
	VertexBuffer(const void* data, size_t size);
	~VertexBuffer();

	void Bind() const;
	void UnNind() const;

private:
	GLuint m_bufferID = 0;
};

