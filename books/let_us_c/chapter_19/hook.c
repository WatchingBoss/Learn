#include <windows.h>

static HHOOK hkb = NULL;
HANDLE h;

BOOL WINAPI
DLLMain(HANDLE hModule,
		DWORD ul_reason_for_call,
		LPVOID lpReserved)
{
	h = hModule;
	return(TRUE);
}

BOOL _declspec(dllexport) installhook()
{
	hkb = SetWindowsHookEx((WH_KEYBOARD,
							(HOOKPROC) KeyboardProc,
							(HINSTANCE) h, 0));
	if(hkb == NULL)
		return(FALSE);

	return(TRUE);
}

LRESULT 
_declspec(dllexport) CALLBACK KeyboardProc(int code,
										   WPARAM wParam,
										   LPARAM lParam)
{
	short int state;

	if(code < 0)
		return CallNextHookEx(hkb, code, wParam, lParam);

	if((code == HC_ACTION) && ((DWORD)lParam & 0x40000000))
	{
		state = GetKeyState(VK_CAPITAL);
		if((state & 1) == 0) // if off
		{
			keybd_event(VK_CAPITAL, 0, KEYEVENTF_EXTENDEDKEY, 0);
			keybd_event
(VK_CAPITAL, 0, KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP, 0);
		}
	}

	return CallNextHookEx(hkb, code, wParam, lParam);
}

BOOL _declspec(dllexport) removehook()
{
	return UnhookWindowsHookEx(hkb);
}
