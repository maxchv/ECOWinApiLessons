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
	// ќтображаем окно	
	ShowWindow(hAddDialog, SW_RESTORE);

	//јктивизируем дополнительное немодальное окно
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
	// –азрушаем немодальное диалоговое окно
	DestroyWindow(hwnd);
	hAddDialog = NULL;
}

BOOL CModelessDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hStatic = GetDlgItem(hwnd, IDC_STATIC1);
	SetWindowText(hwnd, TEXT("ƒополнительный немодальный диалог"));
	//SetWindowText(GetDlgItem(hwnd, IDC_EDIT1), TEXT("ѕередача данных главному диалогу!"));
	SendDlgItemMessage(hwnd, WM_SETTEXT, IDC_EDIT1, NULL, (LPARAM)TEXT("ѕередача данных главному диалогу!"));
	return TRUE;
}


void CModelessDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
		case IDOK:
		{	
			// копирование текста из EDIT в STATIC главного окна
			DialogUtils::Text2Text(GetDlgItem(hwnd, IDC_EDIT1), 
								   GetDlgItem(GetParent(hwnd), IDC_STATIC1));				
		}
		break;
		case IDCANCEL:
		{
			// –азрушаем немодальное диалоговое окно
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
