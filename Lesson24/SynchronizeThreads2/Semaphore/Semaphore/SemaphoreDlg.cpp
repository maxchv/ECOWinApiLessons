#include "SemaphoreDlg.h"

CSemaphoreDlg* CSemaphoreDlg::ptr = NULL;

CSemaphoreDlg::CSemaphoreDlg(void)
{
	ptr = this;
}

CSemaphoreDlg::~CSemaphoreDlg(void)
{
	
}

void CSemaphoreDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CSemaphoreDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
	hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);
	hEdit3 = GetDlgItem(hwnd, IDC_EDIT3);
	hEdit4 = GetDlgItem(hwnd, IDC_EDIT4);
	hEdit5 = GetDlgItem(hwnd, IDC_EDIT5);
	return TRUE;
}

DWORD WINAPI Thread(LPVOID lp)
{
	HWND hEdit = (HWND) lp;
	HANDLE h = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("{41B4DBD4-F00A-4999-BFA9-1A20D12591B1}"));
	if (WaitForSingleObject(h, INFINITE) == WAIT_OBJECT_0)
	{
		for (int i = 0; i <= 50; i++)
		{
			TCHAR str[5];
			wsprintf(str, TEXT("%d"), i);
			Sleep(100);
			SetWindowText(hEdit, str);
		}
		ReleaseSemaphore(h, 1, NULL);
	}
	CloseHandle(h);
	return 1;
}

void CSemaphoreDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_BUTTON1)
	{
		HANDLE hSemaphore = CreateSemaphore(NULL, 3, 3, TEXT("{41B4DBD4-F00A-4999-BFA9-1A20D12591B1}"));
		HANDLE hThread = CreateThread(NULL, 0, Thread, hEdit1, 0, NULL);
		CloseHandle(hThread);
		hThread = CreateThread(NULL, 0, Thread, hEdit2, 0, NULL);
		CloseHandle(hThread);
		hThread = CreateThread(NULL, 0, Thread, hEdit3, 0, NULL);
		CloseHandle(hThread);
		hThread = CreateThread(NULL, 0, Thread, hEdit4, 0, NULL);
		CloseHandle(hThread);
		hThread = CreateThread(NULL, 0, Thread, hEdit5, 0, NULL);
		CloseHandle(hThread);
	}
}

BOOL CALLBACK CSemaphoreDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}