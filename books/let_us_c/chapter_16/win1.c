#include <windows.h>

void
msg()
{
	MessageBox(0, "Hello World!", "Title", MB_ICONINFORMATION);
}


int CALLBACK
WinMain( HINSTANCE hInstance,
		 HINSTANCE hPrevInstance,
		 LPSTR     lpCmdLine,
		 int       nCmdShow)
{
	msg();

	return(0);
}

/*

HINSTANCE and LPSTR are typedefs

HINSTANCE - unsigned int

LPSTR     - pointer to a char

*/
