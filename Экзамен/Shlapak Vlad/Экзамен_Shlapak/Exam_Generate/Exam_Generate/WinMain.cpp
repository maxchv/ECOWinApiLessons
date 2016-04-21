#include "Generate_Text.h"

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
	Generate_Text dlg;
	srand(time(NULL));
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, Generate_Text::DlgProc);
}