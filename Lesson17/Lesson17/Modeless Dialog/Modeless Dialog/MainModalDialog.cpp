#include "MainModalDialog.h"
#include "ModelessDlg.h"

CMainModalDialog* CMainModalDialog::ptr = NULL;

CMainModalDialog::CMainModalDialog()
{
	ptr = this;
}

CMainModalDialog::~CMainModalDialog()
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
	SetWindowText(hEdit1, TEXT("ѕередача данных дополнительному диалогу!"));
	return TRUE;
}


void CMainModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
		case IDC_BUTTON1:
		{	
			// ѕроверим, открыто ли дополнительное немодальное окно
			if (CModelessDialog::getDlgHWND() != NULL)
			{
				//јктивизируем дополнительное немодальное окно
				SetForegroundWindow(CModelessDialog::getDlgHWND());				
			}
			else
			{			
				CModelessDialog* dlg = CModelessDialog::getInstance();
				// —оздаем немодальное диалоговое окно		
				CModelessDialog::Create(hwnd);
								
				// ѕолучаем текст с текстового пол€ ввода				
				// ќтображаем текст на статике дополнительного диалога
				DialogUtils::Text2Text(hEdit1, dlg->getStaticHWND());
			}
		}
		break;
		case IDC_EDIT1:
		{
			if (codeNotify == EN_CHANGE)
			{
				// ѕроверим, открыто ли дополнительное немодальное окно
				if (CModelessDialog::getDlgHWND() != NULL)
				{
					CModelessDialog* dlg = CModelessDialog::getInstance();
					DialogUtils::Text2Text(hEdit1, dlg->getStaticHWND());					
				}
			}
		}
		break;
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
