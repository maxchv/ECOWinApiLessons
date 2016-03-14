#include "AdditionalModalDialog.h"

CAdditionalModalDialog* CAdditionalModalDialog::ptr = NULL;

CAdditionalModalDialog::CAdditionalModalDialog(void)
{
	ptr = this;
	msg[0] = '\0';
}

CAdditionalModalDialog::CAdditionalModalDialog(TCHAR * msg)
{
	ptr = this;
	SendMsg(msg);
}

CAdditionalModalDialog::~CAdditionalModalDialog()
{

}

void CAdditionalModalDialog::SendMsg(TCHAR * msg)
{
	_tcscpy(this->msg, msg);
}

TCHAR * CAdditionalModalDialog::GetMsg()
{	
	return msg;
}

void CAdditionalModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL CAdditionalModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hEdit = GetDlgItem(hwnd, IDC_EDIT1);
	hStatic = GetDlgItem(hwnd, IDC_STATIC1);	
	SetWindowText(hwnd, TEXT("ƒополнительный модальный диалог"));
	SetWindowText(hEdit, TEXT("ѕередача данных главному диалогу!"));
	if (msg[0] != '\0')
	{
		SetWindowText(hStatic, msg);
	}
	return TRUE;
}


void CAdditionalModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDOK:
	{
		// получить дескриптор родительского окан
		HWND hParent = GetParent(hwnd);
		// передать сообщение родителю
		SendMessage(hParent, WM_SETTEXT, NULL, (LPARAM)TEXT("ѕривет из дочернего окна"));
		EndDialog(hwnd, IDOK);
		break;
	}
	case IDCANCEL:
		EndDialog(hwnd, IDCANCEL);
		break;
	default:
		break;
	}
}

BOOL CALLBACK CAdditionalModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
