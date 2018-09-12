#define GLEW_STATIC

#include <iostream>
#include <string>

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

static const uint32 MW_Width = 1024;
static const uint32 MW_Height = 720;

void set_texture_parameters()
{
	GLCALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
							GL_MIRRORED_REPEAT) );
	GLCALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
							GL_MIRRORED_REPEAT) );
	GLCALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
							GL_LINEAR) );
	GLCALL( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
}

static void framebuffer_size_callback(GLFWwindow *win, int width, int height)
{
	glViewport(0, 0, width, height);
	(void)win;
}

static float x_size_change = 0, y_size_change = 0, z_size_change = 0,
	x_pos_change = 0, y_pos_change = 0, z_pos_change = 0,
	x_r_change = 0, y_r_change = 0, z_r_change = 0;

static void key_callback(GLFWwindow *win, int key, int scancode, int action,
						 int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{		
		glfwSetWindowShouldClose(win, true);
		return;
	}

	float changing = 0.04f, r_changing = 5.0f, pos_changing = 0.5f;
	switch(key)
	{
	  case GLFW_KEY_UP:
		  if(action == GLFW_PRESS)
			  if(glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				  if(glfwGetKey(win, GLFW_KEY_Z) == GLFW_PRESS)
					  z_pos_change += pos_changing;
				  else
					  y_pos_change += pos_changing;
			  else if(glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
				  x_r_change += r_changing;
			  else
				  if(glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
					  z_size_change += changing;
				  else
					  y_size_change += changing;
		  break;
	  case GLFW_KEY_DOWN:
		  if(action == GLFW_PRESS)
			  if(glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				  if(glfwGetKey(win, GLFW_KEY_Z) == GLFW_PRESS)
					  z_pos_change -= pos_changing;
				  else
					  y_pos_change -= pos_changing;
			  else if(glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
				  x_r_change -= r_changing;
			  else
				  if(glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
					  z_size_change -= changing;
				  else
					  y_size_change -= changing;
		  break;
	  case GLFW_KEY_RIGHT:
		  if(action == GLFW_PRESS)
			  if(glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				  x_pos_change += pos_changing;
			  else if(glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
				  y_r_change -= r_changing;
			  else
				  x_size_change += changing;
		  break;
	  case GLFW_KEY_LEFT:
		  if(action == GLFW_PRESS)
			  if(glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				  x_pos_change -= pos_changing;
			  else if(glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
				  y_r_change += r_changing;
			  else
				  x_size_change -= changing;
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
		x_pos_change = 0; y_pos_change = 0; z_pos_change = 0;
		x_r_change = 0; y_r_change = 0; z_r_change = 0;
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

	GLCALL( glEnable(GL_DEPTH_TEST) );

	GLCALL( glViewport(0, 0, MW_Width, MW_Height) );

	std::cout << glGetString(GL_VERSION) << "  "
			  << glGetString(GL_RENDERER) << std::endl;
	int maxVerAttrib;
	GLCALL( glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVerAttrib) );
	std::cout << "Max nr of vertex attributes: " << maxVerAttrib << std::endl;

	{
		/* Load textures */
		stbi_set_flip_vertically_on_load(true);
		int t_width, t_height, nrChannels;
		/* First texture */
		uchar *t_data = stbi_load("../media/wood.jpg",
								  &t_width, &t_height, &nrChannels, 0);
		uint32 texture1;
		GLCALL( glGenTextures(1, &texture1) );
		GLCALL( glBindTexture(GL_TEXTURE_2D, texture1) );
		set_texture_parameters();
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
		set_texture_parameters();
		if(t_data)
		{			
			GLCALL( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_width, t_height, 0,
								 GL_RGBA, GL_UNSIGNED_BYTE, t_data) );
			GLCALL( glGenerateMipmap(GL_TEXTURE_2D) );
		}
		else
			sys_error("Failed to load texture");
		stbi_image_free(t_data);
		/* END Load textures */

		/* float vertex[] = { */
		/* 	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, */
		/* 	 0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, */
		/* 	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, */
		/* 	-0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f */
		/* }; */

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

		/* uint32 index[] = { */
		/* 	0, 1, 2, */
		/* 	0, 1, 3 */
		/* }; */

		uint32 vao;
		GLCALL( glGenVertexArrays(1, &vao) );
		GLCALL( glBindVertexArray(vao) );

		uint32 vbo;
		GLCALL( glGenBuffers(1, &vbo) );
		GLCALL( glBindBuffer(GL_ARRAY_BUFFER, vbo) );
		GLCALL( glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex,
							 GL_STATIC_DRAW) );

		/* uint32 index_count = sizeof index / sizeof(uint32); */
		/* uint32 ebo; */
		/* GLCALL( glGenBuffers(1, &ebo) ); */
		/* GLCALL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo) ); */
		/* GLCALL( glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof index, index, */
		/* 					 GL_STATIC_DRAW) ); */

		Shader program("../shader/vertex.vert", "../shader/fragment.frag");

		/* GLCALL( glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), */
		/* 							  (void *)0) ); */
		/* GLCALL( glEnableVertexAttribArray(0) ); */

		/* GLCALL( glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), */
		/* 							  (void *)(3 * sizeof(float))) ); */
		/* GLCALL( glEnableVertexAttribArray(1) ); */
		/* GLCALL( glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), */
		/* 							  (void *)(6 * sizeof(float))) ); */
		/* GLCALL( glEnableVertexAttribArray(2) ); */

		GLCALL( glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
									  (void *)0) );
		GLCALL( glEnableVertexAttribArray(0) );
		GLCALL( glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
									  (void *)(3 * sizeof(float))) );
		GLCALL( glEnableVertexAttribArray(1) );

		program.Bind();
		program.SetUniform1i("ourTexture1", 0);
		program.SetUniform1i("ourTexture2", 1);
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(45.0f),
									  (float)MW_Width / (float)MW_Height,
									  0.1f, 100.0f);
		program.SetUniformMatrix4fv("projection", 1, GL_FALSE,
									glm::value_ptr(projection));
		program.Unbind();

		glm::vec3 cubePos[5] = {
			glm::vec3(-2.0f, -1.0f, 0),
			glm::vec3(-1.0f, -0.5f, 1.0f),
			glm::vec3(0, 1.0f, 0.5f),
			glm::vec3(1.0f, 1.7f, 0),
			glm::vec3(1.5f, 2.1f, 1.1f),
		};

		glm::vec3 size(1.f), pos(0, 0, -10.f);
		float rotation[3] = {30.f, 30.f, 0};

		while(!glfwWindowShouldClose(win))
		{
			glfwSetKeyCallback(win, key_callback);
			glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);

			GLCALL( glClearColor(0.15f, 0.2f, 0.18f, 1.0f) );
			GLCALL( glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) );

			GLCALL( glActiveTexture(GL_TEXTURE0) );
			GLCALL( glBindTexture(GL_TEXTURE_2D, texture1) );
			GLCALL( glActiveTexture(GL_TEXTURE1) );
			GLCALL( glBindTexture(GL_TEXTURE_2D, texture2) );

			size[0] += x_size_change; size[1] += y_size_change;
			size[2] += z_size_change;
			pos[0] += x_pos_change; pos[1] += y_pos_change; pos[2] += z_pos_change;
			rotation[0] += x_r_change; rotation[1] += y_r_change;
			rotation[2] += z_r_change;

			program.Bind();

			glm::mat4 view(1.0f);
			view = glm::translate(view, pos);
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

			/* GLCALL( glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0) ); */
			GLCALL( glBindVertexArray(0) )

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

