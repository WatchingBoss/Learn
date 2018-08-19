#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include "rend_sup.hpp"

class Texture
{
  private:
	uint32 m_RendererID;
	std::string m_FilePath;
	uchar *m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
  public:
	Texture(const std::string &path);
	~Texture();

	void Bind(uint32 slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};

#endif
