#include "EventDlg.h"

CEventDlg* CEventDlg::ptr = NULL;

CEventDlg::CEventDlg(void)
{
	ptr = this;
}

CEventDlg::~CEventDlg(void)
{

}

void CEventDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CEventDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
	hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);
	hEdit3 = GetDlgItem(hwnd, IDC_EDIT3);
	hEdit4 = GetDlgItem(hwnd, IDC_EDIT4);
	hEdit5 = GetDlgItem(hwnd, IDC_EDIT5);
	hEdit6 = GetDlgItem(hwnd, IDC_EDIT6);
	return TRUE;
}

DWORD WINAPI Thread1(LPVOID lp)
{
	HWND hWnd = HWND (lp);
	// ������� ���������� ������������� �������
	HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, 0, TEXT("{2BA7C99B-D9F7-4485-BB3F-E4735FFEF139}"));
	for(int i = 0; i < 5; i++)
	{
		//����� ������� ������� ������� � ���������� ��������� 
		if(WaitForSingleObject(hEvent, INFINITE) == WAIT_OBJECT_0)
		{
			// ����������� ��� ������ ������ �
			// ������� ������� � ���������� ���������, �.�. ������� � ������ �������
			for(int i = 1; i <= 100; i++)
			{
				TCHAR str[10];
				wsprintf(str, TEXT("%d"), i);
				SetWindowText(hWnd, str);
				Sleep(10);
			}
		}
		ResetEvent(hEvent); // ������� ������� � ������������ ���������
	}
	return 0;
}

DWORD WINAPI Thread2(LPVOID lp)
{
	HWND hWnd = HWND (lp);
	// ������� ���������� ������������� �������
	HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, 0, TEXT("{ECA57A59-2BD7-4fb5-A132-7A00944F7CEF}"));
	for(int i = 0; i < 5; i++)
	{
		// ����� ������� ������� ������� � ���������� ��������� 
		if(WaitForSingleObject(hEvent, INFINITE) == WAIT_OBJECT_0)
		{
			// ����������� ���� ������ ����� �
			// ������� ����������� � ������������ ���������, �.�. ����� ��������������
			for(int i = 1; i <= 100; i++)
			{
				TCHAR str[10];
				wsprintf(str, TEXT("%d"), i);
				SetWindowText(hWnd, str);
				Sleep(10);
			}
		}
	}
	return 0;
}

void CEventDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
		case IDC_BUTTON1:
			{
				CreateEvent(NULL, TRUE /* ������ ����� ������� */, FALSE /* ������������ ��������� */, TEXT("{2BA7C99B-D9F7-4485-BB3F-E4735FFEF139}"));
				EnableWindow(GetDlgItem(hwnd, IDC_BUTTON1), 0);
				HANDLE h = CreateThread(NULL, 0, Thread1, hEdit1, 0, NULL);
				CloseHandle(h);
				h = CreateThread(NULL, 0, Thread1, hEdit2, 0, NULL);
				CloseHandle(h);
				h = CreateThread(NULL, 0, Thread1, hEdit3, 0, NULL);
				CloseHandle(h);
			}
			break;
		case IDC_BUTTON2:
			{
				HANDLE h = OpenEvent(EVENT_ALL_ACCESS, 0, TEXT("{2BA7C99B-D9F7-4485-BB3F-E4735FFEF139}"));
				SetEvent(h); // ������� ������� � ���������� ���������
			}
			break;
		case IDC_BUTTON3:
			{
				HANDLE hEvent = CreateEvent(NULL, FALSE /*�������������� ����� ������� */, FALSE /* ������������ ��������� */, TEXT("{ECA57A59-2BD7-4fb5-A132-7A00944F7CEF}"));
				EnableWindow(GetDlgItem(hwnd, IDC_BUTTON3), FALSE);
				HANDLE h;
				h = CreateThread(NULL, 0, Thread2, hEdit4, 0, NULL);
				CloseHandle(h);
				h = CreateThread(NULL, 0, Thread2, hEdit5, 0, NULL);
				CloseHandle(h);
				h = CreateThread(NULL, 0, Thread2, hEdit6, 0, NULL);
				CloseHandle(h);
			}
		case IDC_BUTTON4:
			{
				HANDLE h = OpenEvent(EVENT_ALL_ACCESS, 0, TEXT("{ECA57A59-2BD7-4fb5-A132-7A00944F7CEF}"));
				SetEvent(h); // ������� ������� � ���������� ���������
			}
			break;
	}
}

BOOL CALLBACK CEventDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
