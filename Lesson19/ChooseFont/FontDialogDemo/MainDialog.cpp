#include "MainDialog.h"

MainDialog *MainDialog::ptr = NULL;

MainDialog::MainDialog()
{
	ptr = this;
	lFont = { 0 };
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
	
	return TRUE;
}


void MainDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
		case IDC_BTN_FONT:
		{
			CHOOSEFONT chooseFont = { 0 };
			//lFont = { 0 };
			chooseFont.hwndOwner = hwnd;
			chooseFont.lStructSize = sizeof(CHOOSEFONT);			
			chooseFont.lpLogFont = &lFont;			
			
			chooseFont.Flags = CF_SCREENFONTS | CF_EFFECTS;

			if (ChooseFont(&chooseFont) == TRUE)
			{
				HFONT hFont = CreateFontIndirect(chooseFont.lpLogFont);
				SendDlgItemMessage(hwnd, IDC_EDIT1, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
			}
		}
	
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