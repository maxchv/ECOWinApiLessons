
#include <Windows.h>
#include "resource.h"

INT_PTR WINAPI DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdOpt, int nShowOpt)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
}

HBITMAP hImage;
HWND hPictureBox;

INT_PTR WINAPI DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		hPictureBox = GetDlgItem(hWnd, IDC_IMAGE);
		return TRUE;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDC_BNTOPEN:
			hImage = (HBITMAP)LoadImage(GetModuleHandle(0), TEXT("01.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			if (hImage)
			{
				SendMessage(hPictureBox, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
			}
			else
			{
				MessageBox(hWnd, TEXT("Ошибка загрузки файла"), TEXT("Error"), MB_OK | MB_ICONERROR);
			}
			break;
		}
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	default:
		break;
	}
	return FALSE;
}