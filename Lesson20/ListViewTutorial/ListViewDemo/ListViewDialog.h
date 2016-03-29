#pragma once
#include "header.h"
#include "resource.h"

class ListViewDialog
{
	struct LVHandles
	{
		HWND hListview;
		HIMAGELIST hLargeIcons;
		HIMAGELIST hSmallIcons;
	};

public:
	ListViewDialog();
	~ListViewDialog();
	INT_PTR show();
	
private:

	void Cls_OnClose(HWND hwnd);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	static ListViewDialog* _this;
	static INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
	
	LVHandles *lvh;
	HINSTANCE g_hInst;
};

