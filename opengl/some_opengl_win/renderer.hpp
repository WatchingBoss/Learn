#ifndef RENDERER_H
#define RENDERER_H

#include <signal.h>
#include <GL/glew.h>

#ifdef _MSC_VER
#define DEBUG_BREAK __debugbreak()
#else
#define DEBUG_BREAK raise(SIGABRT)
#endif

/* Error handle macros */
#define ASSERT(x)\
	if(!(x))\
		DEBUG_BREAK;
#define GLCALL(x)\
	gl_clear_error();\
	x;\
	ASSERT(gl_log_call(#x, __FILE__, __LINE__))
/* END Error handle macros */

/* START Error handles */
extern void gl_clear_error();
extern bool gl_log_call(const char *func, const char *file, int line);
/* END Error handles */

#endif
