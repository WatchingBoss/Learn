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

float x_change = 0.0f, y_change = 0.0f;
static void key_callback(GLFWwindow *win, int key, int scancode, int action,
						 int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{		
		glfwSetWindowShouldClose(win, true);
		return;
	}

	float changing = 0.02f;
	switch(key)
	{
	  case GLFW_KEY_UP:
		  if(action == GLFW_PRESS)
			  y_change += changing;
		  else if(action == GLFW_RELEASE)
			  y_change = 0.0f;
		  break;
	  case GLFW_KEY_DOWN:
		  if(action == GLFW_PRESS)
			  y_change -= changing;
		  else if(action == GLFW_RELEASE)
			  y_change = 0.0f;
		  break;
	  case GLFW_KEY_RIGHT:
		  if(action == GLFW_PRESS)
			  x_change += changing;
		  else if(action == GLFW_RELEASE)
			  x_change = 0.0f;
		  break;
	  case GLFW_KEY_LEFT:
		  if(action == GLFW_PRESS)
			  x_change -= changing;
		  else if(action == GLFW_RELEASE)
			  x_change = 0.0f;
		  break;
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

	GLFWwindow *win = create_new_window(MW_Width, MW_Height, "Main window",
										nullptr, nullptr);

	glfwMakeContextCurrent(win);
	glfwSwapInterval(3);

	glewExperimental = GLEW_OK;
	if(glewInit() != GLEW_OK)
		sys_error("mainWin: glewInit error");

	GLCALL( glViewport(0, 0, MW_Width, MW_Height) );

	std::cout << glGetString(GL_VERSION) << "  "
			  << glGetString(GL_RENDERER) << std::endl;
	int maxVerAttrib;
	GLCALL( glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVerAttrib) );
	std::cout << "Max nr of vertex attributes: " << maxVerAttrib << std::endl;

	{
		/* float vertex[] = { */
		/* 	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, */
		/* 	 0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, */
		/* 	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, */
		/* 	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f */
		/* }; */

		float vertex[] = {
			-0.6f, -0.8f, 0.0f,  0.0f, 0.0f, 1.0f,
			-0.3f,  0.8f, 0.0f,  0.7f, 0.0f, 0.0f,
			-0.3f, -0.8f, 0.0f,  0.0f, 0.6f, 0.0f,
			-0.6f,  0.8f, 0.0f,  0.0f, 0.7f, 0.0f,

			 0.3f, -0.8f, 0.0f,  0.6f, 0.0f, 0.0f,
			 0.6f,  0.8f, 0.0f,  0.0f, 1.0f, 0.0f,
			 0.3f,  0.8f, 0.0f,  0.5f, 0.0f, 0.0f,
			 0.6f, -0.8f, 0.0f,  0.0f, 0.0f, 0.8f,

			-0.3f,  0.15f, 0.0f,  0.0f, 0.0f, 1.0f,
			 0.3f, -0.15f, 0.0f,  1.0f, 0.0f, 0.0f,
			-0.3f, -0.15f, 0.0f,  0.0f, 0.7f, 0.0f,
			 0.3f,  0.15f, 0.0f,  0.0f, 0.8f, 0.0f
		};

		/* uint32 index[] = { */
		/* 	0, 1, 2, */
		/* 	0, 1, 3, */
		/* }; */

		uint32 index[] = {
			0, 1, 2,
			0, 1, 3,
			4, 5, 6,
			4, 5, 7,
			8, 9, 10,
			8, 9, 11
		};

		uint32 vao;
		GLCALL( glGenVertexArrays(1, &vao) );
		GLCALL( glBindVertexArray(vao) );

		uint32 vbo;
		GLCALL( glGenBuffers(1, &vbo) );
		GLCALL( glBindBuffer(GL_ARRAY_BUFFER, vbo) );
		GLCALL( glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex,
							 GL_STATIC_DRAW) );

		uint32 index_count = sizeof index / sizeof(uint32);
		uint32 ebo;
		GLCALL( glGenBuffers(1, &ebo) );
		GLCALL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo) );
		GLCALL( glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof index, index,
							 GL_STATIC_DRAW) );

#ifdef _WIN32
		Shader program("../shader/shader.glsl");
#else
		Shader program("../shader/shader.glsl");
#endif

		GLCALL( glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
									  (void *)0) );
		GLCALL( glEnableVertexAttribArray(0) );

		GLCALL( glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
									  (void *)(3 * sizeof(float))) );
		GLCALL( glEnableVertexAttribArray(1) );

		/* float timeValue, redValue, greenValue; */
		float x = 1.0f, y = 1.0f, z = 0.0f;
		while(!glfwWindowShouldClose(win))
		{
			GLCALL( glClearColor(0.15f, 0.2f, 0.18f, 1.0f) );
			GLCALL( glClear(GL_COLOR_BUFFER_BIT) );

			/* timeValue = static_cast<double>(glfwGetTime()); */
			/* redValue = sin(timeValue) / 1.5f + 0.3f; */
			/* greenValue = sin(timeValue) / 2.0f + 0.7f; */

			/* program.SetUniform4f("UniformColor", redValue, greenValue, 0.5f, 1.0f); */
			x += x_change; y += y_change;
			program.SetUniform3f("newSize", x, y, z);

			/* program.Bind(); */
			GLCALL( glBindVertexArray(vao) );

			GLCALL( glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0) );

			GLCALL( glBindVertexArray(0) )

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

