#pragma once
#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer
{
public:

	VertexBuffer(const void* vertices, unsigned int size_of_vertices);
	VertexBuffer(std::vector<float>& vertices, unsigned int draw = true);
	~VertexBuffer();

	void Bind() const;
	void BindDynamic(const std::vector<float>& vertices) const;
	void Unbind() const;
	void setData(const void* vertices, unsigned int size_of_vertices);
	void setID(unsigned int);
	unsigned int getID() const { return m_vertex_buffer_id; }


private:
	unsigned int m_vertex_buffer_id;
	const unsigned int NUM_VERTICES_ALLOCATED = 1000;
};

