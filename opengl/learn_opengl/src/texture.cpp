#include "../inc/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <GL/GLEW.h>

Texture::Texture(const char *pathname, eIMG_TYPE img_type)
	: m_Renderer(0)
{
	stbi_set_flip_vertically_on_load(true);
	int t_width, t_height, nrChannels;

	uchar *t_data = stbi_load(pathname, &t_width, &t_height, &nrChannels, 0);

	GLCALL( glGenTextures(1, &m_Renderer) );
	GLCALL( glBindTexture(GL_TEXTURE_2D, m_Renderer) );

	GLCALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT) );
	GLCALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT) );
	GLCALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
	GLCALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );

	if(!t_data)
		sys_error("Failed to load texture");

	GLenum c_format;
	if (img_type == PNG) c_format = GL_RGBA;
	else if (img_type == JPEG) c_format = GL_RGB;

	GLCALL( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_width, t_height, 0,
						 c_format, GL_UNSIGNED_BYTE, t_data) );
//	GLCALL( glGenerateMipmap(GL_TEXTURE_2D) );

	stbi_image_free(t_data);
}

Texture::~Texture()
{
	GLCALL( glDeleteTextures(1, &m_Renderer) );
}

void Texture::Bind(uint32 slot) const
{
	GLCALL( glActiveTexture(GL_TEXTURE0 + slot) );
	GLCALL( glBindTexture(GL_TEXTURE_2D, m_Renderer) );
}

void Texture::Unbind() const 
{
	GLCALL( glBindTexture(GL_TEXTURE_2D, 0) );
}


