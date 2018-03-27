#include <windows.h>
#include "helper.h"

//void OnDestroy(HWND);

int CALLBACK
WinMain(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR     lpCmdLine,
		int       nCmdShow)
{
	MSG m;

	// perform application initialization
	InitInstance(hInstance, nCmdShow, "Window title");

	// message loop
	while(GetMessage(&m, 0, 0, 0))
		DispatchMessage(&m);

	return(0);
}

LRESULT CALLBACK
WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_DESTROY:
		{
//			OnDestroy (hWnd);
			PostQuitMessage(0);
			} break;
		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		} break;
	}
	return(0);
}
/*
void
OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
}
*/
