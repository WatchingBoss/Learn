#define GLEW_STATIC

#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../inc/sup.hpp"
#include "../inc/glfw.hpp"
#include "../inc/shader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define MW_Width 1024
#define MW_Height 720

static void framebuffer_size_callback(GLFWwindow *win, int width, int height)
{
	glViewport(0, 0, width, height);
	(void)win;
}

float x_change = 0.0f, y_change = 0.0f, r_change = 0.0f,
	x_pos_change = 0.0f, y_pos_change = 0.0f;
static void key_callback(GLFWwindow *win, int key, int scancode, int action,
						 int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{		
		glfwSetWindowShouldClose(win, true);
		return;
	}

	float changing = 0.02f, r_changing = 5.0f, pos_changing = 0.03f;
	switch(key)
	{
	  case GLFW_KEY_UP:
		  if(action == GLFW_PRESS)
			  y_change += changing;
		  else if(action == GLFW_RELEASE)
			  y_change = 0.0f;
		  break;
	  case GLFW_KEY_DOWN:
		  if(action == GLFW_PRESS)
			  y_change -= changing;
		  else if(action == GLFW_RELEASE)
			  y_change = 0.0f;
		  break;
	  case GLFW_KEY_RIGHT:
		  if(action == GLFW_PRESS)
			  x_change += changing;
		  else if(action == GLFW_RELEASE)
			  x_change = 0.0f;
		  break;
	  case GLFW_KEY_LEFT:
		  if(action == GLFW_PRESS)
			  x_change -= changing;
		  else if(action == GLFW_RELEASE)
			  x_change = 0.0f;
		  break;

	  case GLFW_KEY_W:
		  if(action == GLFW_PRESS)
			  y_pos_change += pos_changing;
		  else if(action == GLFW_RELEASE)
			  y_pos_change = 0.0f;
		  break;
	  case GLFW_KEY_S:
		  if(action == GLFW_PRESS)
			  y_pos_change -= pos_changing;
		  else if(action == GLFW_RELEASE)
			  y_pos_change = 0.0f;
		  break;
	  case GLFW_KEY_D:
		  if(action == GLFW_PRESS)
			  x_pos_change += pos_changing;
		  else if(action == GLFW_RELEASE)
			  x_pos_change = 0.0f;
		  break;
	  case GLFW_KEY_A:
		  if(action == GLFW_PRESS)
			  x_pos_change -= pos_changing;
		  else if(action == GLFW_RELEASE)
			  x_pos_change = 0.0f;
		  break;

	  case GLFW_KEY_Q:
		  if(action == GLFW_PRESS)
			  r_change -= r_changing;
		  else if(action == GLFW_RELEASE)
			  r_change = 0.0f;
		  break;
	  case GLFW_KEY_E:
		  if(action == GLFW_PRESS)
			  r_change += r_changing;
		  else if(action == GLFW_RELEASE)
			  r_change = 0.0f;
		  break;
	}

	(void)scancode;
	(void)mods;
}

