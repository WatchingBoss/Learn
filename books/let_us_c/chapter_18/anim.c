#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "helper.h"

void OnDestroy(HWND);
void OnCreate(HWND);
void OnTimer(HWND);

int x, y;
HDC hmemdc;
HGDIOBJ holdbr;
HBRUSH hbr;

int CALLBACK
WinMain(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR     lpCmdLine,
		int       nCmdShow)
{
	MSG m;

	InitInstance(hInstance, nCmdShow, "Hand drowing");

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
		case WM_TIMER:
			OnTimer(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return(0);
}

void
 OnCreate(HWND hWnd)
{
	RECT r;
	HDC hdc;

	hbr = CreateSolidBrush(RGB(234, 14, 15));
	hdc = GetDC(hWnd);
	hmemdc = CreateCompatibleDC(hdc);
	holdbr = SelectObject(hmemdc, hbr);

	ReleaseDC(hWnd, hdc);

	srand(time(NULL));

	GetClientRect(hWnd, &r);

	x = rand() % r.right - 22;
	y = rand() % r.bottom - 22;

	SetTimer(hWnd, 1, 50, NULL);
}

void
OnDestroy(HWND hWnd)
{
	KillTimer(hWnd, 1);
	SelectObject(hmemdc, holdbr);
	DeleteDC(hmemdc);
	DeleteObject(hbr);
	PostQuitMessage(0);
}

void 
OnTimer(HWND hWnd)
{
	HDC hdc;
	RECT r;
	const int wd = 22, ht = 22;
	static int dx = 10, dy = 10;

	hdc = GetDC(hWnd);
	BitBlt(hdc, x, y, wd, ht, hmemdc, 0, 0, WHITENESS);
	GetClientRect(hWnd, &r);

	x += dx;
	if (x < 0)
	{
		x = 0;
		dx = 10;
		PlaySound("chord.wav", NULL, SND_FILENAME|SND_ASYNC);
	}
	else if (x > (r.right - wd))
	{
		x = r.right - wd;
		dx = -10;
		PlaySound("chord.wav", NULL, SND_FILENAME|SND_ASYNC);		
	}

	y += dy;
	if (y < 0)
	{
		y = 0;
		dy = 10;
		PlaySound("chord.wav", NULL, SND_FILENAME|SND_ASYNC);
	}
	else if (y > (r.bottom - ht))
	{
		y = r.bottom - ht;
		dy = -10;
		PlaySound("chord.wav", NULL, SND_FILENAME|SND_ASYNC);		
	}

	BitBlt(hdc, x, y, wd, ht, hmemdc, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, hdc);
}
