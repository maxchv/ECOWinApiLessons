#include "PriorityDlg.h"

CPriorityDlg* CPriorityDlg::ptr = NULL;

CPriorityDlg::CPriorityDlg(void)
{
	ptr = this;
}

CPriorityDlg::~CPriorityDlg(void)
{

}

void CPriorityDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CPriorityDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
	hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);
	hEdit3 = GetDlgItem(hwnd, IDC_EDIT3);
	SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);
	return TRUE;
}

DWORD WINAPI Thread1(LPVOID lp)
{
	DWORD pr = GetPriorityClass(GetCurrentProcess());
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS );
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
	HWND hWnd = HWND(lp);
	for (int i = 0; i <= 50000; i++)
	{
		TCHAR str[10];
		wsprintf(str, TEXT("%d"), i);
		SetWindowText(hWnd, str);
	}
	SetPriorityClass(GetCurrentProcess(), pr);
	return 0;
}

DWORD WINAPI Thread2(LPVOID lp)
{
	DWORD pr = GetPriorityClass(GetCurrentProcess());
	SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS );
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);
	HWND hWnd = HWND(lp);
	for (int i = 0; i <= 50000; i++)
	{
		TCHAR str[10];
		wsprintf(str, TEXT("%d"), i);
		SetWindowText(hWnd, str);
	}
	SetPriorityClass(GetCurrentProcess(), pr);
	return 0;
}

DWORD WINAPI Thread3(LPVOID lp)
{
	DWORD pr = GetPriorityClass(GetCurrentProcess());
	SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_IDLE);
	HWND hWnd = HWND(lp);
	for (int i = 0; i <= 50000; i++)
	{
		TCHAR str[10];
		wsprintf(str, TEXT("%d"), i);
		SetWindowText(hWnd, str);
	}
	SetPriorityClass(GetCurrentProcess(), pr);
	return 0;
}

void CPriorityDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(IDC_REALTIME == id)
	{
		HANDLE hThread = CreateThread(NULL, 0, Thread1, hEdit1, 0, NULL);
		CloseHandle(hThread);
	}
	else if(IDC_NORMAL == id)
	{
		HANDLE hThread = CreateThread(NULL, 0, Thread2, hEdit2, 0, NULL);
		CloseHandle(hThread);
	}
	else if(IDC_IDLE == id)
	{
		HANDLE hThread = CreateThread(NULL, 0, Thread3, hEdit3, 0, NULL);
		CloseHandle(hThread);
	}
}

BOOL CALLBACK CPriorityDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}