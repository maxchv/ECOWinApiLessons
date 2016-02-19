#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include "resource.h"

#pragma comment(lib, "comctl32")

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdOpt, int nCmdOpt)
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
	case IDC_EXIT:
		SendMessage(hDlg, WM_CLOSE, 0, 0);
		break;
	}
}

void Cls_OnHScroll(HWND hDlg, HWND hwndCtl, UINT code, int pos)
{

}

void Cls_OnVScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos)
{

}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hDlg, WM_CLOSE, Cls_OnClose);
		HANDLE_MSG(hDlg, WM_COMMAND, Cls_OnCommand);
		HANDLE_MSG(hDlg, WM_HSCROLL, Cls_OnHScroll);
		HANDLE_MSG(hDlg, WM_VSCROLL, Cls_OnVScroll);
	}
	return FALSE;
}