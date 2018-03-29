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
	HBRUSH hbr;
	HGDIOBJ holdbr;
	HBITMAP hbmp;

	hdc = BeginPaint(hWnd, &ps);
// first
	hbr = CreateSolidBrush(RGB(110, 220, 75));
	holdbr = SelectObject(hdc, hbr);

	Rectangle(hdc, 5, 5, 105, 100);

	SelectObject(hdc, holdbr);
	DeleteObject(hbr);

// secons
	hbr = CreateHatchBrush(HS_CROSS, RGB(49, 114, 214));
	holdbr = SelectObject(hdc, hbr);

	Rectangle(hdc, 125, 5, 225, 100);

	SelectObject(hdc, holdbr);
	DeleteObject(hbr);

// third
/*	hbmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));

	hbr = CreatePatternBrush(hbmp);
	holdbr = SelectObject(hdc, hbr);

	Rectangle(hdc, 245, 5, 345, 100);

	SelectObject(hdc, holdbr);
	DeleteObject(hbr);
	DeleteObject(hbmp);
*/
	EndPaint(hWnd, &ps);

	DeleteObject(hbr);
}
