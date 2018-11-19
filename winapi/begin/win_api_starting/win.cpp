#include <iostream>

#include <windows.h>

// Main window dimantions
constexpr int MW_WIDHT  = 640;
constexpr int MW_HEIGHT = 480;

LPCSTR my_class_name = "my_win_class";

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
	wc.lpszClassName = my_class_name;
	wc.hIconSm       = LoadIcon( NULL, IDI_APPLICATION );

	if ( !RegisterClassEx( &wc ) ) {
		MessageBox( NULL, "Failed RegisterClassEx", "Error", MB_ICONEXCLAMATION | MB_OK );
		std::exit( EXIT_FAILURE );
	}

	return wc;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow ) {
	// Create window class
	WNDCLASSEX wc = myCreateWindowClass( hInstance );

	// Create window
	HWND hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, my_class_name, "Window name",
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
	while ( GetMessage( &msg, NULL, NULL, NULL ) ) {
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	return static_cast<int>( msg.wParam );
}
