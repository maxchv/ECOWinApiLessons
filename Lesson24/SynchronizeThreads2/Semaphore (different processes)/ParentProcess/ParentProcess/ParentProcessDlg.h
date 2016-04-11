#pragma once
#include "header.h"

class ParentProcessDlg
{
public:
	ParentProcessDlg(void);
public:
	~ParentProcessDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static ParentProcessDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
};
