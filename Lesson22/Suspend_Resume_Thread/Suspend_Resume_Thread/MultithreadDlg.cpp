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

DWORD WINAPI Thread(LPVOID lp)
{
	HWND hProgress = (HWND)lp;
	while(TRUE)
	{
		SendMessage(hProgress, PBM_SETPOS, rand()%200+1, 0);
		Sleep(250);
	}
	return 0;
}

BOOL CMultithreadDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	srand(time(0));
	hProgress1 = GetDlgItem(hwnd, IDC_PROGRESS1);
	SendMessage(hProgress1, PBM_SETRANGE, 0, MAKELPARAM(0, 200));
	SendMessage(hProgress1, PBM_SETSTEP, 1, 0);
	SendMessage(hProgress1, PBM_SETPOS, 0, 0);
	SendMessage(hProgress1, PBM_SETBKCOLOR, 0, LPARAM(RGB(0, 0, 255)));
	SendMessage(hProgress1, PBM_SETBARCOLOR, 0, LPARAM(RGB(255, 255, 0)));

	hProgress2 = GetDlgItem(hwnd, IDC_PROGRESS2);
	SendMessage(hProgress2, PBM_SETRANGE, 0, MAKELPARAM(0, 200));
	SendMessage(hProgress2, PBM_SETSTEP, 1, 0);
	SendMessage(hProgress2, PBM_SETPOS, 0, 0);
	SendMessage(hProgress2, PBM_SETBKCOLOR, 0, LPARAM(RGB(0, 255, 0)));
	SendMessage(hProgress2, PBM_SETBARCOLOR, 0, LPARAM(RGB(255, 0, 255)));

	hProgress3 = GetDlgItem(hwnd, IDC_PROGRESS3);
	SendMessage(hProgress3, PBM_SETRANGE, 0, MAKELPARAM(0, 200));
	SendMessage(hProgress3, PBM_SETSTEP, 1, 0);
	SendMessage(hProgress3, PBM_SETPOS, 0, 0);
	SendMessage(hProgress3, PBM_SETBKCOLOR, 0, LPARAM(RGB(255, 0, 0)));
	SendMessage(hProgress3, PBM_SETBARCOLOR, 0,LPARAM(RGB(0, 255, 255)));

	hPlay1 = GetDlgItem(hwnd, IDC_PLAY1);
	hPlay2 = GetDlgItem(hwnd, IDC_PLAY2);
	hPlay3 = GetDlgItem(hwnd, IDC_PLAY3);

	Th1 = CreateThread(NULL, 0, Thread, hProgress1, CREATE_SUSPENDED, NULL);
    Th2 = CreateThread(NULL, 0, Thread, hProgress2, 0, NULL);
	Th3 = CreateThread(NULL, 0, Thread, hProgress3, 0, NULL);
	return TRUE;
}

void CMultithreadDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_PLAY1)
	{
		static BOOL flag = FALSE;
		if(flag)
		{
			SuspendThread(Th1);
			SetWindowText(hPlay1, TEXT("Пуск"));
		}
		else
		{
			ResumeThread(Th1);
			SetWindowText(hPlay1, TEXT("Пауза"));
		}
		flag = !flag;
	}
	else if(id == IDC_PLAY2)
	{
		static BOOL flag = TRUE;
		if(flag)
		{
			SuspendThread(Th2);
			SetWindowText(hPlay2, TEXT("Пуск"));
		}
		else
		{
			ResumeThread(Th2);
			SetWindowText(hPlay2, TEXT("Пауза"));
		}
		flag = !flag;
	}
	else if(id == IDC_PLAY3)
	{
		static BOOL flag = TRUE;
		if(flag)
		{
			SuspendThread(Th3);
			SetWindowText(hPlay3, TEXT("Пуск"));
		}
		else
		{
			ResumeThread(Th3);
			SetWindowText(hPlay3, TEXT("Пауза"));
		}
		flag = !flag;
	}
	else if(id == IDC_STOP1)
	{
		TerminateThread(Th1, 0);
		CloseHandle(Th1);
		EnableWindow(hPlay1, FALSE);
	}
	else if(id == IDC_STOP2)
	{
		TerminateThread(Th2, 0);
		CloseHandle(Th2);
		EnableWindow(hPlay2, FALSE);
	}
	else if(id == IDC_STOP3)
	{
		TerminateThread(Th3, 0);
		CloseHandle(Th3);
		EnableWindow(hPlay3, FALSE);
	}
}

BOOL CALLBACK CMultithreadDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}