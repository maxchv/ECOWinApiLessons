#pragma once
#include "header.h"
#include "resource.h"

class ListViewDialog
{
	
		
	
public:
	ListViewDialog();
	~ListViewDialog();
	INT_PTR show();
	
private:
	void SetView(DWORD dwView);
	int Cls_OnNotify(HWND hwnd, int id, LPNMHDR lParam);
	void Cls_OnClose(HWND hwnd);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	static ListViewDialog* _this;
	static INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
		
	HINSTANCE g_hInst;
	HWND hListview;
	HIMAGELIST hLargeIcons;
	HIMAGELIST hSmallIcons;
};

