#include <cstdio>
#include <cstdlib>

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef unsigned int uint32;

void sys_error(const char *e)
{
	glfwTerminate();

	perror(e);
	exit(EXIT_FAILURE);
}

GLFWwindow * create_new_window(const char *title = "Default", int w = 1024, int h = 768, 
							   GLFWmonitor *monitor = nullptr, GLFWwindow *share = nullptr)
{
	GLFWwindow *new_win = glfwCreateWindow(w, h, title, monitor, share);
	if(!new_win)
	{
		glfwDestroyWindow(new_win);
		sys_error("create_new_window: glfwCreateWindow error");
	}
	return new_win;
}

static const char *vertex_shader =
	"#version 330 core\n\n"
	"lyout(location = 0) in vec4 postion;\n\n"
	"void main()\n" "{\n"
	"    gl_Position = position;\n"
	"}\n";
static const char *fragment_shader =
	"#version 330 core\n\n"
	"lyout(location = 0) out vec4 color;\n"
	"void main()\n" "{\n"
	"    color = vec4(1.0, 0.2, 0.5, 1.0);\n"
	"}\n";

static uint32 CompileShader(uint32 type, const char *source)
{
	uint32 id = glCreateShader(type);
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if(!result)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = (char *)alloca(length * sizeof(char) + 1);
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Faliled to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
				  << " shader" << '\n' << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static uint32 CreateShader(const char *v_shader, const char *f_shader)
{
	uint32 program = glCreateProgram();
	uint32 vs = CompileShader(GL_VERTEX_SHADER, v_shader);
	uint32 fs = CompileShader(GL_FRAGMENT_SHADER, f_shader);

	if(!vs || !fs)
		sys_error("CreateShader: CompileShader error");

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void mainWin()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if(!glfwInit())
		sys_error("mainWin: glfwInit error");

	GLFWwindow *win = create_new_window("My main window");

	glfwMakeContextCurrent(win);

	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
		sys_error("mainWin: glewInit error");

	std::cout << glGetString(GL_VERSION) << ' ' << glGetString(GL_RENDERER) << std::endl;

	float vertex_position[] = { -0.5f, -0.5f,
								 0.0f,  0.5f,
								 0.5f, -0.5f };
	uint32 buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertex_position, vertex_position, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof *vertex_position * 2, 0);

	uint32 shader = CreateShader(vertex_shader, fragment_shader);
	glUseProgram(shader);

	while(glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(win))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(win);

		glfwPollEvents();
	}

	glfwTerminate();
}

int main()
{
	mainWin();

	return 1;
}
