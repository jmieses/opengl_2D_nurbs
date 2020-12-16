#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{	
	this->Bind();
	vb.Bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {

		const auto& element = elements[i];

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void *)offset);

		offset += element.count * VertexBufferElements::getSizeOfType(element.type);
	}
}

void VertexArray::AddOneBuffer(const VertexBuffer& vb, unsigned int count, unsigned int stride){
	this->Bind();
	vb.Bind();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, count, GL_FLOAT, GL_FALSE, stride, (const void *)0);
}

void const VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void const VertexArray::UnBind() const
{
	glBindVertexArray(0);
}
