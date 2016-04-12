#pragma once
#include "header.h"

class CodingThreadDlg
{
public:
	CodingThreadDlg(void);
public:
	~CodingThreadDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CodingThreadDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	HWND hDialog;
};
