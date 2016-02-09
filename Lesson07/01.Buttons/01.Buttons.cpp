// 01.Buttons.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "01.Buttons.h"

INT_PTR CALLBACK  DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	return  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

HWND hBtn;
HWND hBtn2;
HWND hCheck1;
HWND hCheck2;

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
		hBtn = CreateWindow
			(
				TEXT("BUTTON"),
				TEXT("Программная кнопка 1"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP | WS_TABSTOP,
				10, 10,
				85, 85,
				hDlg,
				(HMENU)IDC_BTN1,
				GetModuleHandle(0),
				NULL
			 );
		hBtn2 = CreateWindow
			(
				TEXT("BUTTON"),
				TEXT("Программная кнопка 2"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
				105, 10,
				185, 40,
				hDlg,
				(HMENU)IDC_BTN2,
				GetModuleHandle(0),
				NULL
				);
		hCheck2 = CreateWindow
			(
				TEXT("BUTTON"),
				TEXT("Программный флажок"),
				WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTO3STATE,
				10, 105,
				185, 40,
				hDlg,
				NULL,
				GetModuleHandle(0),
				NULL
				);
		
		hCheck1 = GetDlgItem(hDlg, IDC_CHECK1);
		SendMessage(hCheck1, BM_SETCHECK, BST_CHECKED, NULL);

        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
		else if (LOWORD(wParam) == IDC_BTN1)
		{
			//MessageBox(hDlg, TEXT("Кнопка нажата"), TEXT("Информация"), MB_OK);
			HBITMAP hSmile = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_SMILE));
			SetFocus(hBtn2);
			SendMessage(hBtn, BM_SETIMAGE, IMAGE_BITMAP, LPARAM(hSmile));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_CHECK1)
		{
			UINT state;
			//state = SendMessage(hCheck, BM_GETCHECK, NULL, NULL);
			//state = IsDlgButtonChecked(hDlg, IDC_CHECK1);
			state = SendDlgItemMessage(hDlg, IDC_CHECK1, BM_GETCHECK, NULL, NULL);
			if (state == BST_CHECKED)
			{
				CheckDlgButton(hDlg, IDC_CHECK1, BST_UNCHECKED);
			}
			else
			{
				CheckDlgButton(hDlg, IDC_CHECK1, BST_CHECKED);				
			}
		}
		else if (LOWORD(wParam) >= IDC_RADIO1 && LOWORD(wParam) <= IDC_RADIO3)
		{
			CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO3, LOWORD(wParam));
		}
		else if (LOWORD(wParam) >= IDC_RADIO4 && LOWORD(wParam) <= IDC_RADIO6)
		{
			CheckRadioButton(hDlg, IDC_RADIO4, IDC_RADIO6, LOWORD(wParam));
		}
        break;
    }
    return (INT_PTR)FALSE;
}
