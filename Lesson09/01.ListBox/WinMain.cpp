#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include "resource.h"


INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdOpt, int nShowOpt)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{		
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