#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include "resource.h"

#pragma comment(lib, "comctl32")

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdOpt, int nCmdOpt)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

void Cls_OnClose(HWND hDlg)
{
	EndDialog(hDlg, 0);
}

void Cls_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_EXIT:
		SendMessage(hDlg, WM_CLOSE, 0, 0);
		break;
	}
}


void Cls_OnVScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos)
{
	
}

BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	SendDlgItemMessage(hwnd, IDC_SPIN1, UDM_SETRANGE32, 100, 100000);
	UDACCEL accel[3] = { {1, 10}, {3, 100}, {5, 500} };
	SendDlgItemMessage(hwnd, IDC_SPIN1, UDM_SETACCEL, 3, LPARAM(accel));

	HINSTANCE hInst = GetModuleHandle(NULL);

	HWND hEdit = CreateWindow(WC_EDIT, TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER,
		100, 100, 70, 30, hwnd, NULL, hInst, NULL);

	HWND hSpin =  CreateUpDownControl(
		WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS | UDS_ALIGNRIGHT |
		UDS_SETBUDDYINT| UDS_WRAP, // стили элемента управлени€
		0, // клиентска€ координата X левого верхнего угла
		0, // клиентска€ координата Y левого верхнего угла
		10, // ширина элемента управлени€
		30, // высота элемента управлени€
		hwnd, // дескриптор родительского окна
		1010, // идентификатор элемента управлени€
		hInst, // дескриптор приложени€
		hEdit, // дескриптор Ђпри€тел€ї
		1000, // верхн€€ граница
		100, // нижн€€ граница
		150 // текуща€ позици€
		);

	return TRUE;
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hDlg, WM_INITDIALOG, Cls_OnInitDialog);
		HANDLE_MSG(hDlg, WM_CLOSE, Cls_OnClose);
		HANDLE_MSG(hDlg, WM_COMMAND, Cls_OnCommand);		
		HANDLE_MSG(hDlg, WM_VSCROLL, Cls_OnVScroll);
	}
	return FALSE;
}