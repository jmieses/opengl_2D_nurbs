#pragma once
#include <iostream>
#include <array>

class VertexBuffer
{
public:

	VertexBuffer(const void* vertices, unsigned int size_of_vertices);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	unsigned int getID() const { return m_vertex_buffer_id; }

private:
	unsigned int m_vertex_buffer_id;
};

