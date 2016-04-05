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
		SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT(">>> Работает первый поток")));
		Sleep(100);
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
		Sleep(150);
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
		Sleep(175);
	}
	SendMessage(hList, LB_ADDSTRING, 0, LPARAM(TEXT("Третий поток завершает работу")));
	return 0;
}

void CMultithreadDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	static HANDLE h = 0;
	switch (id)
	{
	case IDC_BUTTON1:
	{
		HWND hList = GetDlgItem(hwnd, IDC_LIST1);
		/*Thread1(hList);
		Thread2(hList);
		Thread3(hList);*/
		h = CreateThread(NULL, 0, Thread1, hList, CREATE_SUSPENDED, NULL);
		CreateThread(NULL, 0, Thread2, hList, 0, NULL);
		CreateThread(NULL, 0, Thread3, hList, 0, NULL);
	}
	break;
	case IDC_BUTTON2:
	{
		if (h)
		{
			ResumeThread(h);
		}
	}
	break;
		
	
	}
}

BOOL CALLBACK CMultithreadDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);		
	}
	return FALSE;
}