#include <cstdio>
#include <cstdlib>

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

void mainWin()
{
	if(!glfwInit())
		sys_error("mainWin: glfwInit error");

	GLFWwindow *win = create_new_window("My main window");

	glfwMakeContextCurrent(win);

	if(glewInit() != GLEW_OK)
		sys_error("mainWin: glewInit error");

	std::cout << glGetString(GL_VERSION) << std::endl;
	
	while(glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(win))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f( 0.0f,  0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();

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
