#include "VertexBuffer.h"




VertexBuffer::VertexBuffer(const void* vertices, unsigned int size_of_vertices)
{
	glGenBuffers(1, &m_vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, size_of_vertices, vertices, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(std::vector<float>& vertices, unsigned int dynamic_draw)
{
	glGenBuffers(1, &m_vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_id);

	if(dynamic_draw){
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);
	}
	else{
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * NUM_VERTICES_ALLOCATED, nullptr, GL_DYNAMIC_DRAW);
	}
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_id);
}

void VertexBuffer::BindDynamic(const std::vector<float>& vertices) const{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), &vertices.front());
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
