#ifndef SHADER_H
#define SHADER_H

#include "sup.hpp"

#include <string>

typedef struct SourceGLSL
{
	std::string vs;
	std::string fs;
} SourceGLSL;

class Shader
{
  private:
	uint32 m_RendererID;
	std::string m_FilePath;
  public:
	Shader(const std::string &filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

  private:
	SourceGLSL ParseSource();
	uint32 CompileShader(uint32 type, const char *source);
	uint32 CreateShader(const std::string &vs, const std::string &fs);
};

#endif
