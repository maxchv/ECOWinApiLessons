#include "MainModalDialog.h"
#include "AdditionalModalDialog.h"

CMainModalDialog* CMainModalDialog::ptr = NULL;

CMainModalDialog::CMainModalDialog(void)
{
	ptr = this;
}

CMainModalDialog::~CMainModalDialog(void)
{

}

void CMainModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL CMainModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
	hStatic1 = GetDlgItem(hwnd, IDC_STATIC1);
	hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);
	hStatic2 = GetDlgItem(hwnd, IDC_STATIC2);
	SetWindowText(hEdit1, TEXT("Передача данных дополнительному диалогу!"));
	SetWindowText(hEdit2, TEXT("Передача данных дополнительному диалогу!"));
	return TRUE;
}


void CMainModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_BUTTON1)
	{
		CAdditionalModalDialog dlg;
		TCHAR buf[100];
		GetWindowText(hEdit1, buf, 100);
		dlg.SendMsg(buf);
		if (DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, CAdditionalModalDialog::DlgProc) == IDOK)
		{
			//MessageBox(hwnd, TEXT("OK"), TEXT(""), 0);
			_tcscpy(buf, dlg.GetMsg());
			SetWindowText(hStatic1, buf);

		}
		else
		{
			//MessageBox(hwnd, TEXT("Cancel"), TEXT(""), 0);
		}
	}
	else if(id == IDC_BUTTON2)
	{
		TCHAR buf[100];
		GetWindowText(hEdit2, buf, 100);
		CAdditionalModalDialog dlg(buf);
		if (DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, CAdditionalModalDialog::DlgProc) == IDOK)
		{
			SetWindowText(hStatic2, dlg.GetMsg());
			//MessageBox(hwnd, TEXT("OK"), TEXT(""), 0);
		}
		else
		{
			//MessageBox(hwnd, TEXT("Cancel"), TEXT(""), 0);
		}
	}
}

BOOL CALLBACK CMainModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
