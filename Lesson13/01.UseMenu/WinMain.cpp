#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include "resource.h"

#pragma comment(lib, "comctl32")

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hStatus;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdArgs, int nCmdOpt)
{
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	HMENU hMenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));
	SetMenu(hwnd, hMenu);

	hStatus = CreateStatusWindow(WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP | SBARS_TOOLTIPS, TEXT("Ready"), hwnd, IDC_STATUSBAR);

	HMENU hEdit = GetSubMenu(hMenu, 1);

	EnableMenuItem(hEdit, 0, MF_BYPOSITION | MF_GRAYED);
	
	DrawMenuBar(hwnd);

	return FALSE;
}

void Cls_OnMenuSelect(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags)
{
	switch (item) 
	{
	case ID_FILE_NEW:
		SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)TEXT("Create new file"));
		break;
	case ID_FILE_OPEN:
		SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)TEXT("Open file"));
		break;
	case ID_FILE_SAVE:
		SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)TEXT("Save file"));
		break;
	case ID_FILE_EXIT:
		SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)TEXT("Close the program"));
		break;
	default:
		SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)TEXT("Ready"));
		break;
	}
}

void Cls_OnClose(HWND hDlg)
{
	EndDialog(hDlg, 0);
}

void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id) 
	{
	case IDOK:
	case ID_FILE_EXIT:
		SendMessage(hwnd, WM_CLOSE, NULL, NULL);
		break;
	}
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hDlg, WM_INITDIALOG, Cls_OnInitDialog);
		HANDLE_MSG(hDlg, WM_MENUSELECT, Cls_OnMenuSelect);
		HANDLE_MSG(hDlg, WM_COMMAND, Cls_OnCommand);
		HANDLE_MSG(hDlg, WM_CLOSE, Cls_OnClose);
	}
	return FALSE;
}