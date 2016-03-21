#include "MainDialog.h"

MainDialog *MainDialog::ptr = NULL;

MainDialog::MainDialog()
{
	ptr = this;
}


MainDialog::~MainDialog()
{
}

void MainDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL MainDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	// Create the Toolbar control
	RECT rc = { 0, 0, 0, 0 };
	hToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, 0,
		TBSTYLE_FLAT | CCS_ADJUSTABLE | CCS_NODIVIDER | WS_CHILD | WS_VISIBLE,
		rc.left, rc.top, rc.right, rc.bottom,
		hwnd, (HMENU)IDC_TOOLBAR, GetModuleHandle(0), 0);

	SendMessage(hToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
			
	TBADDBITMAP tbAddBmp = { 0 };
	tbAddBmp.hInst = HINST_COMMCTRL;	
	tbAddBmp.nID = IDB_STD_SMALL_COLOR;	

	SendMessage(hToolbar, TB_ADDBITMAP, 0, (WPARAM)&tbAddBmp);

	const int numButtons = 7;
	TBBUTTON tbButtons[numButtons] =
	{
		{ STD_FILENEW, ID_FILE_NEW, TBSTATE_ENABLED,
			BTNS_AUTOSIZE, 0, 0, (INT_PTR)TEXT("New") },

		{ STD_FILEOPEN, ID_FILE_OPEN, TBSTATE_ENABLED,
			BTNS_AUTOSIZE, 0, 0, (INT_PTR)TEXT("Open") },

		{ STD_FILESAVE, ID_FILE_SAVE, 0,
			BTNS_AUTOSIZE, 0, 0, (INT_PTR)TEXT("Save") },

		{ 0, NULL, 0,	TBSTYLE_SEP, 0, 0, (INT_PTR)TEXT("") }, // Separator

		{ STD_COPY, ID_EDIT_COPY, TBSTATE_ENABLED,
			BTNS_AUTOSIZE, 0, 0, (INT_PTR)TEXT("Copy") },

		{ STD_CUT, ID_EDIT_CUT, TBSTATE_ENABLED,
			BTNS_AUTOSIZE, 0, 0, (INT_PTR)TEXT("Cut") },

		{ STD_PASTE, ID_EDIT_PASTE, TBSTATE_ENABLED,
			BTNS_AUTOSIZE, 0, 0, (INT_PTR)TEXT("Paste") }
	};

	SendMessage(hToolbar, TB_ADDBUTTONS, numButtons, (LPARAM)tbButtons);
	
	SendMessage(hToolbar, TB_AUTOSIZE, 0, 0);

	return TRUE;
}


void MainDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case ID_FILE_NEW:
		MessageBox(hwnd, TEXT("New file"), TEXT(""), MB_OK);
		break;
	}
}

BOOL CALLBACK MainDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}