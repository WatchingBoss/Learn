#ifndef RENDERER_H
#define RENDERER_H

#include <signal.h>
#include <GL/glew.h>

#include "rend_sup.hpp"

/* Renderer */

#include "buffer.hpp"
#include "shader.hpp"

class Renderer
{
  public:
	void Clear() const;
	void Draw(const VertexArray &va, const IndexBuffer &ib,
			  const Shader &shader) const;
};

/* END Renderer */

#endif
