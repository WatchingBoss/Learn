#define GLEW_STATIC

#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../inc/sup.hpp"
#include "../inc/glfw.hpp"

#include "../inc/shader.hpp"

#define MW_Width 1024
#define MW_Height 720

static void framebuffer_size_callback(GLFWwindow *win, int width, int height)
{
	glViewport(0, 0, width, height);
	(void)win;
}

static void key_callback(GLFWwindow *win, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{		
		glfwSetWindowShouldClose(win, true);
		return;
	}

	(void)scancode;
	(void)mods;
}

static void mainWin()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if(!glfwInit())
		sys_error("mainWin: glfwInit error");

	GLFWwindow *win = create_new_window(MW_Width, MW_Height, "Main window", nullptr, nullptr);

	glfwMakeContextCurrent(win);
	glfwSwapInterval(5);

	glewExperimental = GLEW_OK;
	if(glewInit() != GLEW_OK)
		sys_error("mainWin: glewInit error");

	GLCALL( glViewport(0, 0, MW_Width, MW_Height) );

	std::cout << glGetString(GL_VERSION) << "  " << glGetString(GL_RENDERER) << std::endl;

	{
		float vertex[] = { -0.5f, -0.5f, 0.0f,
						    0.5f, -0.5f, 0.0f,
						   -0.5f,  0.5f, 0.0f,
						    0.5f,  0.5f, 0.0f };

		uint32 index[] = { 0, 1, 3,
						   0, 2, 3 };

		uint32 vao;
		GLCALL( glGenVertexArrays(1, &vao) );
		GLCALL( glBindVertexArray(vao) );

		uint32 vbo;
		GLCALL( glGenBuffers(1, &vbo) );
		GLCALL( glBindBuffer(GL_ARRAY_BUFFER, vbo) );
		GLCALL( glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW) );

		uint32 index_count = sizeof index / sizeof(uint32);
		uint32 ebo;
		GLCALL( glGenBuffers(1, &ebo) );
		GLCALL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo) );
		GLCALL( glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof index, index, GL_STATIC_DRAW) );

		Shader program("../shader/shader.glsl");

		GLCALL( glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
									  3 * sizeof(float), (void *)0) );
		GLCALL( glEnableVertexAttribArray(0) );

		while(!glfwWindowShouldClose(win))
		{
			GLCALL( glClearColor(0.41f, 0.4f, 0.5f, 1.0f) );
			GLCALL( glClear(GL_COLOR_BUFFER_BIT) );

			program.Bind();
			GLCALL( glBindVertexArray(vao) );

			GLCALL( glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0) );

			GLCALL( glBindVertexArray(0) );

			glfwSetKeyCallback(win, key_callback);

			glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);

			glfwSwapBuffers(win);
			glfwPollEvents();
		}
	}

	glfwDestroyWindow(win);
    glfwTerminate();
}

int main()
{
	mainWin();

	return 0;
}

