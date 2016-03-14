#pragma once
#include "header.h"

class CAdditionalModalDialog
{
public:
	CAdditionalModalDialog(void);
	CAdditionalModalDialog(LPCTSTR lpStr);
public:
	~CAdditionalModalDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CAdditionalModalDialog* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	TCHAR text[200];
	HWND hEdit, hStatic;
};
