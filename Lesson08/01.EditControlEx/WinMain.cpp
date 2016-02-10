#include <Windows.h>
#include <windowsx.h>
#include "resource.h"

INT_PTR WINAPI DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdOpt, int nShowOpt)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

HWND hEdit1;
HWND hEdit2;
HWND hPass;

INT_PTR WINAPI DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:		
	{
		hEdit1 = GetDlgItem(hDlg, IDC_EDIT1);
		hPass = GetDlgItem(hDlg, IDC_EDIT2);
		DWORD exStyle = GetWindowLong(hEdit1, GWL_EXSTYLE);
		DWORD style = GetWindowLong(hEdit1, GWL_STYLE);
		
		hEdit2 = CreateWindowEx
			(	exStyle,
				TEXT("EDIT"),
				TEXT(""),
				//style | WS_VSCROLL | WS_HSCROLL,
				WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN,
				10, 10,
				300, 200,
				hDlg,
				NULL,
				GetModuleHandle(0),
				NULL
			);
		Edit_SetPasswordChar(hPass, TEXT('o'));
		ShowWindow(hEdit2, SW_HIDE);
	}
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