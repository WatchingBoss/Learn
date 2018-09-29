#define GLEW_STATIC

#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../inc/sup.hpp"
#include "../inc/glfw.hpp"
#include "../inc/shader.hpp"
#include "../inc/texture.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

static const uint32 MW_Width = 1024;
static const uint32 MW_Height = 720;

extern void DrawCubes(uint32 &, Shader &, Texture &, Texture &, 
					  glm::vec3 &, glm::vec3 &, glm::vec3 &,
					  glm::vec3 &, float [], std::vector<glm::vec3> &);
extern void action(glm::vec3 &, float[], glm::vec3 &, glm::vec3 &, glm::vec3 &);

static void framebuffer_size_callback(GLFWwindow *win, int width, int height)
{
	glViewport(0, 0, width, height);
	(void)win;
}

static float x_size_change = 0, y_size_change = 0, z_size_change = 0,
	x_r_change = 0, y_r_change = 0, z_r_change = 0;
static bool pressA = false, pressD = false, pressS = false, pressW = false;

static void key_callback(GLFWwindow *win, int key, int scancode, int action,
						 int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{		
		glfwSetWindowShouldClose(win, true);
		return;
	}

	float changing = 0.04f, r_changing = 5.0f;
	switch(key)
	{
	  case GLFW_KEY_UP:
		  if(action == GLFW_PRESS)
			  if(glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
				  x_r_change = r_changing;
			  else
				  if(glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
					  z_size_change = changing;
				  else
					  y_size_change = changing;
		  break;
	  case GLFW_KEY_DOWN:
		  if(action == GLFW_PRESS)
			  if(glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
				  x_r_change = -r_changing;
			  else
				  if(glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
					  z_size_change = -changing;
				  else
					  y_size_change = -changing;
		  break;
	  case GLFW_KEY_RIGHT:
		  if(action == GLFW_PRESS)
			  if(glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
				  y_r_change = -r_changing;
			  else
				  x_size_change = changing;
		  break;
	  case GLFW_KEY_LEFT:
		  if(action == GLFW_PRESS)
			  if(glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
				  y_r_change = r_changing;
			  else
				  x_size_change = -changing;
		  break;

	  case GLFW_KEY_W:
		  if(action == GLFW_PRESS)        pressW = true;
		  else if(action == GLFW_RELEASE) pressW = false;
		  break;
	  case GLFW_KEY_S:
		  if(action == GLFW_PRESS)        pressS = true;
		  else if(action == GLFW_RELEASE) pressS = false;
		  break;
	  case GLFW_KEY_A:
		  if(action == GLFW_PRESS)        pressA = true;
		  else if(action == GLFW_RELEASE) pressA = false;
		  break;
	  case GLFW_KEY_D:
		  if(action == GLFW_PRESS)        pressD = true;
		  else if(action == GLFW_RELEASE) pressD = false;
		  break;

	  case GLFW_KEY_Q:
		  if(action == GLFW_PRESS)
			  z_r_change -= r_changing;
		  break;
	  case GLFW_KEY_E:
		  if(action == GLFW_PRESS)
			  z_r_change += r_changing;
		  break;
	}

	if( (key == GLFW_KEY_UP || key == GLFW_KEY_DOWN    ||
		 key == GLFW_KEY_RIGHT || key == GLFW_KEY_LEFT ||
		 key == GLFW_KEY_Q || key == GLFW_KEY_E)       &&
		action == GLFW_RELEASE )
	{
		x_size_change = 0; y_size_change = 0; z_size_change = 0;
		x_r_change = 0; y_r_change = 0; z_r_change = 0;
	}

	(void)scancode;
	(void)mods;
}

static float lastX = 400.f, lastY = 300.f, yaw = 1.f, pitch = 1.f;
static bool firstMouse = true;
static glm::vec3 front(1.f);
static void cursor_pos_callback(GLFWwindow *win, double xpos, double ypos)
{
	if(firstMouse)
	{
		lastX = static_cast<float>(xpos);
		lastY = static_cast<float>(ypos);
		firstMouse = false;
	}
	
	float xoffset = static_cast<float>(xpos) - lastX;
	float yoffset = lastY - static_cast<float>(ypos);
	lastX = static_cast<float>(xpos);
	lastY = static_cast<float>(ypos);

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw   += xoffset;
	pitch += yoffset;

	if(pitch >  89.f) pitch = 89.f;
	if(pitch < -89.f) pitch = -89.f;

	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
}

static float fov = 45.f;
static void scroll_callback(GLFWwindow *win, double xoffset, double yoffset)
{
	if(fov >= 1.f && fov <= 45.f) fov -= static_cast<float>(yoffset);
	if(fov <= 1.f)                fov = 1.f;
	if(fov >= 45.f)               fov = 45.f;
}

static void calls_to_glfw(GLFWwindow *win)
{
	glfwSetKeyCallback(win, key_callback);
	glfwSetCursorPosCallback(win, cursor_pos_callback);
	glfwSetScrollCallback(win, scroll_callback);
	glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
}

float deltaTime = 0.f, lastFrame = 0.f;

static void mainWin()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if(!glfwInit())
		sys_error("mainWin: glfwInit error");

	GLFWwindow *win = create_new_window(MW_Width, MW_Height, "Main window",
										nullptr, nullptr);

	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwMakeContextCurrent(win);
	glfwSwapInterval(3);

	glewExperimental = GLEW_OK;
	if(glewInit() != GLEW_OK)
		sys_error("mainWin: glewInit error");

	GLCALL( glEnable(GL_DEPTH_TEST) );

	GLCALL( glViewport(0, 0, MW_Width, MW_Height) );

	std::cout << glGetString(GL_VERSION) << "  "
			  << glGetString(GL_RENDERER) << std::endl;
	int maxVerAttrib;
	GLCALL( glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVerAttrib) );
	std::cout << "Max nr of vertex attributes: " << maxVerAttrib << std::endl;

	{
		Texture texture1("../media/wood.jpg", JPEG);
		Texture texture2("../media/diamond.png", PNG);

		float vertex[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		uint32 vao;
		GLCALL( glGenVertexArrays(1, &vao) );
		GLCALL( glBindVertexArray(vao) );

		uint32 vbo;
		GLCALL( glGenBuffers(1, &vbo) );
		GLCALL( glBindBuffer(GL_ARRAY_BUFFER, vbo) );
		GLCALL( glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex,
							 GL_STATIC_DRAW) );

		Shader program("../shader/vertex.vert", "../shader/fragment.frag");

		GLCALL( glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
									  (void *)0) );
		GLCALL( glEnableVertexAttribArray(0) );
		GLCALL( glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
									  (void *)(3 * sizeof(float))) );
		GLCALL( glEnableVertexAttribArray(1) );

		program.Bind();
		program.SetUniform1i("ourTexture1", 0);
		program.SetUniform1i("ourTexture2", 1);
		program.Unbind();

		std::vector<glm::vec3> cubePos = {
			glm::vec3(-1.f, -1.f, 0.f),
			glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(1.f, 1.5f, 1.5f),
			glm::vec3(2.f, 2.5f, 2.f),
			glm::vec3(2.5f, 1.f, 2.1f),
		};

		glm::vec3 size(1.f),
			camPos(0, 0, 2.f), camFront(0.f, 0.f, -1.f), camUp(0.f, 1.f, 0.f);
		float rotation[3] = {30.f, 30.f, 0};

		while(!glfwWindowShouldClose(win))
		{
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			calls_to_glfw(win);

			GLCALL( glClearColor(0.15f, 0.2f, 0.18f, 1.0f) );
			GLCALL( glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) );

			action(size, rotation, camPos, camFront, camUp);

			DrawCubes(vao, program, texture1, texture2, 
					  camPos, camFront, camUp, size, rotation, cubePos);

			glfwSwapBuffers(win);
			glfwPollEvents();
		}
	}

	glfwDestroyWindow(win);
    glfwTerminate();
}

static void
DrawCubes(uint32 &vao, Shader &program, Texture &tex1, Texture &tex2,
		  glm::vec3 &camPos, glm::vec3 &camFront, glm::vec3 &camUp,
		  glm::vec3 &size, float rotation[], std::vector<glm::vec3> &cubePos)
{
	tex1.Bind(0);
	tex2.Bind(1);

	program.Bind();

	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(fov),
								  (float)MW_Width / (float)MW_Height,
								  0.1f, 100.0f);
	program.SetUniformMatrix4fv("projection", 1, GL_FALSE,
								glm::value_ptr(projection));

	glm::mat4 view(1.0f);
	view = glm::lookAt(camPos, camPos + camFront, camUp);
	program.SetUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(view));

	GLCALL( glBindVertexArray(vao) );
	for(size_t i = 0; i < 5; ++i)
	{
		glm::mat4 model(1.0f);
		float c_t = static_cast<float>(glfwGetTime());
		model = glm::translate(model, cubePos[i]);
		model = glm::rotate(model, glm::radians(rotation[0]),
							glm::vec3(1.0f, 0, 0));
		model = glm::rotate(model, glm::radians(rotation[1]),
							glm::vec3(0, 1.0f, 0));
		model = glm::rotate(model, glm::radians(rotation[2]),
							glm::vec3(0, 0, 1.0f));
		model = glm::scale(model, size);

		program.SetUniformMatrix4fv("model", 1, GL_FALSE,
									glm::value_ptr(model));
		GLCALL( glDrawArrays(GL_TRIANGLES, 0, 36) );
	}
	program.Unbind();
	GLCALL( glBindVertexArray(0) );
}

static void action(glm::vec3 &size, float rotation[],
				   glm::vec3 &camPos, glm::vec3 &camFront, glm::vec3 &camUp)
{
	float camSpeed = 2.5f * deltaTime;

	camFront = glm::normalize(front);

	if(pressW && !pressS)
		camPos += camSpeed * camFront;
	else if(pressS)
		camPos -= camSpeed * camFront;
	if(pressA && !pressD)
		camPos -= glm::normalize(glm::cross(camFront, camUp)) * camSpeed;
	else if(pressD)
		camPos += glm::normalize(glm::cross(camFront, camUp)) * camSpeed;

	size[0] += x_size_change; size[1] += y_size_change;
	size[2] += z_size_change;
	rotation[0] += x_r_change; rotation[1] += y_r_change;
	rotation[2] += z_r_change;
}

int main()
{
	mainWin();

	return 0;
}

