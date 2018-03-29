#include <windows.h>
#include "helper.h"

void OnPaint(HWND);
void OnDestroy(HWND);

int CALLBACK
WinMain(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR     lpCmdLine,
		int       nCmdShow)
{
	MSG m;

	InitInstance(hInstance, nCmdShow, "Different types of pens");

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
		case WM_PAINT:
			OnPaint(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return(0);
}

void
OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
}

void
OnPaint(HWND hWnd)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hpen;
	HGDIOBJ holdpen;

	hdc = BeginPaint(hWnd, &ps);

// first
	hpen = CreatePen(PS_DASH, 1, RGB(255, 0, 0));
	holdpen = SelectObject(hdc, hpen);

	MoveToEx(hdc, 10, 10, NULL);
	LineTo(hdc, 500, 10);

	SelectObject(hdc, holdpen);
	DeleteObject(hpen);
// second
	hpen = CreatePen(PS_DOT, 1, RGB(80, 150, 50));
	holdpen = SelectObject(hdc, hpen);

	MoveToEx(hdc, 10, 60, NULL);
	LineTo(hdc, 500, 60);

	SelectObject(hdc, holdpen);
	DeleteObject(hpen);
// third
	hpen = CreatePen(PS_DASHDOT, 1, RGB(255, 143, 214));
	holdpen = SelectObject(hdc, hpen);

	MoveToEx(hdc, 10, 110, NULL);
	LineTo(hdc, 500, 110);

	SelectObject(hdc, holdpen);
	DeleteObject(hpen);
// fourth
	hpen = CreatePen(PS_DASHDOTDOT, 1, RGB(23, 214, 124));
	holdpen = SelectObject(hdc, hpen);

	MoveToEx(hdc, 10, 160, NULL);
	LineTo(hdc, 500, 160);

	SelectObject(hdc, holdpen);
	DeleteObject(hpen);
// fifth
	hpen = CreatePen(PS_SOLID, 5, RGB(89, 40, 231));
	holdpen = SelectObject(hdc, hpen);

	MoveToEx(hdc, 10, 210, NULL);
	LineTo(hdc, 500, 210);

	SelectObject(hdc, holdpen);
	DeleteObject(hpen);

	EndPaint(hWnd, &ps);
}

