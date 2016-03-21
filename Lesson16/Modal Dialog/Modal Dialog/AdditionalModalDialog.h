#pragma once
#include "header.h"

class CAdditionalModalDialog
{
	TCHAR msg[100];
public:
	CAdditionalModalDialog();	
	CAdditionalModalDialog(TCHAR *msg);
	~CAdditionalModalDialog();
	void SendMsg(TCHAR *msg);
	TCHAR* GetMsg();
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CAdditionalModalDialog* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);	
	HWND hEdit, hStatic;
};
