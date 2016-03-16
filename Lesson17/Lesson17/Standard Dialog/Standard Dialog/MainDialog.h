#pragma once
#include "header.h"

class CMainDialog
{
public:
	CMainDialog();
	~CMainDialog();
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CMainDialog* ptr;
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void OnFind();
	void OnReplace();
	void MessageFromFindReplace();
	TCHAR bufFind[100], alltext[65536], bufReplace[100];
	HWND hEdit, hFR, hDialog;
	FINDREPLACE fr;
};
