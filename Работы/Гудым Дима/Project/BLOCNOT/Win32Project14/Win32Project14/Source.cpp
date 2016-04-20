#include "Header.h"


int APIENTRY WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszCmdOpt, int nShowOpt)
{
	CMainDialog dlg;
	return DialogBox(hThisInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, CMainDialog::DlgProc);
}

