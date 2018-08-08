#include <iostream>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../common.cpp"

int main()
{
	if(!glfwInit())
		sys_error("glfwInit error");

	call_glfwWindowHint();

	GLFWwindow *my_window = create_new_window(1024, 768, "First window");

	glfwMakeContextCurrent(my_window);

	glewExperimental = true;
	if(glewInit() != GLEW_OK)
		sys_error("glewInit error");

	glfwSetInputMode(my_window, GLFW_STICKY_KEYS, GL_TRUE);

	while(glfwGetKey(my_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(my_window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(my_window);
		glfwPollEvents();
	}

	glfwDestroyWindow(my_window);
	glfwTerminate();
	return 1;
}
