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
	static bool isShown = false;

	switch (msg)
	{
	case WM_INITDIALOG:		
	{
		hEdit1 = GetDlgItem(hDlg, IDC_EDIT1);
		hPass = GetDlgItem(hDlg, IDC_PASSWORD);
		DWORD exStyle = GetWindowLong(hEdit1, GWL_EXSTYLE);
		DWORD style = GetWindowLong(hEdit1, GWL_STYLE);
		
		hEdit2 = CreateWindowEx
			(	exStyle,
				TEXT("EDIT"),
				TEXT(""),
				//style | WS_VSCROLL | WS_HSCROLL,
				WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN,
				25, 80,
				200, 150,
				hDlg,
				NULL,
				GetModuleHandle(0),
				NULL
			);
		Edit_SetPasswordChar(hPass, TEXT('0'));
		SetFocus(hPass);
		if (!isShown)
		{
			ShowWindow(hEdit2, SW_HIDE);
		}
	}
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{		
		case IDC_PASSWORD:
		{			
			if (HIWORD(wParam) == EN_CHANGE)
			{
				TCHAR text[256];
				//SendMessage(hPass, WM_GETTEXT, 255, LPARAM(text));
				//SendDlgItemMessage(hDlg, IDC_PASSWORD, WM_GETTEXT, 255, LPARAM(text));
				//GetWindowText(hPass, text, 255);
				Edit_GetText(hPass, text, 255);

				if (lstrcmp(text, TEXT("123456")) == 0)
				{
					ShowWindow(hEdit2, SW_SHOW);
				}
				else
				{
					ShowWindow(hEdit2, SW_HIDE);
				}
			}
		}
			return TRUE;
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