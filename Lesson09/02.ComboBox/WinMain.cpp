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

HWND hEditText;
HWND hComboDropDown;
HWND hComboDDList;

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		hEditText = GetDlgItem(hDlg, IDC_EDITTEXT);
		hComboDropDown = GetDlgItem(hDlg, IDC_COMBODDOWN);
		hComboDDList = GetDlgItem(hDlg, IDC_COMBODDOWNLIST);
		TCHAR *list[3] = { TEXT("первый"),TEXT("второй"),TEXT("третий") };
		for (int i = 0; i <3; i++)
		{
			SendDlgItemMessage(hDlg, IDC_COMBOSIMPLE, CB_ADDSTRING, NULL, LPARAM(list[i]));
			ComboBox_AddString(hComboDropDown, list[i]);
			SendMessage(hComboDDList, CB_ADDSTRING, NULL, LPARAM(list[i]));
		}
		SendDlgItemMessage(hDlg, IDC_COMBOSIMPLE, CB_SETCURSEL, 0, NULL);
		ComboBox_SetCurSel(hComboDropDown, 1);
		SendMessage(hComboDDList, CB_SETCURSEL, 2, NULL);
	}
		return TRUE;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTONADD:
		{
			int count = Edit_GetTextLength(hEditText);
			std::unique_ptr<TCHAR> text(new TCHAR[count+1]);
			Edit_GetText(hEditText, text.get(), count+1);
			
			SendDlgItemMessage(hDlg, IDC_COMBOSIMPLE, CB_ADDSTRING, NULL, LPARAM(text.get()));
			ComboBox_AddString(hComboDropDown, text.get());
			SendMessage(hComboDDList, CB_ADDSTRING, NULL, LPARAM(text.get()));

			count = SendDlgItemMessage(hDlg, IDC_COMBOSIMPLE, CB_GETCOUNT, NULL, NULL);
			SendDlgItemMessage(hDlg, IDC_COMBOSIMPLE, CB_SETCURSEL, count-1, NULL);

			break;
		}
		case IDC_EXIT:
			SendMessage(hDlg, WM_CLOSE, NULL, NULL);
			break;
		}
	}
	return TRUE;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	}
	return FALSE;
}