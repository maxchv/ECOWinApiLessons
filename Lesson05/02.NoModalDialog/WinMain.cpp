#include <Windows.h>
#include "resource.h"
#include <sstream>
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
HWND hStatic;

std::wstringstream sbuf;

BOOL CALLBACK DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool isEnabled = false;
	RECT rect;
	static int dx, dy;
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
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		sbuf.str(TEXT(""));
		sbuf << TEXT("x: ") << x << TEXT(" y: ") << y <<
			TEXT(" dx: ") << dx << TEXT(" dy: ") << dy;

		SetWindowText(hWnd, sbuf.str().data());
		
		GetWindowRect(hStatic, &rect);
		dx = rect.left - x - 6;
		dy = rect.top - y;

		if (x > rect.left && x < rect.right && y > rect.top && y < rect.bottom)
		{
			isClick = true;
		}
	}
	return TRUE;
	case WM_MOUSEMOVE:
	{
		if (isClick)
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			RECT rect;
			GetWindowRect(hStatic, &rect);
			int height = rect.bottom - rect.top;
			int width  = rect.right  - rect.left;
			
			sbuf.str(TEXT(""));
			sbuf << TEXT("x: ") << x << TEXT(" y: ") << y << std::endl <<
				TEXT(" left: ") << rect.left << TEXT(" top: ") << rect.top;
			SetWindowText(hStatic, sbuf.str().data());

			MoveWindow(hStatic, 
				       x + dx, y - dy, 
				       width, height, TRUE);
		}
	}
		return TRUE;
	case WM_LBUTTONUP:
		isClick = false;
		return TRUE;
	case WM_INITDIALOG:
		hStatic = GetDlgItem(hWnd, IDC_STATICMOVE);
		
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