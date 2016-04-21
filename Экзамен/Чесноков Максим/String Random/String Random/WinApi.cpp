#include "MainDlg.h"

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmd, int nShowOpt)
{
	srand(static_cast<unsigned int>(time(0)));

	MainDlg dlg;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, MainDlg::DlgProc);
}