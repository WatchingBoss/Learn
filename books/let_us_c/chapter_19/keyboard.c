#include <windows.h>
#include "helper.h"

void OnDestroy(HWND);
void OnCreate(HWND);

HINSTANCE h;

int CALLBACK
WinMain(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR     lpCmdLine,
		int       nCmdShow)
{
	MSG m;

	InitInstance(hInstance, nCmdShow, "Keyboard");

	while(GetMessage(&m, NULL, 0, 0))
		DispatchMessage(&m);

	return(0);
}

LRESULT CALLBACK 
WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_DESTROY:
			OnDestroy(hWnd);
			break;
		case WM_CREATE:
			OnCreate(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return(0);
}

void
OnCreate(HWND hWnd)
{
	BOOL(CALLBACK *p)();

	h = LoadLibrary("hook.dll");
	if(h != NULL)
	{
		p = GetProcAddress(h, "installhook");
		(*p)(); // calls installhook()
	}
}

void
OnDestroy(HWND hWnd)
{
	BOOL(CALLBACK *p)();

	p = GetProcAddress(h, "removehook");
	(*p)(); // calls removehook()

	FreeLibrary(h);
	PostQuitMessage(0);
}
