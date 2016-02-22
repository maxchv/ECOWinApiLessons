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

void Cls_OnHScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos)
{
	int _pos = -1;
	static int prev_pos = -1;
	switch (code)
	{
	case TB_TOP:
	case TB_BOTTOM:
	case TB_LINEUP:		
	case TB_LINEDOWN:
	case TB_PAGEUP:
	case TB_PAGEDOWN:
		_pos = SendMessage(hwndCtl, TBM_GETPOS, NULL, NULL);
		break;
	case TB_THUMBPOSITION:
	case TB_THUMBTRACK:
		_pos = pos;
	default:
		break;
	}
	if (_pos >= 0)
	{
		TCHAR txt[10];
		wsprintf(txt, TEXT("%d"), _pos);
		SetWindowText(hwnd, txt);

		RECT r;
		GetWindowRect(hwnd, &r);
		
		if (prev_pos > _pos)
		{
			MoveWindow(hwnd,
				r.left, r.top,
				r.right - r.left - 10,
				r.bottom - r.top,
				TRUE);
		}
		else
		{
			MoveWindow(hwnd,
				r.left, r.top,
				r.right - r.left + 10,
				r.bottom - r.top,
				TRUE);
		}
		
		prev_pos = _pos;
	}
}

BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	HWND hHirizSlider = GetDlgItem(hwnd, IDC_SLIDERHORIZONT);
	SendMessage(hHirizSlider, TBM_SETRANGE, NULL, MAKELPARAM(100, 150));
	SendMessage(hHirizSlider, TBM_SETLINESIZE, NULL, 5);
	SendMessage(hHirizSlider, TBM_SETPAGESIZE, NULL, 15);
	SendMessage(hHirizSlider, TBM_SETTICFREQ, 5, NULL);
	return TRUE;
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		HANDLE_MSG(hDlg, WM_INITDIALOG, Cls_OnInitDialog);
		HANDLE_MSG(hDlg, WM_CLOSE, Cls_OnClose);
		HANDLE_MSG(hDlg, WM_COMMAND, Cls_OnCommand);	
		HANDLE_MSG(hDlg, WM_HSCROLL, Cls_OnHScroll);
	}
	return FALSE;
}