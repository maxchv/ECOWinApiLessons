#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <fstream>
#include <string>
#include "resource.h"
using namespace std;

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


INT_PTR WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lPstr, int last)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	return FALSE;
}

void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_BTNSTART:
		SetDlgItemText(hwnd, IDC_STATIC1, TEXT("“ут должна выводитьс€ случайна€ перва€ строка"));
		SetDlgItemText(hwnd, IDC_STATIC2, TEXT("“ут должна выводитьс€ случайна€ втора€ строка"));
		SetDlgItemText(hwnd, IDC_STATIC3, TEXT("“ут должна выводитьс€ случайна€ треть€ строка"));
		break;
	}
}

void Cls_OnClose(HWND hwnd)
{
	DestroyWindow(hwnd);
}

INT_PTR CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hwnd, WM_INITDIALOG, Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_CLOSE, Cls_OnClose);
	}
	return FALSE;
}