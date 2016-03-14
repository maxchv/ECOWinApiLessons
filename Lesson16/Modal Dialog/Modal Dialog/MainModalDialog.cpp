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
	SetWindowText(hEdit1, TEXT("�������� ������ ��������������� �������!"));
	SetWindowText(hEdit2, TEXT("�������� ������ ��������������� �������!"));
	return TRUE;
}


void CMainModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_BUTTON1)
	{
		CAdditionalModalDialog dlg;
		TCHAR buffer[200];
		GetWindowText(hEdit1, buffer, 200);
		// �������� ������ ����� public-���� ������ CAdditionalModalDialog ��������������� �������
		_tcscpy(dlg.text, buffer);
		INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, CAdditionalModalDialog::DlgProc);
		if(result == IDOK)
		{
			// ���������� �� ��������������� ������� ������ ������������ �� �������
			SetWindowText(hStatic1, dlg.text);
		}
	}
	else if(id == IDC_BUTTON2)
	{
		TCHAR buffer[200];
		GetWindowText(hEdit2, buffer, 200);
		// �������� ������ ����� ����������� ������ CAdditionalModalDialog ��������������� �������
		CAdditionalModalDialog dlg(buffer);
		INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, CAdditionalModalDialog::DlgProc);
		if(result == IDOK)
		{
			// ���������� �� ��������������� ������� ������ ������������ �� �������
			SetWindowText(hStatic2, dlg.text);
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
