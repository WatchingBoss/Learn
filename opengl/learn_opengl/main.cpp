#define GLEW_STATIC

#include <cstdlib>
#include <csignal>

#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

typedef unsigned int uint32;
typedef unsigned char uchar;

#ifdef _MSC_VER
#define DEBUG_BREAK __debugbreak()
#else
#define DEBUG_BREAK raise(SIGABRT)
#endif

/* Error handle macros */
#define ASSERT(x)								\
	if(!(x))									\
		DEBUG_BREAK;
#define GLCALL(x)								\
	gl_clear_error();							\
	x;											\
	ASSERT(gl_log_call(#x, __FILE__, __LINE__))
/* END Error handle macros */

/* START Error handles */
extern void gl_clear_error();
extern bool gl_log_call(const char *func, const char *file, int line);
/* END Error handles */
/* Error handle */
void gl_clear_error()
{
	while(glGetError() != GL_NO_ERROR);
}

bool gl_log_call(const char *func, const char *file, int line)
{
	while(GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error <<  "): " << func << " "
				  << file << ": " << line << std::endl;
		return false;
	}
	return true;
}
/* END Error handle */

static void sys_error(const char *e)
{
	perror(e);
	glfwTerminate();
	exit(EXIT_FAILURE);
}

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

static void mainWin()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if(!glfwInit())
		sys_error("mainWin: glfwInit error");

	GLFWwindow *win = create_new_window(1024, 720, "Main window", nullptr, nullptr);

	glfwMakeContextCurrent(win);
	glfwSwapInterval(2);

	glewExperimental = GLEW_OK;
	if(glewInit() != GLEW_OK)
		sys_error("mainWin: glewInit error");

	std::cout << glGetString(GL_VERSION) << "  " << glGetString(GL_RENDERER) << std::endl;

	{
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(win, true);
		ImGui_ImplOpenGL3_Init();
		ImGui::StyleColorsDark();

		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		while(glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(win))
		{
			GLCALL(glClear(GL_COLOR_BUFFER_BIT));

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			{
				static float f = 0.0f;
				static int counter = 0;

				ImGui::Text("Hello, world!");
				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
				ImGui::ColorEdit3("clear color", (float*)&clear_color);

				ImGui::Checkbox("Demo Window", &show_demo_window);
				ImGui::Checkbox("Another Window", &show_another_window);

				if (ImGui::Button("Button"))
					++counter;
				ImGui::SameLine();
				ImGui::Text("counter = %d", counter);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
							1000.0f / ImGui::GetIO().Framerate,
							ImGui::GetIO().Framerate);

				static float prev = f;
				static ImVec4 prev_color = clear_color;
				if(prev != f)
				{
					std::cout << "Value of f: " << f << std::endl;
					prev = f;
				}
				if(prev_color.x != clear_color.x ||
				   prev_color.y != clear_color.y ||
				   prev_color.z != clear_color.z)
				{
					std::cout << "Current color: "
						<< "R: " << ((int)(255 * clear_color.x)) << "  "
						<< "G: " << ((int)(255 * clear_color.y)) << "  "
						<< "B: " << ((int)(255 * clear_color.z)) << std::endl;
				}
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
	mainWin();

	return 0;
}

