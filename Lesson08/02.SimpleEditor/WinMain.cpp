#include <Windows.h>
#include <windowsx.h>
#include "resource.h"

INT_PTR WINAPI DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdOpt, int nShowOpt)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

HWND hEdit;

WNDPROC OriginalProc = NULL;

LRESULT CALLBACK EditProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Вызов стандартного обработчика сообщений
	switch (message)
	{
	case WM_KEYDOWN:
		//MessageBox(NULL, TEXT("catch"), TEXT("info"), 0);
		break;
	default:
		break;
	}
	
	return CallWindowProc(OriginalProc, hWnd, message, wParam, lParam);
}

INT_PTR WINAPI DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{		
		hEdit = GetDlgItem(hDlg, IDC_EDITCTRL);
		OriginalProc = (WNDPROC)SetWindowLong(hEdit, GWL_WNDPROC, LONG(EditProc));
	}
	return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{		
		case IDC_BTNCUT:		// Cut
			break;
		case IDC_BTNPASTE:		// Paste
			break;
		case IDC_BTNCOPY:		// Copy
			break;
		case IDC_BTNSELECTALL:	// Select All
			//MessageBox(hDlg, TEXT("catch"), TEXT("info"), 0);
			//SendDlgItemMessage(hDlg, IDC_EDIT1, EM_SETSEL, 0, -1);
			//SendMessage(hEdit, EM_SETSEL, 1, -1);
			Edit_SetSel(hEdit, 0, -1);
			break;
		case IDC_BTNCLEAR:		// Clear
			//Edit_SetSel(hEdit, 0, -1);
			SendDlgItemMessage(hDlg, IDC_EDITCTRL, WM_CLEAR, NULL, NULL);
			break;			
		case IDC_BTNUNDO:		// Undo
			if (SendDlgItemMessage(hDlg, IDC_EDITCTRL, EM_CANUNDO, NULL, NULL))
			{
				SendDlgItemMessage(hDlg, IDC_EDITCTRL, WM_UNDO, NULL, NULL);
			}
			break;
		case IDOK:
		case IDCANCEL:
			SendMessage(hDlg, WM_CLOSE, NULL, NULL);
			break;
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