
#include <Windows.h>
#include "resource.h"

INT_PTR WINAPI DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdOpt, int nShowOpt)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
}

HWND hBtn;
HWND hEdit;

INT_PTR WINAPI DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND hCalc;
	switch (msg)
	{
	case WM_COMMAND:
		switch (wParam)
		{
		case IDC_BTNPMWMC:
			hCalc = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
			if (hCalc)
			{
				PostMessage(hCalc, WM_CLOSE, NULL, NULL);
			}
			return TRUE;
		case IDC_BTNPMWMQ:
			hCalc = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
			if (hCalc)
			{
				PostMessage(hCalc, WM_QUIT, NULL, NULL);
			}
			return TRUE;
		case IDC_BTNSMWMC:
			hCalc = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
			if (hCalc)
			{
				SendMessage(hCalc, WM_CLOSE, NULL, NULL);
			}
			return TRUE;
		case IDC_BTNSMWMQ:
			hCalc = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
			if (hCalc)
			{
				SendMessage(hCalc, WM_QUIT, NULL, NULL);
			}
			return TRUE;
		case IDC_BUTTON1:
			//SetWindowText(hEdit, TEXT("Текст в поле ввода"));
			SendMessage(hEdit, WM_SETTEXT, NULL, LPARAM(TEXT("Текст в поле ввода")));
			return TRUE;
		default:
			return TRUE;
		}
		return TRUE;
	case WM_INITDIALOG:
		hBtn = GetDlgItem(hWnd, IDC_BUTTON1);
		hEdit = GetDlgItem(hWnd, IDC_EDIT1);
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	default:
		return FALSE;
	}
	
	return FALSE;
}