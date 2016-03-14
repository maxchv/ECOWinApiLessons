#pragma once
#include "header.h"

class CMainDialog
{
public:
	CMainDialog(void);
public:
	~CMainDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CMainDialog* ptr;
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
};
