#pragma once
#include "header.h"

class CMultithreadDlg
{
public:
	CMultithreadDlg(void);
public:
	~CMultithreadDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CMultithreadDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	HWND hProgress1, hProgress2, hProgress3, hPlay1, hPlay2, hPlay3;
	HANDLE Th1, Th2, Th3;
};
