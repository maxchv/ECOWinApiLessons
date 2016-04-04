#pragma once
#include "header.h"

class CInheritHandleDlg
{
public:
	CInheritHandleDlg(void);
public:
	~CInheritHandleDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CInheritHandleDlg* ptr;
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	TCHAR CommandLine[MAX_PATH];
	HANDLE hHandle;
};
