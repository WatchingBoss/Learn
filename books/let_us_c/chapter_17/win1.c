#include <windows.h>

void
create(nCmdShow)
{
	HWND h;
	h = CreateWindow("BUTTON", "Hit Me", WS_OVERLAPPEDWINDOW,
					 50, 50, 300, 200, 0, 0, 0, 0);
	ShowWindow(h, nCmdShow);
	MessageBox(0, "Hi!", "Waiting", MB_OK);
}

void
several()
{
	HWND h[10];
	int x;

	for(x = 0; x <= 9; x++)
	{
		h[x] = CreateWindow("BUTTON", "Prss ME", WS_OVERLAPPEDWINDOW,
							x*50, x*50, 200, 150, 0, 0, 0, 0);
		ShowWindow(h[x], 1);
	}

	MessageBox(0, "Hi!", "Waiting", 0);
}

int CALLBACK
WinMain(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR     lpCmdLine,
		int       nCmdShow)
{
	several();

	return(0);
}
