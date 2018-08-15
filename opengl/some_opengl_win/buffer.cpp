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

void VertexBuffer::bind() const
{
	GLCALL( glBindBuffer(GL_ARRAY_BUFFER, m_RendererID) );
}

void VertexBuffer::unbind() const
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

void IndexBuffer::bind() const
{
	GLCALL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID) );
}

void IndexBuffer::unbind() const
{
	GLCALL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
}

/* END Index buffer */

