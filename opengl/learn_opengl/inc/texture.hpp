#ifndef TEXTURE_H
#define TEXTURE_H

#include "sup.hpp"

typedef enum { PNG, JPEG } eIMG_TYPE;

class Texture {
  private:
	uint32 m_Renderer;

  public:
	Texture(const char *, eIMG_TYPE);
	~Texture();

	void Bind(uint32) const;
	void Unbind() const;
};

#endif
