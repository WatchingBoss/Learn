#include "../inc/glfw.hpp"
#include "../inc/sup.hpp"

GLFWwindow * create_new_window(int width, int height, const char *title,
							   GLFWmonitor *monitor, GLFWwindow *share)
{
	GLFWwindow *new_win = glfwCreateWindow(width, height, title, monitor, share);
	if(!new_win)
	{
		glfwDestroyWindow(new_win);
		sys_error("create_new_window: glfwCreatewindow error");
	}
	return new_win;
}
