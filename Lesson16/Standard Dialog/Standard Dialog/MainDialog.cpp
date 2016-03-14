#include "MainDialog.h"

CMainDialog* CMainDialog::ptr = NULL;

CMainDialog::CMainDialog(void)
{
	ptr = this;
}

CMainDialog::~CMainDialog(void)
{

}

void CMainDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

void CMainDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_SAVE)
	{
		
	}
	else if(id == IDC_OPEN)
	{

	}
}

BOOL CALLBACK CMainDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
