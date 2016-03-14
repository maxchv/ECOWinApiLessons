#include "AdditionalModalDialog.h"

CAdditionalModalDialog* CAdditionalModalDialog::ptr = NULL;

CAdditionalModalDialog::CAdditionalModalDialog(void)
{
	ptr = this;
}

CAdditionalModalDialog::CAdditionalModalDialog(LPCTSTR lpStr)
{
	ptr = this;
	_tcscpy(text, lpStr);
}

CAdditionalModalDialog::~CAdditionalModalDialog(void)
{

}

void CAdditionalModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL CAdditionalModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hEdit = GetDlgItem(hwnd, IDC_EDIT1);
	hStatic = GetDlgItem(hwnd, IDC_STATIC1);
	// ѕереданные от главного диалога данные отображаютс€ на статике
	SetWindowText(hStatic, text);
	SetWindowText(hwnd, TEXT("ƒополнительный модальный диалог"));
	SetWindowText(hEdit, TEXT("ѕередача данных главному диалогу!"));
	return TRUE;
}


void CAdditionalModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDOK)
	{
		TCHAR buffer[200];
		GetWindowText(hEdit, buffer, 200);
		_tcscpy(text, buffer);
		HWND hParent = GetParent(hwnd);
		// ѕередача данных главному диалогу
		SetWindowText(hParent, TEXT("ѕривет от дочернего окна!"));
		EndDialog(hwnd, IDOK);
	}
	else if(id == IDCANCEL)
	{
		EndDialog(hwnd, IDCANCEL);
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
