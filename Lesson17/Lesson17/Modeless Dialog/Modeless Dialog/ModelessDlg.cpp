#include "ModelessDlg.h"

CModelessDialog* CModelessDialog::ptr = NULL;
HWND CModelessDialog::hAddDialog = NULL;

CModelessDialog::CModelessDialog(void)
{
	//ptr = this;
}

CModelessDialog::~CModelessDialog(void)
{

}

CModelessDialog* CModelessDialog::getInstance()
{
	if (!ptr)
	{
		ptr = new CModelessDialog();
	}
	return ptr;
}

void CModelessDialog::Create(HWND hParent)
{
	hAddDialog = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hParent, CModelessDialog::DlgProc);
	// ���������� ����	
	ShowWindow(hAddDialog, SW_RESTORE);

	//������������ �������������� ����������� ����
	SetForegroundWindow(hAddDialog);
}

HWND CModelessDialog::getStaticHWND()
{
	return hStatic;
}

HWND CModelessDialog::getDlgHWND()
{
	return hAddDialog;
}

void CModelessDialog::Cls_OnClose(HWND hwnd)
{
	// ��������� ����������� ���������� ����
	DestroyWindow(hwnd);
	hAddDialog = NULL;
}

BOOL CModelessDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hStatic = GetDlgItem(hwnd, IDC_STATIC1);
	SetWindowText(hwnd, TEXT("�������������� ����������� ������"));
	//SetWindowText(GetDlgItem(hwnd, IDC_EDIT1), TEXT("�������� ������ �������� �������!"));
	SendDlgItemMessage(hwnd, WM_SETTEXT, IDC_EDIT1, NULL, (LPARAM)TEXT("�������� ������ �������� �������!"));
	return TRUE;
}


void CModelessDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
		case IDOK:
		{	
			// ����������� ������ �� EDIT � STATIC �������� ����
			DialogUtils::Text2Text(GetDlgItem(hwnd, IDC_EDIT1), 
								   GetDlgItem(GetParent(hwnd), IDC_STATIC1));				
		}
		break;
		case IDCANCEL:
		{
			// ��������� ����������� ���������� ����
			DestroyWindow(hwnd);
			hAddDialog = NULL;			
		}
		break;
		case IDC_EDIT1:
		{
			if (codeNotify = EN_CHANGE)
			{
				SendMessage(hwnd, WM_COMMAND, IDOK, NULL);
			}
		}
		break;
	}
}

BOOL CALLBACK CModelessDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
