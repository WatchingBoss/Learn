#ifndef SHADER_H
#define SHADER_H

#include "sup.hpp"

#include <string>
#include <GL/glew.h>

typedef struct SourceGLSL
{
	std::string vs;
	std::string fs;
} SourceGLSL;

class Shader
{
  private:
	uint32 m_RendererID;
	std::string m_VertPath, m_FragPath;
  public:
	Shader(const std::string &vertpath, const std::string &fragpath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const char *shaderVar, float f1, float f2,
		float f3, float f4) const;
	void SetUniform3f(const char *shaderVar, float f1, float f2,
		float f3) const;
	void SetUniform1i(const char *texture, int i1);
	void SetUniformMatrix4fv(const char *texture, GLsizei size, GLboolean transpose,
							 const GLfloat *fv);
  private:
	SourceGLSL ParseSource();
	uint32 CompileShader(uint32 type, const char *source);
	uint32 CreateShader(const std::string &vs, const std::string &fs);
};

#endif
