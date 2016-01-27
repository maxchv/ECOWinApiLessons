#include "resource.h"
#include <Windows.h>

BOOL CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszCmdOpt, int nShowOpt)
{
	return DialogBox(hThisInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
}

BOOL CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (wParam)
		{
		case IDC_EXIT:
			EndDialog(hWnd, 0);
			return TRUE;
		case IDC_SHOW:
			MessageBox(NULL, TEXT("Диалоговое окно"), TEXT("Заголовок"), MB_OK);
			return TRUE;
		default:
			return FALSE;
		}
	}
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}