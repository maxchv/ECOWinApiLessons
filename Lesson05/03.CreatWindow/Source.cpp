#include "resource.h"
#include <Windows.h>

BOOL CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszCmdOpt, int nShowOpt)
{
	int ret = DialogBox(hThisInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
	return ret;
}

HWND hStatic;
HWND hBtn;
HWND hEdit;

BOOL CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		hStatic = CreateWindow(TEXT("STATIC"),
			TEXT("Content"),
			WS_CHILD  | SS_CENTER | SS_CENTERIMAGE | WS_BORDER,
			10, 10,
			100, 80,
			hWnd, NULL, GetModuleHandle(0), NULL);
		ShowWindow(hStatic, SW_NORMAL);

		hBtn = CreateWindow(TEXT("BUTTON"),
			TEXT("Button"),
			WS_CHILD | WS_VISIBLE | BS_CENTER,
			120, 10,
			100, 80,
			hWnd, NULL, GetModuleHandle(0), NULL);

		hEdit = CreateWindow(TEXT("EDIT"),
			TEXT("Edit field"),
			WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL,
			250, 10,
			100, 80,
			hWnd, NULL, GetModuleHandle(0), NULL);
		return TRUE;
	case WM_COMMAND:
	{
		return FALSE;
	}	
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}