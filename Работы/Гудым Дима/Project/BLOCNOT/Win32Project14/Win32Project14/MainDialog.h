#pragma once
#include "header.h"

using namespace std;

class CMainDialog
{
	POINT mouse;
public:
	CMainDialog(void);
public:
	~CMainDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CMainDialog* ptr;
	void OnFind();
	void OnReplace();
	void MessageFromFindReplace();
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnMenuSelect(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy);
	void Cls_OnClose(HWND hwnd);
	void COpenFile(HWND hwnd);
	void CWriteFile(HWND hwnd);
	HWND hToolbar;
	TCHAR bufFind[100], alltext[65536], bufReplace[100];
	HWND hEdit, hFindReplace, hDialog;
	int num;
	FINDREPLACE fr;
	INT startSel, endSel;
	LOGFONT lFont;
};