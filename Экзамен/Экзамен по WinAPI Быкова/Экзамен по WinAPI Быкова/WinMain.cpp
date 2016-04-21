#include "ClassRandQuestionDlg.h"

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmd, int nShowOpt)
{
	srand(time(0));
	RandQuestionDlg dlg;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, RandQuestionDlg::DlgProc);
}