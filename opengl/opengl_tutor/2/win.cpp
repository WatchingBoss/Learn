#include <iostream>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../common/common.cpp"
#include "../common/shader.cpp"

static const GLfloat g_vertex_buffer_data[] = {-1.0f, -1.0f, 0.0f,
											   1.0f, -1.0f, 0.0f,
											   0.0f, 1.0f, 0.0f};

int main()
{
	if(!glfwInit())
		sys_error("glfwInit error");

	call_glfwWindowHint();

	GLFWwindow *my_window = create_new_window(1024, 768, "First window");

	glfwMakeContextCurrent(my_window);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof g_vertex_buffer_data, g_vertex_buffer_data, GL_STATIC_DRAW);

	glewExperimental = true;
	if(glewInit() != GLEW_OK)
		sys_error("glewInit error");

	glfwSetInputMode(my_window, GLFW_STICKY_KEYS, GL_TRUE);

	GLuint programID = LoadShaders("simple_vertex_shader.vertexshader",
								   "simple_fragment_shader.fragmentshader");

	while(glfwGetKey(my_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(my_window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

		glUseProgram(programID);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(my_window);
		glfwPollEvents();
	}

	glfwDestroyWindow(my_window);
	glfwTerminate();
	return 1;
}
