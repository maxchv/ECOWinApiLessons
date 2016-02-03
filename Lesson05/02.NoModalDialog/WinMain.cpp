#include <Windows.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszCmpOpt, int nShowOpt)
{
	HWND hDlg = CreateDialog(hThisInstance, MAKEINTRESOURCE(IDD_NOMODAL), NULL, DlgProc);

	ShowWindow(hDlg, nShowOpt);
	MSG msg;
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

HWND hEdit;
HWND hBtn;

BOOL CALLBACK DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool isEnabled = false;
	static POINT old_pt, cur_pt;
	static bool isClick = false;
	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (wParam)
		{
		case IDC_BTNONOFF:
			isEnabled = !isEnabled;
			isEnabled ? SetWindowText(hBtn, TEXT("Off")) : SetWindowText(hBtn, TEXT("On"));
			EnableWindow(hEdit, isEnabled);
			return TRUE;
		default:
			return FALSE;
		}
	}
		return TRUE;
	case WM_LBUTTONDOWN:
	{		
		isClick = true;
		old_pt.x = LOWORD(lParam);
		old_pt.y = HIWORD(lParam);
	}
	return TRUE;
	case WM_MOUSEMOVE:
	{
		if (isClick)
		{
			cur_pt.x = LOWORD(lParam);
			cur_pt.y = HIWORD(lParam);
			// переместить окно

			old_pt.x = cur_pt.x;
			old_pt.y = cur_pt.y;
		}
	}
		return TRUE;
	case WM_LBUTTONUP:
		isClick = false;
		return TRUE;
	case WM_INITDIALOG:
		hEdit = GetDlgItem(hWnd, IDC_EDITTEXT);
		EnableWindow(hEdit, isEnabled);
		hBtn = GetDlgItem(hWnd, IDC_BTNONOFF);
		return TRUE;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}