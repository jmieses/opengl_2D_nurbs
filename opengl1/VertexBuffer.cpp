#include "VertexBuffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


VertexBuffer::VertexBuffer(const void* vertices, unsigned int size_of_vertices)
{
	glGenBuffers(1, &m_vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, size_of_vertices, vertices, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_id);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setData(const void * vertices, unsigned int size_of_vertices)
{
	this->Bind();
	glBufferData(GL_ARRAY_BUFFER, size_of_vertices, vertices, GL_DYNAMIC_DRAW);
}

void VertexBuffer::setID(unsigned int id) 
{
	m_vertex_buffer_id = id;
}
