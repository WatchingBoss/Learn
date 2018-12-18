#include "resources.h"

#include <iostream>

#include <windows.h>

// Main window dimantions
constexpr int MW_WIDHT  = 640;
constexpr int MW_HEIGHT = 480;

constexpr char *MY_CLASS_NAME = "my_win_class";

extern WNDCLASSEX myCreateWindowClass( HINSTANCE );
extern HWND       myCreateMainWindow( HINSTANCE );
extern LRESULT CALLBACK myWinProc( HWND, UINT, WPARAM, LPARAM );

#define myInfoMsg( text, title ) \
	MessageBoxA( NULL, text, title, MB_OK | MB_ICONINFORMATION )

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow ) {
	// Create window class
	WNDCLASSEX wc = myCreateWindowClass( hInstance );

	// Create window
	HWND hwnd = myCreateMainWindow( hInstance );

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

static LRESULT CALLBACK myWinProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
	switch ( msg ) {
		case WM_COMMAND:
			switch ( LOWORD( wParam ) ) {
				case ID_FILE_EXIT: myInfoMsg( "File exit string", "You pressed" ); break;
				case ID_STUFF_GO: myInfoMsg( "File GO string", "You pressed" ); break;
			}
			break;
		case WM_CREATE: {
			HMENU hMenu = CreateMenu( );

			HMENU hSubMenu = CreatePopupMenu( );
			AppendMenu( hSubMenu, MF_STRING, ID_FILE_EXIT, "E&exit" );
			AppendMenu( hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File" );

			hSubMenu = CreatePopupMenu( );
			AppendMenu( hSubMenu, MF_STRING, ID_STUFF_GO, "&Go" );
			AppendMenu( hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Stuff" );

			SetMenu( hwnd, hMenu );

			HICON hIconBg = (HICON)LoadImageA( NULL, ICON_ARROW_UP, IMAGE_ICON, 32, 32,
			                                   LR_LOADFROMFILE );
			if ( hIconBg )
				SendMessageA( hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIconBg );
			else
				myInfoMsg( "Could not load big image", "Error" );

			HICON hIconSm = (HICON)LoadImageA( NULL, ICON_ARROW_UP, IMAGE_ICON, 16, 16,
			                                   LR_LOADFROMFILE );
			if ( hIconSm )
				SendMessageA( hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm );
			else
				myInfoMsg( "Could not load small image", "Error" );

		} break;
		case WM_LBUTTONDOWN:
			MessageBox( NULL, "You pressed left button", "Hello",
			            MB_OK | MB_ICONINFORMATION );
			break;
		case WM_RBUTTONDOWN: {
			char bufferFileName[MAX_PATH] = { 0 };
			GetModuleFileNameA( GetModuleHandleA( 0 ), bufferFileName, MAX_PATH );
			MessageBox( NULL, bufferFileName, "File name is",
			            MB_OK | MB_ICONINFORMATION );
		} break;
		case WM_CLOSE: DestroyWindow( hwnd ); break;
		case WM_DESTROY: PostQuitMessage( 0 ); break;
		default: return DefWindowProc( hwnd, msg, wParam, lParam );
	}
	return 0;
}

static WNDCLASSEX myCreateWindowClass( HINSTANCE hInstance ) {
	WNDCLASSEX wc = { 0 };

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

static HWND myCreateMainWindow( HINSTANCE hInstance ) {
	HWND hwnd = CreateWindowExA( WS_EX_CLIENTEDGE, MY_CLASS_NAME, "My window",
	                             WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
	                             MW_WIDHT, MW_HEIGHT, NULL, NULL, hInstance, NULL );
	if ( hwnd ) return hwnd;

	MessageBox( NULL, "Failed CreateWindowEx", "Error", MB_ICONEXCLAMATION | MB_OK );
	std::exit( EXIT_FAILURE );
}
