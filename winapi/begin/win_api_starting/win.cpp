#include <iostream>

#include <windows.h>

// Main window dimantions
constexpr int MW_WIDHT  = 640;
constexpr int MW_HEIGHT = 480;

LPCSTR MY_CLASS_NAME = "my_win_class";

static LRESULT CALLBACK myWinProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
	switch ( msg ) {
		case WM_CLOSE: DestroyWindow( hwnd ); break;
		case WM_DESTROY: PostQuitMessage( 0 ); break;
		default: return DefWindowProc( hwnd, msg, wParam, lParam );
	}
	return 0;
}

static WNDCLASSEX myCreateWindowClass( HINSTANCE hInstance ) {
	WNDCLASSEX wc;

	wc.cbSize        = sizeof( WNDCLASSEX );
	wc.style         = 0;
	wc.lpfnWndProc   = myWinProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon( NULL, IDI_APPLICATION );
	wc.hCursor       = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = MY_CLASS_NAME;
	wc.hIconSm       = LoadIcon( NULL, IDI_APPLICATION );

	if ( !RegisterClassExA( &wc ) ) {
		MessageBox( NULL, "Failed RegisterClassEx", "Error", MB_ICONEXCLAMATION | MB_OK );
		std::exit( EXIT_FAILURE );
	}

	return wc;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow ) {
	// Create window class
	WNDCLASSEX wc = myCreateWindowClass( hInstance );

	// Create window
	HWND hwnd = CreateWindowExA( WS_EX_CLIENTEDGE, MY_CLASS_NAME, "My window",
	                             WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
	                             MW_WIDHT, MW_HEIGHT, NULL, NULL, hInstance, NULL );
	if ( !hwnd ) {
		MessageBox( NULL, "Failed CreateWindowEx", "Error", MB_ICONEXCLAMATION | MB_OK );
		std::exit( EXIT_FAILURE );
	}

	ShowWindow( hwnd, nCmdShow );
	UpdateWindow( hwnd );

	// Message handling loop
	MSG msg;
	while ( GetMessageA( &msg, NULL, NULL, NULL ) ) {
		TranslateMessage( &msg );
		DispatchMessageA( &msg );
	}

	return static_cast<int>( msg.wParam );
}
