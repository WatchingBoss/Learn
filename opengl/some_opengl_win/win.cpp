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
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "vendor/imgui/imgui_impl_glfw.h"

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

	switch(key)
	{
		case GLFW_KEY_UP:
			if(action == GLFW_PRESS)
				move_y = 0.1f;
			else if(action == GLFW_RELEASE)
				move_y = 0;
			break;
		case GLFW_KEY_DOWN:
			if(action == GLFW_PRESS)
				move_y = -0.1f;
			else if(action == GLFW_RELEASE)
				move_y = 0;
			break;
		case GLFW_KEY_RIGHT:
			if(action == GLFW_PRESS)
				move_x = 0.1f;
			else if(action == GLFW_RELEASE)
				move_x = 0;
			break;
		case GLFW_KEY_LEFT:
			if(action == GLFW_PRESS)
				move_x = -0.1f;
			else if(action == GLFW_RELEASE)
				move_x = 0;
			break;
	}
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

    glfwSwapInterval(3);

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

		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(win, true);
		ImGui_ImplOpenGL3_Init();
		ImGui::StyleColorsDark();

		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		float colors[] = {0.0f, 0.0f, 0.0f}, interval[] = {0.2f, 0.4f, 0.6f};
		float move_model[] = {0, 0};
		int x_move = 10, y_move = 10; bool toRight = false, toUp = true;
		while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			   !glfwWindowShouldClose(win))
		{
			rend.Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

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

			glfwSetKeyCallback(win, key_callback);

			move_model[0] += move_x;
			move_model[1] += move_y;

			glm::mat4 model = glm::translate(glm::mat4(1.0f),
											 glm::vec3(move_model[0],
													   move_model[1], 0));
			glm::mat4 mvp = proj * model;
			shader.SetUniformMat4f("u_MVP", mvp);

			{
				static flaot f = 0.0f;
				static int counter = 0;

				ImGui::Text("Hello, world!");
				ImGui::Checkbox("Demo Window", &show_demo_window);
				ImGui::Checkbox("Another Window", &show_another_window);

				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
// Edit 3 floats representing a color
				ImGui::ColorEdit3("clear color", (float*)&clear_color);
// Edit bools storing our windows open/close state
				ImGui::Checkbox("Demo Window", &show_demo_window);
				ImGui::Checkbox("Another Window", &show_another_window);
// Buttons return true when clicked (NB: most widgets return true when
// edited/activated)
				if (ImGui::Button("Button"))
					counter++;
				ImGui::SameLine();
				ImGui::Text("counter = %d", counter);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
							1000.0f / ImGui::GetIO().Framerate,
							ImGui::GetIO().Framerate);
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(win);

			glfwPollEvents();
		}
    }

	ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

	glfwDestroyWindow(win);
    glfwTerminate();
}

int main()
{
    srand(static_cast<uint32>(time(NULL)));
    mainWin();

    return 1;
}
