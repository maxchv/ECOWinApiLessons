#pragma once
#include "header.h"

class CWaitableTimerDlg
{
public:
	CWaitableTimerDlg(void);
public:
	~CWaitableTimerDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CWaitableTimerDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy);
	void OnTrayIcon(WPARAM wp, LPARAM lp); // обработчик пользовательского сообщени€
	HWND hButton, hEdit1, hSpin1, hEdit2, hSpin2, hEdit3, hSpin3, hDialog;
	HICON hIcon;
	PNOTIFYICONDATA pNID;
};
