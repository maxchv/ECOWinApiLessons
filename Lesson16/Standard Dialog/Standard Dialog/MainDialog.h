#pragma once
#include "header.h"
#include <iostream>
using namespace std;

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
	void COpenFile(HWND hwnd);
	void CWriteFile(HWND hwnd);
};
