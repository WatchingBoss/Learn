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

	InitInstance(hInstance, nCmdShow, "Text");

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
	HFONT hfont;
	LOGFONT f = {0};
	HGDIOBJ holdfont;
	char *fonts[] = {"Arial", "Times New Roman", "Comic Sans MS"};
	int i;

//	RECT rec;

	hdc = BeginPaint(hWnd, &ps);

	for (i = 0; i <= 2; i++)
	{
		strcpy(f.lfFaceName, fonts[i]); // copy font name
		f.lfHeight = 40 * (i + 1);     // font height
		f.lfItalic = 1;                // italic

		hfont = CreateFontIndirect(&f);
		holdfont = SelectObject(hdc, hfont);

		SetTextColor(hdc, RGB(0, 0, 255));

		TextOut(hdc, 10, 70 * i, "Hello Windows", 13);
/*		GetClientRect(hWnd, &rec);
		SetBkMode(hdc, TRANSPARENT);
		rec.left = 10;
		rec.top = 20 * (i + 1);
		DrawText(hdc, "Hello Windows", -1, &rec, DT_CALCRECT);
*/
		SelectObject(hdc, holdfont);
		DeleteObject(hfont);
	}

	EndPaint(hWnd, &ps);
}

