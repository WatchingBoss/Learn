#include "buffer.hpp"
#include "renderer.hpp"

/* Vertex Buffer */
VertexBuffer::VertexBuffer(const void *data, uint32 size)
{
	GLCALL( glGenBuffers(1, &m_RendererID) );
	GLCALL( glBindBuffer(GL_ARRAY_BUFFER, m_RendererID) );
	GLCALL( glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW) );
}

VertexBuffer::~VertexBuffer()
{
	GLCALL( glDeleteBuffers(1, &m_RendererID) );
}

void VertexBuffer::Bind() const
{
	GLCALL( glBindBuffer(GL_ARRAY_BUFFER, m_RendererID) );
}

void VertexBuffer::Unbind() const
{
	GLCALL( glBindBuffer(GL_ARRAY_BUFFER, 0) );
}
/* END Vertex Buffer */

/* Index buffer */
IndexBuffer::IndexBuffer(const uint32 *data, uint32 count)
	: m_Count(count)
{
	GLCALL( glGenBuffers(1, &m_RendererID) );
	GLCALL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID) );
	GLCALL( glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32),
						 data, GL_STATIC_DRAW) );
}

IndexBuffer::~IndexBuffer()
{
	GLCALL( glDeleteBuffers(1, &m_RendererID) );
}

void IndexBuffer::Bind() const
{
	GLCALL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID) );
}

void IndexBuffer::Unbind() const
{
	GLCALL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
}

/* END Index buffer */

/* Vertex buffer layout */
/* VertexBufferLayout::VertexBufferLayout() */
/* //	: m_Stride */
/* { */

/* } */

VertexBufferLayout::~VertexBufferLayout()
{

}

/* END Vertex buffer layout */

/* Vertex array */
VertexArray::VertexArray()
{
	GLCALL( glGenVertexArrays(1, &m_RendererID) );
}

VertexArray::~VertexArray()
{
	GLCALL( glDeleteVertexArrays(1, &m_RendererID) );
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
	Bind();
	vb.Bind();
	const auto & elements = layout.GetElements();
	uint32 offset = 0;

	for(uint32 i = 0; i < elements.size(); ++i)
	{
		const auto &element = elements[i];

		GLCALL( glEnableVertexAttribArray(i) );
		GLCALL( glVertexAttribPointer(i, element.count, element.type, GL_FALSE,
 									  layout.GetStride(), (const void*)offset) );
		offset += element.count * VertexBufferElements::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GLCALL( glBindVertexArray(m_RendererID) );
}

void VertexArray::Unbind() const
{
	GLCALL( glBindVertexArray(0) );
}

/* END Vertex array */
