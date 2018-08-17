#include "shader.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>

Shader::Shader(const std::string &filepath)
	: m_FilePath(filepath), m_RendererID(0)
{
	ShaderSource shader_source = ParseShader(filepath);
	m_RendererID = CreateShader(shader_source.vs, shader_source.fs);
}

Shader::~Shader()
{
	GLCALL( glDeleteProgram(m_RendererID) );
}

ShaderSource Shader::ParseShader(const std::string &filepath)
{
	std::ifstream stream(filepath.c_str());
	std::string line;
	std::stringstream ss[2];

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
			ss[static_cast<int>(type)] << line << '\n';
	}

	ShaderSource shader_source{ ss[0].str(), ss[1].str() };

	return shader_source;
}

uint32 Shader::CompileShader(uint32 type, const char *source)
{
	uint32 id = glCreateShader(type);
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = (char *)malloc(length * sizeof(char) + 1);
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Faliled to compile "
				  << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
				  << " shader" << '\n' << message << std::endl;
		glDeleteShader(id);
		free(message);
		return 0;
	}

	return id;
}

uint32 Shader::CreateShader(const std::string &v_shader, const std::string &f_shader)
{
	GLCALL(uint32 program = glCreateProgram());
	uint32 vs = CompileShader(GL_VERTEX_SHADER, v_shader.c_str());
	uint32 fs = CompileShader(GL_FRAGMENT_SHADER, f_shader.c_str());

	if (!vs || !fs)
	{
		perror("CreateShader: CompileShader error");
		exit(EXIT_FAILURE);
	}

	GLCALL(glAttachShader(program, vs));
	GLCALL(glAttachShader(program, fs));
	GLCALL(glLinkProgram(program));
	GLCALL(glValidateProgram(program));

	GLCALL(glDeleteShader(vs));
	GLCALL(glDeleteShader(fs));

	return program;
}

void Shader::Bind() const
{
	GLCALL( glUseProgram(m_RendererID) );
}

void Shader::Unbind() const
{
	GLCALL( glUseProgram(0) );
}

int Shader::GetUniformLocation(const std::string &name)
{
	if (m_UniformLocationCashe.find(name) != m_UniformLocationCashe.end())
		return m_UniformLocationCashe[name];
		

	GLCALL( int location = glGetUniformLocation(m_RendererID, name.c_str()) );
	if (location == -1)
		std::cout << "Uniform" << name << "Does not exist" << std::endl;

	m_UniformLocationCashe[name] = location;

	return location;
}

void Shader::SetUniform4f(const std::string &name, 
						  float v0, float v1, float v2, float v3)
{
	GLCALL( glUniform4f(GetUniformLocation(name), v0, v1, v2, v3) );
}
