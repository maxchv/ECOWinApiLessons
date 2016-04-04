#include "MultithreadDlg.h"

CMultithreadDlg* CMultithreadDlg::ptr = NULL;

CMultithreadDlg::CMultithreadDlg(void)
{
	ptr = this;
}

CMultithreadDlg::~CMultithreadDlg(void)
{

}

void CMultithreadDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

DWORD WINAPI Thread1(LPVOID lp)
{
	HWND hList = (HWND)lp;
	for(int i = 0; i < 15; i++)
	{
		SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("Работает первый поток")));
		Sleep(10);
	}
	SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("Первый поток завершает работу")));
	return 0;
}

DWORD WINAPI Thread2(LPVOID lp)
{
	HWND hList = (HWND)lp;
	for(int i = 0; i < 20; i++)
	{
		SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("Работает второй поток")));
		Sleep(10);
	}
	SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("Второй поток завершает работу")));
	return 0;
}

DWORD WINAPI Thread3(LPVOID lp)
{
	HWND hList = (HWND)lp;
	for(int i = 0; i < 10; i++)
	{
		SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("Работает третий поток")));
		Sleep(10);
	}
	SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("Третий поток завершает работу")));
	return 0;
}

BOOL CMultithreadDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	HWND hList = GetDlgItem(hwnd, IDC_LIST1);
	CreateThread(NULL, 0, Thread1, hList, 0, NULL);
	CreateThread(NULL, 0, Thread2, hList, 0, NULL);
	CreateThread(NULL, 0, Thread3, hList, 0, NULL);
	return TRUE;
}

BOOL CALLBACK CMultithreadDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
	}
	return FALSE;
}