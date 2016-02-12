#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <map>
#include <string>
#include "resource.h"


INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdOpt, int nShowOpt)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

std::map<int, HWND> hButtons;

HWND hList;

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{		
	case WM_INITDIALOG:
		
		return TRUE;
	case WM_COMMAND:		
		switch (LOWORD(wParam))
		{
		case IDC_EXIT:
			SendMessage(hDlg, WM_CLOSE, NULL, NULL);
			break;
		}
		return TRUE;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;	
	}
	return FALSE;
}