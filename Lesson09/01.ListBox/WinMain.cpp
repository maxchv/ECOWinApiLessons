#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <map>
#include <string>
#include <memory>
#include "resource.h"


INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdOpt, int nShowOpt)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

std::map<int, HWND> hButtons;

HWND hList;
HWND hEditString;
HWND hListBoxSingle;

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{		
	case WM_INITDIALOG:
		hEditString = GetDlgItem(hDlg, IDC_EDTSTRING);
		hListBoxSingle = GetDlgItem(hDlg, IDC_LISTSINGLE);
		return TRUE;
	case WM_COMMAND:		
		switch (LOWORD(wParam))
		{
		case IDC_LISTSINGLE:
		{
			switch (HIWORD(wParam))
			{
				case LBN_DBLCLK: // уведомление двойной клик в списке
				{
					TCHAR str[50];
					int idx = SendDlgItemMessage(hDlg, IDC_LISTSINGLE, LB_GETCURSEL, NULL, NULL);
					if (idx != LB_ERR)
					{
						wsprintf(str, TEXT("Выбран элемент с индексом %d"), idx);
						MessageBox(NULL, str, TEXT("Выбран"), MB_OK);
					}
				}
				break;
			}
		}
			break;
		case IDC_BTNADDSTRING:
		{
			TCHAR str[50];
			GetWindowText(hEditString, str, 49);
			//SendDlgItemMessage(hDlg, IDC_LISTSINGLE, LB_ADDSTRING, NULL, LPARAM(str));
			ListBox_AddString(hListBoxSingle, str);
			SendDlgItemMessage(hDlg, IDC_LISTMULTIPLE, LB_ADDSTRING, NULL, LPARAM(str));
		}
			break;
		case IDC_BTNFINDSTRING:
		{
			TCHAR str[50];
			GetWindowText(hEditString, str, 49);
			int idx = SendDlgItemMessage(hDlg, IDC_LISTSINGLE, LB_FINDSTRING, -1, LPARAM(str));
			if (idx != LB_ERR)
			{
				wsprintf(str, TEXT("Найден элемент с индексом %d"), idx);
				MessageBox(NULL, str, TEXT("Найден"), MB_OK);
			}
			else
			{
				MessageBox(NULL, TEXT("Элемент не найден"), TEXT("Не найден"), MB_OK);
			}
		}
			break;
		case IDC_BTNGETCURSEL:
		{
			TCHAR str[50];
			int idx = SendDlgItemMessage(hDlg, IDC_LISTSINGLE, LB_GETCURSEL, NULL, NULL);
			if (idx != LB_ERR)
			{
				wsprintf(str, TEXT("Выбран элемент с индексом %d"), idx);
				MessageBox(NULL, str, TEXT("Выбран"), MB_OK);
			}
			else
			{
				MessageBox(NULL, TEXT("Ни один элемент не выбран"), TEXT("Не выбарн"), MB_OK);
			}
		}
			break;
		case IDC_BTNGETSELCOUNT:
		{
			TCHAR str[50];
			int idx = SendDlgItemMessage(hDlg, IDC_LISTMULTIPLE, LB_GETSELCOUNT, NULL, NULL);
			if (idx != LB_ERR)
			{
				wsprintf(str, TEXT("Выбрано элементов %d"), idx);
				MessageBox(NULL, str, TEXT("Выбран"), MB_OK);
			}
			else
			{
				MessageBox(NULL, TEXT("Ни один элемент не выбран"), TEXT("Не выбарн"), MB_OK);
			}
		}
			break;
		case IDC_BTNGETSELITEMS:
		{
			TCHAR str[256];
			int count = SendDlgItemMessage(hDlg, IDC_LISTMULTIPLE, LB_GETSELCOUNT, NULL, NULL);
			if (count != LB_ERR)
			{
				std::unique_ptr<int> indexes(new int[count]);
				SendDlgItemMessage(hDlg, IDC_LISTMULTIPLE, LB_GETSELITEMS, count, LPARAM(indexes.get()));							
				for (int i = 0; i < count; i++)
				{
					wsprintf(str, TEXT("Выбран элемент с индексом %d"), indexes.get()[i]);
					MessageBox(NULL, str, TEXT("Выбран"), MB_OK);
				}
				
			}
			else
			{
				MessageBox(NULL, TEXT("Ни один элемент не выбран"), TEXT("Не выбарн"), MB_OK);
			}
		}
		break;
		case IDC_BTNINSERTSTRING:
		{
			TCHAR str[50];
			GetWindowText(hEditString, str, 49);
			int idx = SendDlgItemMessage(hDlg, IDC_LISTSINGLE, LB_GETCURSEL, NULL, NULL);
			if (idx != LB_ERR)
			{
				SendDlgItemMessage(hDlg, IDC_LISTSINGLE, LB_INSERTSTRING, idx + 1, LPARAM(str));
			}
			else
			{
				SendDlgItemMessage(hDlg, IDC_LISTSINGLE, LB_ADDSTRING, NULL, LPARAM(str));
			}
		}
			break;
		case IDC_BTNSELECTSTRING:
		{
			TCHAR str[50];
			GetWindowText(hEditString, str, 49);
			int idx = SendDlgItemMessage(hDlg, IDC_LISTSINGLE, LB_SELECTSTRING, -1, LPARAM(str));
			if (idx != LB_ERR)
			{
				wsprintf(str, TEXT("Найден элемент с индексом %d"), idx);
				//MessageBox(NULL, str, TEXT("Найден"), MB_OK);
			}
			else
			{
				MessageBox(NULL, TEXT("Элемент не найден"), TEXT("Не найден"), MB_OK);
			}
		}
			break;
		case IDC_BTNSETCURSEL:
		{
			TCHAR str[50];
			SendDlgItemMessage(hDlg, IDC_EDTNUMBER, WM_GETTEXT, 50, LPARAM(str));
			int idx = _wtoi(str);
			SendDlgItemMessage(hDlg, IDC_LISTMULTIPLE, LB_SETSEL, TRUE, idx);			
		}
			break;
		case IDC_BTNGETTEXT:
		{			
			int idx = SendDlgItemMessage(hDlg, IDC_LISTSINGLE, LB_GETCURSEL, NULL, NULL);
			if (idx != LB_ERR)
			{
				int count = SendDlgItemMessage(hDlg, IDC_LISTSINGLE, LB_GETTEXTLEN, idx, NULL);
				std::unique_ptr<TCHAR> str(new TCHAR[count + 1]);
				SendDlgItemMessage(hDlg, IDC_LISTSINGLE, LB_GETTEXT, idx, LPARAM(str.get()));
				MessageBox(NULL, str.get(), TEXT("Выбран текст"), MB_OK);
			}
		}
			break;
		case IDC_BTNDELETESTRING:
		{
			int idx = SendDlgItemMessage(hDlg, IDC_LISTSINGLE, LB_GETCURSEL, NULL, NULL);
			if (idx != LB_ERR)
			{
				SendDlgItemMessage(hDlg, IDC_LISTSINGLE, LB_DELETESTRING, idx, NULL);
				if (idx)
				{
					SendDlgItemMessage(hDlg, IDC_LISTSINGLE, LB_SETCURSEL, idx - 1, NULL);
				}
			}
		}
			break;
		case IDC_BTNRESETCONTENT:
		{
			SendDlgItemMessage(hDlg, IDC_LISTSINGLE, LB_RESETCONTENT, NULL, NULL);
			SendDlgItemMessage(hDlg, IDC_LISTMULTIPLE, LB_RESETCONTENT, NULL, NULL);
		}
		break;
		case IDC_BTNGETCOUNT:
		{
			int count = SendDlgItemMessage(hDlg, IDC_LISTMULTIPLE, LB_GETCOUNT, NULL, NULL);
			TCHAR str[50];
			wsprintf(str, TEXT("Всего %d элементов"), count);
			MessageBox(NULL, str, TEXT("Информация"), MB_OK);
		}
		break;
		case IDC_EXIT:
			SendMessage(hDlg, WM_CLOSE, NULL, NULL);
			break;
		}
		return TRUE;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;	
	}
	return FALSE;
}