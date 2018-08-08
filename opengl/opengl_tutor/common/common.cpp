#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void sys_error(const char *e)
{
	perror(e);
	glfwTerminate();
	exit(EXIT_FAILURE);
}

void call_glfwWindowHint()
{
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
}

GLFWwindow * create_new_window(int width = 640, int height = 480,
							   const char *title = "Default title",
							   GLFWmonitor *monitor = nullptr, GLFWwindow *share = nullptr)
{
	GLFWwindow *new_win = glfwCreateWindow(width, height, title, monitor, share);
	if(!new_win)
	{
		glfwDestroyWindow(new_win);
		sys_error("create_new_window: glfwCreateWindow error");
	}
	return new_win;
}
