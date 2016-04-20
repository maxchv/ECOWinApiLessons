#pragma once
#include "stdafx.h"
#include "header.h"
#include <iostream>
using namespace std;

class CMainDialog
{
public:
	CMainDialog(void);
	~CMainDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CMainDialog* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	void Static_1(HWND hwnd);
	void Static_2(HWND hwnd);
	void Static_3(HWND hwnd);

	HWND hStatic1, hStatic2, hStatic3;
	int r_line1, r_line2, r_line3;
};