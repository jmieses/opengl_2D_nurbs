#pragma once
#include <iostream>
#include <array>

class IndexBuffer
{
public:

	IndexBuffer(const void* vertices, unsigned int size_of_vertices);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	void setData(const void* vertices, unsigned int size_of_vertices);
	void setID(unsigned int);
	unsigned int getID() const { return m_index_buffer_id; }


private:
	unsigned int m_index_buffer_id;
};

