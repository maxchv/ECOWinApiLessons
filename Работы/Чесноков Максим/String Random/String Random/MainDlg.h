#pragma once
#include "Header.h"

class MainDlg
{
public:
	MainDlg();
	~MainDlg();
	static INT_PTR CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);

	int GetNumberLinesInFile(TCHAR path[MAX_PATH * 2]);	

	static MainDlg *this_;
	HWND hEditPath;
	HWND hStaticString1, hStaticString2, hStaticString3;
};