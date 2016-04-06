#include "InterlockDlg.h"

CInterlockDlg* CInterlockDlg::ptr = NULL;

LONG counter = 0;

CInterlockDlg::CInterlockDlg(void)
{
	ptr = this;
}

CInterlockDlg::~CInterlockDlg(void)
{
	
}

void CInterlockDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CInterlockDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
	hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);
	return TRUE;
}

DWORD WINAPI Thread1(LPVOID lp)
{
	HWND hWnd = HWND(lp);
	for (int i = 0; i < 50000000; i++) 
	{
		++counter; 
	}
	TCHAR str[10];
	wsprintf(str, TEXT("%d"), counter);
	SetWindowText(hWnd, str);
	return 0;
}

DWORD WINAPI Thread2(LPVOID lp)
{
	HWND hWnd = HWND(lp);
	for (int i = 0; i < 50000000; i++) 
	{
		--counter; 
	}
	TCHAR str[10];
	wsprintf(str, TEXT("%d"), counter);
	SetWindowText(hWnd, str);
	return 0;
}

DWORD WINAPI Thread3(LPVOID lp)
{
	HWND hWnd = HWND(lp);
	for (int i = 0; i < 50000000; i++) 
	{
		InterlockedIncrement(&counter); 
	}
	TCHAR str[10];
	wsprintf(str, TEXT("%d"), counter);
	SetWindowText(hWnd, str);
	return 0;
}

DWORD WINAPI Thread4(LPVOID lp)
{
	HWND hWnd = HWND(lp);
	for (int i = 0; i < 50000000; i++) 
	{
		InterlockedDecrement(&counter); 
	}
	TCHAR str[10];
	wsprintf(str, TEXT("%d"), counter);
	SetWindowText(hWnd, str);
	return 0;
}

void CInterlockDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_BUTTON1)
	{
		counter = 0;
		HANDLE hThread = CreateThread(NULL, 0, Thread1, hEdit1, 0, NULL); 
		CloseHandle(hThread);
		hThread = CreateThread(NULL, 0, Thread2, hEdit1, 0, NULL); 
		CloseHandle(hThread);
	}
	else if(id == IDC_BUTTON2)
	{
		counter = 0;
		HANDLE hThread = CreateThread(NULL, 0, Thread3, hEdit2, 0, NULL); 
		CloseHandle(hThread);
		hThread = CreateThread(NULL, 0, Thread4, hEdit2, 0, NULL); 
		CloseHandle(hThread);
	}
}

BOOL CALLBACK CInterlockDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}