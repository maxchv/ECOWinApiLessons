#pragma once
#include "header.h"
#include "DialogUtils.h"

class CModelessDialog
{
public:
	
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);	
	HWND getStaticHWND();
	static HWND getDlgHWND();
	static void Create(HWND hParent);
	static CModelessDialog* getInstance();

private:
	CModelessDialog();
	~CModelessDialog();
	static CModelessDialog* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	HWND hStatic;
	static HWND hAddDialog; // дескриптор дополнительного диалога
};
