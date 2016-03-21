#pragma once
#include "header.h"

class MainDialog
{
	void InitFindReplace();
public:
	MainDialog();
	~MainDialog();
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static MainDialog* _this;
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void OnFind();
	void OnReplace();	
	void MessageFromFindReplace();
	TCHAR bufFind[FINDTEXTLENTH], alltext[TEXTLENGTH], bufReplace[FINDTEXTLENTH];
	HWND hEdit, hFindReplace, hDialog, hStatus;
	FINDREPLACE fr;
};
