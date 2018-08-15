#include "renderer.hpp"

#include <iostream>

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
