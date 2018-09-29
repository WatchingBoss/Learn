#ifndef SHADER_H
#define SHADER_H

#include "vendor/glm/glm.hpp"
#include "rend_sup.hpp"

#include <string>
#include <unordered_map>

typedef struct ShaderSource
{
	std::string vs;
	std::string fs;
} ShaderSource;

class Shader
{
  private:
	uint32 m_RendererID;
	std::string m_FilePath;
	std::unordered_map<std::string, int> m_UniformLocationCashe;
  public:
	Shader(const std::string &file_path);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniformi(const std::string &name, int value);
	void SetUniform1f(const std::string &name, float value);
	void SetUniform4f(const std::string &name, 
					  float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string &name, const glm::mat4 &matrix);
  private:
	int GetUniformLocation(const std::string &name);
	ShaderSource ParseShader(const std::string &filepath);
	uint32 CompileShader(uint32 type, const char *source);
	uint32 CreateShader(const std::string &v_shader, const std::string &f_shader);
};

#endif
