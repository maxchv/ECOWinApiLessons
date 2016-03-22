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
	// создаем окно панели инструментов
	hToolbar = CreateWindow(TOOLBARCLASSNAME,
							NULL,
							TBSTYLE_FLAT | CCS_TOP | CCS_NODIVIDER | WS_CHILD | WS_VISIBLE,
							0, 0, 0, 0,
							hwnd,
							(HMENU)IDC_TOOLBAR,
							GetModuleHandle(0),
							NULL);
	// использовать структуру TBBUTTON дл€ хранени€ данных кнопок панели инструментов
	SendMessage(hToolbar, TB_BUTTONSTRUCTSIZE, WPARAM(sizeof(TBBUTTON)), 0);
	
	// «адать размер изображений в панели инструментов
	SendMessage(hToolbar, TB_SETBITMAPSIZE, 0, (LPARAM)MAKELONG(16, 15));
	
	// —оздание и настройка структуры дл€ панели управлени€
	// ”казать исочник изображений дл€ панели управлени€
	TBADDBITMAP tbAddBmp = { 0 };
	tbAddBmp.hInst = GetModuleHandle(0);// HINST_COMMCTRL;     // стандартные изображени€
	tbAddBmp.nID = IDB_BITMAP2;// IDB_STD_SMALL_COLOR;  

	SendMessage(hToolbar, TB_ADDBITMAP, 6, (LPARAM)&tbAddBmp);

	// «аполнение панели данными
	TBBUTTON systemButtons[] = {
		{STD_FILENEW, ID_FILE_NEW, TBSTATE_ENABLED, BTNS_AUTOSIZE, { 0 }, 0, (INT_PTR)TEXT("New")},		
		{STD_FILEOPEN, ID_FILE_OPEN, TBSTATE_ENABLED, BTNS_AUTOSIZE,{ 0 }, 0, (INT_PTR)TEXT("Open") },		
		{STD_FILESAVE, ID_FILE_SAVE, TBSTATE_ENABLED, BTNS_AUTOSIZE,{ 0 }, 0, (INT_PTR)TEXT("Save") },		
		{ 0, NULL, 0, TBSTYLE_SEP, { 0 }, 0, (INT_PTR)TEXT("") },
		{ STD_COPY, ID_EDIT_COPY, TBSTATE_ENABLED, BTNS_AUTOSIZE,{ 0 }, 0, (INT_PTR)TEXT("Copy") },		
		{ STD_CUT, ID_EDIT_CUT, TBSTATE_ENABLED, BTNS_AUTOSIZE,{ 0 }, 0, (INT_PTR)TEXT("Cut") },		
		{ STD_PASTE, ID_EDIT_PASTE, TBSTATE_ENABLED, BTNS_AUTOSIZE,{ 0 }, 0, (INT_PTR)TEXT("Paste") }		
	};

	TBBUTTON buttons[] = {	
		{ 0, ID_FILE_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON,{ 0 }, 0, (INT_PTR)TEXT("New") },		
		{ 1, ID_FILE_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON,{ 0 }, 0, (INT_PTR)TEXT("Open") },		
		{ 2, ID_FILE_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON,{ 0 }, 0, (INT_PTR)TEXT("Save") },
		{ 0, NULL, 0, TBSTYLE_SEP,{ 0 }, 0, (INT_PTR)TEXT("") },		
		{ 3, ID_EDIT_COPY, TBSTATE_ENABLED, TBSTYLE_BUTTON,{ 0 }, 0, (INT_PTR)TEXT("Copy") },		
		{ 4, ID_EDIT_CUT, TBSTATE_ENABLED, TBSTYLE_BUTTON,{ 0 }, 0, (INT_PTR)TEXT("Cut") },		
		{ 5, ID_EDIT_PASTE, TBSTATE_ENABLED, TBSTYLE_BUTTON,{ 0 }, 0, (INT_PTR)TEXT("Paste") }
	};

	int nButtons = sizeof(buttons) / sizeof(buttons[0]);
		
	// ”становка панели
	SendMessage(hToolbar, TB_ADDBUTTONS, nButtons, (LPARAM)buttons);

	// ѕодбор размера панели под размер окна
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
	case ID_FILE_QUIT:
		Cls_OnClose(hwnd);
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