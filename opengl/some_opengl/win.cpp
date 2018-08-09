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

# define STEP 2
void mainWin()
{
	if(!glfwInit())
		sys_error("mainWin: glfwInit error");

	GLFWwindow *win = create_new_window("My main window");

	glfwMakeContextCurrent(win);

	if(glewInit() != GLEW_OK)
		sys_error("mainWin: glewInit error");

	std::cout << glGetString(GL_VERSION) << std::endl;

#if STEP == 2
	float vertex_position[] = { -0.5f, -0.5f,
								 0.0f,  0.5f,
								 0.5f, -0.5f };
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertex_position, vertex_position, GL_STATIC_DRAW);
#endif

	while(glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(win))
	{
		glClear(GL_COLOR_BUFFER_BIT);

#if STEP == 2
		glDrawArrays(GL_TRIANGLES, 0, 3);
#endif

#if STEP == 1
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f( 0.0f,  0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();
#endif

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
