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
#include "shader.hpp"

void sys_error(const char *e)
{
    glfwTerminate();

    perror(e);
    exit(EXIT_FAILURE);
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

		VertexArray va;
		VertexBuffer vb(vertex_position, sizeof vertex_position);

		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		uint32 numberIndices = sizeof indices / sizeof(float);
		IndexBuffer ib(indices, numberIndices);
		
		Shader shader("shader/Shader.shader");
		shader.Bind();
		shader.SetUniform4f("u_color", 0.2235f, 1.0f, 0.8f, 1.0f);

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();

		float colors[] = {0.0f, 0.0f, 0.0f}, interval[] = {0.2f, 0.4f, 0.6f};
		while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			   !glfwWindowShouldClose(win))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			shader.Bind();
			shader.SetUniform4f("u_color", colors[0], colors[1], colors[2], 1.0f);

			va.Bind();
			ib.Bind();

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
    }
    glfwTerminate();
}

int main()
{
    srand(static_cast<uint32>(time(NULL)));
    mainWin();

    return 1;
}
