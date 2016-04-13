#pragma once
#include "header.h"

class CEventDlg
{
public:
	CEventDlg(void);
public:
	~CEventDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CEventDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	HWND hEdit1, hEdit2, hEdit3, hEdit4, hEdit5, hEdit6;
};