static void mainWin()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if(!glfwInit())
		sys_error("mainWin: glfwInit error");

	GLFWwindow *win = create_new_window(MW_Width, MW_Height, "Main window",
										nullptr, nullptr);

	glfwMakeContextCurrent(win);
	glfwSwapInterval(3);

	glewExperimental = GLEW_OK;
	if(glewInit() != GLEW_OK)
		sys_error("mainWin: glewInit error");

	GLCALL( glViewport(0, 0, MW_Width, MW_Height) );

	std::cout << glGetString(GL_VERSION) << "  "
			  << glGetString(GL_RENDERER) << std::endl;
	int maxVerAttrib;
	GLCALL( glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVerAttrib) );
	std::cout << "Max nr of vertex attributes: " << maxVerAttrib << std::endl;

	{
		GLCALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
								GL_MIRRORED_REPEAT) );
		GLCALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
								GL_MIRRORED_REPEAT) );
		GLCALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
								GL_LINEAR) );
		GLCALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );

		/* Load texture */
		stbi_set_flip_vertically_on_load(true);
		int t_width, t_height, nrChannels;
		/* First texture */
		uchar *t_data = stbi_load("../media/wood.jpg",
								  &t_width, &t_height, &nrChannels, 0);
		uint32 texture1;
		GLCALL( glGenTextures(1, &texture1) );
		GLCALL( glBindTexture(GL_TEXTURE_2D, texture1) );
		if(t_data)
		{			
			GLCALL( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_width, t_height, 0,
								 GL_RGB, GL_UNSIGNED_BYTE, t_data) );
			GLCALL( glGenerateMipmap(GL_TEXTURE_2D) );
		}
		else
			sys_error("Failed to load texture");
		stbi_image_free(t_data);
		/* Second texture */
		t_data = stbi_load("../media/diamond.png",
								  &t_width, &t_height, &nrChannels, 0);
		uint32 texture2;
		GLCALL( glGenTextures(1, &texture2) );
		GLCALL( glBindTexture(GL_TEXTURE_2D, texture2) );
		if(t_data)
		{			
			GLCALL( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_width, t_height, 0,
								 GL_RGBA, GL_UNSIGNED_BYTE, t_data) );
			GLCALL( glGenerateMipmap(GL_TEXTURE_2D) );
		}
		else
			sys_error("Failed to load texture");
		stbi_image_free(t_data);
		

		float vertex[] = {
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f
		};

		uint32 index[] = {
			0, 1, 2,
			0, 1, 3
		};

		uint32 vao;
		GLCALL( glGenVertexArrays(1, &vao) );
		GLCALL( glBindVertexArray(vao) );

		uint32 vbo;
		GLCALL( glGenBuffers(1, &vbo) );
		GLCALL( glBindBuffer(GL_ARRAY_BUFFER, vbo) );
		GLCALL( glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex,
							 GL_STATIC_DRAW) );

		uint32 index_count = sizeof index / sizeof(uint32);
		uint32 ebo;
		GLCALL( glGenBuffers(1, &ebo) );
		GLCALL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo) );
		GLCALL( glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof index, index,
							 GL_STATIC_DRAW) );

		Shader program("../shader/vertex.vert", "../shader/fragment.frag");

		GLCALL( glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
									  (void *)0) );
		GLCALL( glEnableVertexAttribArray(0) );

		GLCALL( glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
									  (void *)(3 * sizeof(float))) );
		GLCALL( glEnableVertexAttribArray(1) );
		GLCALL( glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
									  (void *)(6 * sizeof(float))) );
		GLCALL( glEnableVertexAttribArray(2) );

		program.SetUniform1i("ourTexture1", 0);
		program.SetUniform1i("ourTexture2", 1);

		float x = 1.0f, y = 1.0f, z = 1.0f, rotation = 0.0f, pos[3] = {0.0f};

		while(!glfwWindowShouldClose(win))
		{
			GLCALL( glClearColor(0.15f, 0.2f, 0.18f, 1.0f) );
			GLCALL( glClear(GL_COLOR_BUFFER_BIT) );

			x += x_change; y += y_change; rotation -= r_change;
			pos[0] += x_pos_change; pos[1] += y_pos_change;

			glm::mat4 trans(1.0f);
			trans = glm::rotate(trans, glm::radians(rotation),
								glm::vec3(0, 0, 1.0f));
			trans = glm::scale(trans, glm::vec3(x, y, z));
			trans = glm::translate(trans, glm::vec3(pos[0], pos[1], pos[2]));
			program.SetUniformMatrix4fv("transform", 1, GL_FALSE,
										glm::value_ptr(trans));

			GLCALL( glActiveTexture(GL_TEXTURE0) );
			GLCALL( glBindTexture(GL_TEXTURE_2D, texture1) );
			GLCALL( glActiveTexture(GL_TEXTURE1) );
			GLCALL( glBindTexture(GL_TEXTURE_2D, texture2) );

			GLCALL( glBindVertexArray(vao) );

			GLCALL( glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0) );

			GLCALL( glBindVertexArray(0) )

			glfwSetKeyCallback(win, key_callback);

			glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);

			glfwSwapBuffers(win);
			glfwPollEvents();
		}
	}

	glfwDestroyWindow(win);
    glfwTerminate();
}

int main()
{
	mainWin();

	return 0;
}

