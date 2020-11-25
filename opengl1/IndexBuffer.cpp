#include "IndexBuffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


IndexBuffer::IndexBuffer(const void* indices, unsigned int count)
{
	glGenBuffers(1, &m_index_buffer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_index_buffer_id);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void IndexBuffer::setData(const void* vertices, unsigned int size_of_vertices)
{
	this->Bind();
	glBufferData(GL_ARRAY_BUFFER, size_of_vertices, vertices, GL_DYNAMIC_DRAW);
}

void IndexBuffer::setID(unsigned int id)
{
	m_index_buffer_id = id;
}
