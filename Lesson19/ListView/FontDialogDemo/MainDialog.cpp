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
	/*HFONT hFont = CreateFont(24, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, \
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, \
		DEFAULT_PITCH | FF_SWISS, L"Arial");
	SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_SETFONT, WPARAM(hFont), TRUE);*/
	HDC hDC = GetDC(GetDlgItem(hwnd, IDC_EDIT1));
	SetTextColor(hDC, RGB(255, 0, 0));
	return TRUE;
}


void MainDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_BTN_FONT:
	{
		CHOOSEFONT cf;            // common dialog box structure
		static LOGFONT lf;        // logical font structure
		static DWORD rgbCurrent;  // current text color
		HFONT hfont, hfontPrev;
		DWORD rgbPrev;

		// Initialize CHOOSEFONT
		ZeroMemory(&cf, sizeof(cf));
		cf.lStructSize = sizeof(cf);
		cf.hwndOwner = hwnd;
		cf.lpLogFont = &lf;
		cf.rgbColors = rgbCurrent;
		cf.Flags = CF_SCREENFONTS;

		if (ChooseFont(&cf) == TRUE)
		{
			hfont = CreateFontIndirect(cf.lpLogFont);			
			SendMessage(GetDlgItem(hwnd, IDC_EDIT1), WM_SETFONT, WPARAM(hfont), TRUE);
			
			
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