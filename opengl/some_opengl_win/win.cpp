#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "renderer.hpp"
#include "buffer.hpp"

typedef unsigned int uint32;

void sys_error(const char *e)
{
	glfwTerminate();

	perror(e);
	exit(EXIT_FAILURE);
}

typedef struct ShaderSource
{
	std::string vs;
	std::string fs;
} ShaderSource;

static ShaderSource parse_shader(const char *filepath)
{
	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss[2];

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	ShaderType type = ShaderType::NONE; 

	while(getline(stream, line))
	{
		if(line.find("#shader") != std::string::npos)
		{
			if(line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if(line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
			ss[static_cast<int>(type)] << line << '\n';
	}

	ShaderSource shader_source{ ss[0].str(), ss[1].str() };

	return shader_source;
}

GLFWwindow * create_new_window(const char *title = "Default",
							   int w = 1024, int h = 768,
							   GLFWmonitor *monitor = nullptr,
							   GLFWwindow *share = nullptr)
{
	GLFWwindow *new_win = glfwCreateWindow(w, h, title, monitor, share);
	if (!new_win)
	{
		glfwDestroyWindow(new_win);
		sys_error("create_new_window: glfwCreateWindow error");
	}
	return new_win;
}

static uint32 CompileShader(uint32 type, const char *source)
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

static uint32 CreateShader(const std::string &v_shader, const std::string &f_shader)
{
	GLCALL( uint32 program = glCreateProgram() );
	uint32 vs = CompileShader(GL_VERTEX_SHADER, v_shader.c_str());
	uint32 fs = CompileShader(GL_FRAGMENT_SHADER, f_shader.c_str());

	if (!vs || !fs)
		sys_error("CreateShader: CompileShader error");

	GLCALL( glAttachShader(program, vs) );
	GLCALL( glAttachShader(program, fs) );
	GLCALL( glLinkProgram(program) );
	GLCALL( glValidateProgram(program) );

	GLCALL( glDeleteShader(vs) );
	GLCALL( glDeleteShader(fs) );

	return program;
}

static inline float rand_color(int min, int max)
{
	return (float)(rand() % (max + 1 - min) + min) / 10.0f;
}

void mainWin()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!glfwInit())
		sys_error("mainWin: glfwInit error");

	GLFWwindow *win = create_new_window("My main window");

	glfwMakeContextCurrent(win);

	glfwSwapInterval(5);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		sys_error("mainWin: glewInit error");

	std::cout << glGetString(GL_VERSION) << ' ' << glGetString(GL_RENDERER)
			  << std::endl;

	{
		float vertex_position[] = { -0.5f, -0.5f,
									0.5f, -0.5f,
									0.5f,  0.5f,
									-0.5f,  0.5f };
		uint32 indices[] = { 0, 1, 2,
							 2, 3, 0 };

		uint32 vao;
		GLCALL( glGenVertexArrays(1, &vao) );
		GLCALL( glBindVertexArray(vao) );

		VertexBuffer vb(vertex_position, sizeof vertex_position);

		GLCALL( glEnableVertexAttribArray(0) );
		GLCALL( glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
									  sizeof *vertex_position * 2, 0) );

		uint32 numberIndices = sizeof indices / sizeof(float);
		IndexBuffer ib(indices, numberIndices);

		ShaderSource shader_source = parse_shader("shader/Shader.shader");

		uint32 shader = CreateShader(shader_source.vs, shader_source.fs);
		GLCALL( glUseProgram(shader) );

		GLCALL( int location = glGetUniformLocation(shader, "u_color") );
		ASSERT(location != -1);
		GLCALL( glUniform4f(location, 0.2235f, 1.0f, 0.8f, 1.0f) );

		GLCALL( glBindVertexArray(0) );
		GLCALL( glUseProgram(0) );
		GLCALL( glBindBuffer(GL_ARRAY_BUFFER, 0) );
		GLCALL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );

		float colors[] = {0.0f, 0.0f, 0.0f}, interval[] = {0.2f, 0.4f, 0.6f};
		while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			   !glfwWindowShouldClose(win))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			GLCALL( glUseProgram(shader) );
			GLCALL( glUniform4f(location, colors[0], colors[1], colors[2], 1.0f) );

			GLCALL( glBindVertexArray(vao) );
			ib.bind();

			GLCALL( glDrawElements(GL_TRIANGLES, numberIndices,
								   GL_UNSIGNED_INT, nullptr) );

			if(colors[0] > 1.0f)
				interval[0] = -rand_color(1, 5);
			else if(colors[0] < 0.0f)
				interval[0] = rand_color(1, 5);
			if(colors[1] > 1.0f)
				interval[1] = -rand_color(1, 5);
			else if(colors[1] < 0.0f)
				interval[1] = rand_color(1, 5);
			if(colors[2] > 1.0f)
				interval[2] = -rand_color(1, 5);
			else if(colors[2] < 0.0f)
				interval[2] = rand_color(1, 5);
			colors[0] += interval[0];
			colors[1] += interval[1];
			colors[2] += interval[2];

			glfwSwapBuffers(win);

			glfwPollEvents();
		}

		glDeleteProgram(shader);
	}
	glfwTerminate();
}

int main()
{
	srand(time(NULL));
	mainWin();

	return 1;
}
