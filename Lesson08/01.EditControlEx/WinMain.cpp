#include <Windows.h>
#include <windowsx.h>
#include "resource.h"

INT_PTR WINAPI DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdOpt, int nShowOpt)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}


INT_PTR WINAPI DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:		
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{		
		case IDOK:
		case IDCANCEL:
			SendMessage(hDlg, WM_CLOSE, NULL, NULL);
			return TRUE;
		default:
			return FALSE;
		}
		return TRUE;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}