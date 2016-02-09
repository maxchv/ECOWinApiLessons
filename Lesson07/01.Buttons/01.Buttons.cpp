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
			SendMessage(hBtn, BM_SETIMAGE, IMAGE_BITMAP, LPARAM(hSmile));
			return (INT_PTR)TRUE;
		}
        break;
    }
    return (INT_PTR)FALSE;
}
