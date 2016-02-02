#include "resource.h"
#include <Windows.h>

BOOL CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DialogProc2(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszCmdOpt, int nShowOpt)
{
	return DialogBox(hThisInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
}

HWND hStaticText;
HWND hBtnSet;
HWND hBtnGet;
HWND hEdit;

BOOL CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		hStaticText = GetDlgItem(hWnd, IDC_MYSTATIC);
		hBtnSet = GetDlgItem(hWnd, IDC_BTNSET);
		hBtnGet = GetDlgItem(hWnd, IDC_BTNGET);
		hEdit = GetDlgItem(hWnd, IDC_EDIT1);
		return TRUE;
	case WM_COMMAND:
	{
		switch (wParam)
		{
		case IDC_EXIT:
			EndDialog(hWnd, 0);
			return TRUE;
		case IDC_BTNGET:
		{
			LPTSTR buff;
			int len = GetWindowTextLength(hStaticText);
			buff = new TCHAR[len+1];
			GetWindowText(hStaticText, buff, len+1);
			MessageBox(hWnd, buff, TEXT("Статик"), 0);
			delete[]buff;
		}
			return TRUE;
		case IDC_BTNSET:
		{
			LPTSTR buff;
			int len = GetWindowTextLength(hEdit);
			buff = new TCHAR[len + 1];
			GetWindowText(hEdit, buff, len + 1);
			SetWindowText(hStaticText, buff);
			delete[]buff;
		}
			return TRUE;
		case IDC_SHOW:
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hWnd, DialogProc2);
			return TRUE;
		default:
			return FALSE;
		}
	}
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}

BOOL CALLBACK DialogProc2(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (wParam)
		{
		case IDOK:
			EndDialog(hWnd, 0);
			return TRUE;		
		default:
			return FALSE;
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}