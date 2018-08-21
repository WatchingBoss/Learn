#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "rend_sup.hpp"
#include "renderer.hpp"
#include "buffer.hpp"
#include "shader.hpp"
#include "texture.hpp"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

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

static float move_x = 0, move_y = 0;
static void key_callback(GLFWwindow *win,
						 int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_UP && action == GLFW_PRESS)
		move_y = 0.1f;
	else if(key == GLFW_KEY_UP && action == GLFW_RELEASE)
		move_y = 0;
	if(key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		move_y = -0.1f;
	else if(key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
		move_y = 0;
	if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		move_x = 0.1f;
	else if(key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
		move_x = 0;
	if(key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		move_x = -0.1f;
	else if(key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
		move_x = 0;
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
		float vertex_position[] = { -0.5f, -0.5f, 0.0f, 0.0f,
									 0.5f, -0.5f, 1.0f, 0.0f,
									 0.5f,  0.5f, 1.0f, 1.0f,
									-0.5f,  0.5f, 0.0f, 1.0f };
		uint32 indices[] = { 0, 1, 2,
							 2, 3, 0 };

		GLCALL( glEnable(GL_BLEND) );
		GLCALL( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

		uint32 vao;
		GLCALL( glGenVertexArrays(1, &vao) );
		GLCALL( glBindVertexArray(vao) );

		VertexArray va;
		VertexBuffer vb(vertex_position, sizeof vertex_position);

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, sizeof indices / sizeof(float));

		glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		glm::mat4 mvp = proj * view * model;

		Shader shader("shader/Shader.shader");
		shader.Bind();
		shader.SetUniform4f("u_color", 0.2235f, 1.0f, 0.8f, 1.0f);
		shader.SetUniformMat4f("u_MVP", mvp);

		Texture tex("img/tree.png");
		tex.Bind();
		shader.SetUniformi("u_texture", 0);

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();

		Renderer rend;

		float colors[] = {0.0f, 0.0f, 0.0f}, interval[] = {0.2f, 0.4f, 0.6f};
		float move_model[] = {0, 0};
		int x_move = 10, y_move = 10; bool toRight = false, toUp = true;
		while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			   !glfwWindowShouldClose(win))
		{
			rend.Clear();

			shader.Bind();
			shader.SetUniform4f("u_color", colors[0], colors[1], colors[2], 1.0f);

			rend.Draw(va, ib, shader);

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

			/* if(toUp) */
			/* { */
			/* 	move_model[1] -= 0.1f; */
			/* 	--y_move; */
			/* 	if(y_move == 0) */
			/* 		toUp = false; */
			/* } */
			/* else */
			/* { */
			/* 	move_model[1] += 0.1f; */
			/* 	++y_move; */
			/* 	if(y_move == 10) */
			/* 		toUp = true; */
			/* } */
			/* if(toRight) */
			/* { */
			/* 	move_model[0] += 0.1f; */
			/* 	++x_move; */
			/* 	if(x_move == 20) */
			/* 		toRight = false; */
			/* } */
			/* else */
			/* { */
			/* 	move_model[0] -= 0.1f; */
			/* 	--x_move; */
			/* 	if(x_move == 0) */
			/* 		toRight = true; */
			/* } */

			glfwSetKeyCallback(win, key_callback);

			move_model[0] += move_x;
			move_model[1] += move_y;

			glm::mat4 model = glm::translate(glm::mat4(1.0f),
											 glm::vec3(move_model[0],
													   move_model[1], 0));
			glm::mat4 mvp = proj * model;
			shader.SetUniformMat4f("u_MVP", mvp);

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
