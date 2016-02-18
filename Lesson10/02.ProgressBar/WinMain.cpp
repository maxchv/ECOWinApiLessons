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
	ctrl.dwICC = ICC_WIN95_CLASSES;

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
			SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_DELTAPOS, -10, 0);
			SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_DELTAPOS, -5, 0);
			SendDlgItemMessage(hDlg, IDC_PROGRESS3, PBM_DELTAPOS, -2, 0);
			break;
		case IDC_BTNPLUS:
			SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_STEPIT, 0, 0);
			SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_STEPIT, 0, 0);
			SendDlgItemMessage(hDlg, IDC_PROGRESS3, PBM_STEPIT, 0, 0);
			break;
	}
}

void Cls_OnClose(HWND hDlg)
{
	EndDialog(hDlg, 0);
}

BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	SendDlgItemMessage(hwnd, IDC_PROGRESS1, PBM_SETBARCOLOR, 0, RGB(128, 0, 0));
	SendDlgItemMessage(hwnd, IDC_PROGRESS1, PBM_SETBKCOLOR, 0, RGB(0, 128, 0));
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