#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, size_t size)
{
	glGenBuffers(1, &m_bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
}

void VertexBuffer::UnNind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
