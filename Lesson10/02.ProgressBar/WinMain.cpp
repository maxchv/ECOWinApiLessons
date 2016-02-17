#include <Windows.h>
#include <windowsx.h>
#include "resource.h"
#include <CommCtrl.h>

#pragma comment(lib, "comctl32")

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdOpt, int nShowOpt)
{
	INITCOMMONCONTROLSEX ctrl;
	ctrl.dwSize = sizeof(ctrl);
	ctrl.dwICC = ICC_PROGRESS_CLASS;
	InitCommonControlsEx(&ctrl);

	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

void Cls_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
		case IDOK:
		case IDCANCEL:
			SendMessage(hDlg, WM_CLOSE, NULL, NULL);
			break;
		case IDC_BTNMINUS:
			
			break;
		case IDC_BTNPLUS:
			
			break;
	}
}

void Cls_OnClose(HWND hDlg)
{
	EndDialog(hDlg, 0);
}

BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	return TRUE;
}
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hDlg, WM_INITDIALOG, Cls_OnInitDialog);
		HANDLE_MSG(hDlg, WM_CLOSE, Cls_OnClose);
		HANDLE_MSG(hDlg, WM_COMMAND, Cls_OnCommand);	
	}
	return FALSE;
}