#include <cstdlib>
#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "linmath.h"

static void error_callback(int error, const char *desc)
{
	printf("code: %d\terror: %s\n", error, desc);
}

static void key_callback(GLFWwindow *win, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(win, GLFW_TRUE);
}

static void sys_error(const char *e)
{
	perror(e);
	glfwTerminate();
	exit(EXIT_FAILURE);
}

static GLFWwindow * create_new_window(int width = 640, int height = 480,
									  const char *title = "Default title",
									  GLFWmonitor *monitor = nullptr, GLFWwindow *share = nullptr)
{
	GLFWwindow *new_win = glfwCreateWindow(width, height, title, monitor, share);
	if(!new_win)
	{
		glfwDestroyWindow(new_win);
		sys_error("mainWin: glfwCreateWindow");
	}
	return new_win;
}

static const char* vertex_shader_text =
	"uniform mat4 MVP;\n"
	"attribute vec3 vCol;\n"
	"attribute vec2 vPos;\n"
	"varying vec3 color;\n"
	"void main()\n"
	"{\n"
	"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
	"    color = vCol;\n"
	"}\n";
static const char* fragment_shader_text =
	"varying vec3 color;\n"
	"void main()\n"
	"{\n"
	"    gl_FragColor = vec4(color, 1.0);\n"
	"}\n";

static struct vertex_color
{
	float x, y, r, g, b;
} vertices[3];

static void init_triangle_vertices()
{
	vertices[0] = { -0.6f, -0.4f, 1.f, 0.f, 0.f};
	vertices[1] = {  0.6f, -0.4f, 0.f, 1.f, 0.f};
	vertices[2] = {   0.f,  0.6f, 0.f, 0.f, 1.f};
}

static void mainWin()
{
	GLFWwindow *my_win;
	GLuint vertex_buffer, vertex_shader, fragment_shader, program;
	GLint mvp_location, vpos_location, vcol_location;

	glfwSetErrorCallback(error_callback);

	init_triangle_vertices();

	if(!glfwInit())
		sys_error("mainWin: glfwInit");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	my_win = create_new_window(640, 480, "My window");

	glfwSetKeyCallback(my_win, key_callback);

	glfwMakeContextCurrent(my_win);

	glfwSwapInterval(1);

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 5, (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 5, (void*) (sizeof(float) * 2));	

	float ratio;
	int width, height;
	mat4x4 m, p, mvp;
	while(!glfwWindowShouldClose(my_win))
	{
		glfwGetFramebufferSize(my_win, &width, &height);

		ratio = (float)width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		mat4x4_identity(m);
		mat4x4_rotate_Z(m, m, (float)glfwGetTime());
		mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		mat4x4_mul(mvp, p, m);

		glUseProgram(program);
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)mvp);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(my_win);
		glfwPollEvents();
	}

	glfwDestroyWindow(my_win);
	
	glfwTerminate();
}

int main()
{
	mainWin();

	return 0;
}

