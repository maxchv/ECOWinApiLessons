#include "MainModalDialog.h"

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
	CMainModalDialog dlg;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, CMainModalDialog::DlgProc);
}