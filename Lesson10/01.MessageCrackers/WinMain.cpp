#include <Windows.h>
#include <windowsx.h>
#include "resource.h"

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdOpt, int nShowOpt)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

void Cls_OnClose(HWND hDlg)
{
	EndDialog(hDlg, 0);
}

void Cls_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
		case IDOK:
		case IDCANCEL:
			SendMessage(hDlg, WM_CLOSE, NULL, NULL);
			break;
	}
}

void Cls_OnLButtonDown(HWND hDlg, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	TCHAR buff[50];
	wsprintf(buff, TEXT("x: %d, y: %d"), x, y);
	SetWindowText(hDlg, buff);
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hDlg, WM_CLOSE, Cls_OnClose);
		HANDLE_MSG(hDlg, WM_COMMAND, Cls_OnCommand);
		HANDLE_MSG(hDlg, WM_LBUTTONDOWN, Cls_OnLButtonDown);
	}
	return FALSE;
}