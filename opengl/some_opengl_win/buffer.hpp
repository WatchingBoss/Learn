#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <vector>
#include <GL/glew.h>

#include "renderer.hpp"

typedef unsigned int uint32;
typedef unsigned char uchar;

/* Vertex buffer */
class VertexBuffer
{
private:
    uint32 m_RendererID;
public:
    VertexBuffer(const void *data, uint32 size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};
/* END Vertex buffer */

/* Index buffer */
class IndexBuffer
{
private:
    uint32 m_RendererID;
    uint32 m_Count;
public:
    IndexBuffer(const uint32 *data, uint32 size);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline uint32 Get_Count() const {return m_Count;}
};
/* END Index buffer */

/* Vertex buffer layout */
struct VertexBufferElements
{
    uint32 type;
    uint32 count;
    uchar normalized;

    static uint32 GetSizeOfType(uint32 type)
	{
		switch(type)
		{
		  case GL_FLOAT: return 4;
		  case GL_UNSIGNED_INT: return 4;
		  case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElements> m_Elements;
    uint32 m_Stride;
public:
    VertexBufferLayout()
		: m_Stride(0) {}
    ~VertexBufferLayout();

    template<typename T>
    void Push(uint32 count)
	{
	    static_assert(false);
	}

    template<>
    void Push<float>(uint32 count)
	{
		GLenum current_type = GL_FLOAT;
	    m_Elements.push_back({ current_type, count, GL_FALSE });
	    m_Stride += count * VertexBufferElements::GetSizeOfType(current_type);
	}
    template<>
    void Push<uint32>(uint32 count)
	{
		GLenum current_type = GL_UNSIGNED_INT;
	    m_Elements.push_back({ current_type, count, GL_FALSE });
	    m_Stride += count * VertexBufferElements::GetSizeOfType(current_type);
	}
    template<>
    void Push<uchar>(uint32 count)
	{
		GLenum current_type = GL_UNSIGNED_BYTE;
	    m_Elements.push_back({ current_type, count, GL_TRUE });
	    m_Stride += count * VertexBufferElements::GetSizeOfType(current_type);
	}

    inline const std::vector<VertexBufferElements> GetElements() const
	{ return m_Elements; }
    inline uint32 GetStride() const { return m_Stride; }
};
/* END Vertex buffer layout */

/* Vertex array */
class VertexArray
{
private:
    uint32 m_RendererID;
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

    void Bind() const;
    void Unbind() const;
};
/* END Vertex array */

#endif
