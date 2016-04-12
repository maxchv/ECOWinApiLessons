#pragma once
#include "header.h"

class OnlyOneCopyDlg
{
public:
	OnlyOneCopyDlg(void);
public:
	~OnlyOneCopyDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static OnlyOneCopyDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	HANDLE hMutex;
};
