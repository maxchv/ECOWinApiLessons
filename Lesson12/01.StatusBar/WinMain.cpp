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
	case IDOK:
		SendMessage(hDlg, WM_CLOSE, 0, 0);
		break;
	}
}

BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	// Создание строки состояния
	HWND hStatus = CreateStatusWindow(WS_CHILD | WS_VISIBLE | CCS_BOTTOM | SBARS_TOOLTIPS,
		                              TEXT("Все в порядке "), 
									  hwnd, IDD_STATUSBAR);
	
	RECT r;
	GetWindowRect(hwnd, &r);
	int width = r.right - r.left;
	
	// Добавление трех секций
	int parts[4] = { width / 3, width * 2 / 3, width*2/3+80, -1 };
	SendMessage(hStatus, SB_SETPARTS, 4, LPARAM(parts));
	
	// Добавляем текст
	SendMessage(hStatus, SB_SETTEXT, 1 | SBT_NOBORDERS, LPARAM(TEXT("Вторая секция")));	

	SendMessage(hStatus, SB_SETTEXT, 2 | SBT_POPOUT, LPARAM(TEXT("Третья секция")));

	//SendMessage(hStatus, SB_SETBKCOLOR, 0, LPARAM(RGB(0, 0, 255)));

	// Задание иконки в статусбаре
	HICON hIcon = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON1));
	SendMessage(hStatus, SB_SETICON, 3, LPARAM(hIcon));

	// Всплывающая подсказка
	SendMessage(hStatus, SB_SETTIPTEXT, 0, LPARAM(TEXT("Всплывающая подсказка")));

	return TRUE;
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		HANDLE_MSG(hDlg, WM_CLOSE, Cls_OnClose);
		HANDLE_MSG(hDlg, WM_COMMAND, Cls_OnCommand);
		HANDLE_MSG(hDlg, WM_INITDIALOG, Cls_OnInitDialog);
	}
	return FALSE;
}