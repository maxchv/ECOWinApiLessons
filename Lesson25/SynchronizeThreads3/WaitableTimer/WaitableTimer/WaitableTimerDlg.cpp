#define WM_ICON WM_APP
#define ID_TRAYICON WM_USER
#include "WaitableTimerDlg.h"

CWaitableTimerDlg* CWaitableTimerDlg::ptr = NULL;

CWaitableTimerDlg::CWaitableTimerDlg(void)
{
	ptr = this;
	pNID = new NOTIFYICONDATA;
}

CWaitableTimerDlg::~CWaitableTimerDlg(void)
{
	delete pNID;
}

void CWaitableTimerDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CWaitableTimerDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	// ������� ����������� ��������� ����������
	hSpin1 = GetDlgItem(hwnd, IDC_SPIN2);
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
	hSpin2 = GetDlgItem(hwnd, IDC_SPIN3);
	hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);
	hSpin3 = GetDlgItem(hwnd, IDC_SPIN4);
	hEdit3 = GetDlgItem(hwnd, IDC_EDIT3);
	hButton = GetDlgItem(hwnd, IDC_BUTTON1);
	hDialog = hwnd;

	SYSTEMTIME st;
	GetLocalTime(&st); // ������� ������� ��������� �����
	TCHAR buff[10];

	wsprintf(buff, TEXT("%d"), st.wHour);
	SetWindowText(hEdit1, buff);
	wsprintf(buff, TEXT("%d"), st.wMinute);
	SetWindowText(hEdit2, buff);
	wsprintf(buff, TEXT("%d"), st.wSecond);
	SetWindowText(hEdit3, buff);

	// ��������� ����������� �������� ��� ���������
	SendMessage(hSpin1, UDM_SETRANGE32, 0, 23);
	SendMessage(hSpin2, UDM_SETRANGE32, 0, 59);
	SendMessage(hSpin3, UDM_SETRANGE32, 0, 59);

	// ������� ���������� ���������� ����������
	HINSTANCE hInst = GetModuleHandle(NULL);

	hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)); // ��������� ������
	SetClassLong(hDialog, GCL_HICON, LONG(hIcon)); // ������������� ������ � ������� ���� ����������
	
	memset(pNID, 0, sizeof(NOTIFYICONDATA)); //��������� ���������
	pNID->cbSize = sizeof(NOTIFYICONDATA); //������ ���������
	pNID->hIcon = hIcon; //��������� ���������������� ������
	pNID->hWnd = hwnd; //���������� ����, ������� ����� �������� ������������ ���������,
	// ��������������� � ������� � ����.	
	lstrcpy(pNID->szTip, TEXT("���������")); // ���������

	pNID->uCallbackMessage = WM_ICON; // ���������������� ���������
	// ������� ���������� ���� ������������� ��� ������� ������������
	// ��������� ����, ���������� �������� �������� � ���� hWnd. ��� ���������
	// ����������, ����� ���������� "�������" ��������� � ��������������, ���
	// ����������� ������, ��� ������ ���������� ��� �������������� � �������
	// ����������. �������� ��������� wParam �������� ��� ���� �������������
	// ������ � ����, ��� ��������� �������, � �������� ��������� lParam - 
	// "�������" ��� ������������ ���������, ��������������� � ��������.
	// ������ �������: ������ ����� �� ������ � ����.

	pNID->uFlags = NIF_TIP | NIF_ICON | NIF_MESSAGE | NIF_INFO;
	// NIF_ICON - ���� hIcon �������� ���������� �������� (��������� ������� ������ � ����).
	// NIF_MESSAGE - ���� uCallbackMessage �������� ���������� ��������
	// (��������� �������� ��������� �� ������ � ����).
	// NIF_TIP - ���� szTip �������� ���������� �������� (��������� ������� ����������� ��������� ��� ������ � ����).
	// NIF_INFO - ���� szInfo �������� ���������� �������� (��������� ������� Balloon ��������� ��� ������ � ����).
	lstrcpy(pNID->szInfo, TEXT("���������� ������������� ������ ������� �������������"));
	lstrcpy(pNID->szInfoTitle, TEXT("���������!"));
	pNID->uID = ID_TRAYICON; // ��������������� ������������� ������
	return TRUE;
}

DWORD WINAPI Thread(LPVOID lp)
{
	CWaitableTimerDlg* p = (CWaitableTimerDlg*)lp;
	HANDLE hTimer = CreateWaitableTimer(NULL, TRUE, NULL);// ������� ������ �������������
	TCHAR buf[10];
	int hours, minutes, seconds;
	GetWindowText(p->hEdit1, buf, 10);
	hours = _tstoi(buf);
	GetWindowText(p->hEdit2, buf, 10);
	minutes = _tstoi(buf);
	GetWindowText(p->hEdit3, buf, 10);
	seconds = _tstoi(buf);
	SYSTEMTIME st;
	GetLocalTime(&st); // ������� ������� ��������� �����
	if(st.wHour > hours || st.wHour == hours && st.wMinute > minutes || 
		st.wHour == hours && st.wMinute == minutes && st.wSecond > seconds)
	{
		CloseHandle(hTimer);
		EnableWindow(p->hButton, TRUE);
		EnableWindow(p->hEdit1, TRUE);
		EnableWindow(p->hEdit2, TRUE);
		EnableWindow(p->hEdit3, TRUE);
		return 0;
	}
	st.wHour = hours;
	st.wMinute = minutes;
	st.wSecond = seconds;
	FILETIME ft;
	SystemTimeToFileTime(&st, &ft); // ����������� ��������� SYSTEMTIME � FILETIME
	LocalFileTimeToFileTime(&ft, &ft); // ����������� ������� ����� � UTC-����� 
	SetWaitableTimer(hTimer, (LARGE_INTEGER *)&ft, 0, NULL, NULL, FALSE); // ������������� ������
	// ������� ������� ������� � ���������� ���������
	if(WaitForSingleObject(hTimer, INFINITE) == WAIT_OBJECT_0)
	{
		Shell_NotifyIcon(NIM_DELETE, p->pNID); // ������� ������ �� ����
		ShowWindow(p->hDialog, SW_NORMAL); // ��������������� ����
		SetForegroundWindow(p->hDialog); // ������������� ���� �� �������� ����
		for(int i = 0; i < 10; i++)
		{
			Beep(1000, 500);
			Sleep(1000);
		}
	}
	CancelWaitableTimer(hTimer); // �������� ������
	CloseHandle(hTimer); // ��������� ���������� �������
	EnableWindow(p->hButton, TRUE);
	EnableWindow(p->hEdit1, TRUE);
	EnableWindow(p->hEdit2, TRUE);
	EnableWindow(p->hEdit3, TRUE);
	return 0;
}


void CWaitableTimerDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_BUTTON1)
	{
		HANDLE h;
		h = CreateThread(NULL, 0, Thread, this, 0, NULL);
		CloseHandle(h);
		EnableWindow(hButton, FALSE);
		EnableWindow(hEdit1, FALSE);
		EnableWindow(hEdit2, FALSE);
		EnableWindow(hEdit3, FALSE);
		ShowWindow(hwnd, SW_HIDE); // ������ ����
		Shell_NotifyIcon(NIM_ADD, pNID); // ��������� ������ � ����
	}
}

void CWaitableTimerDlg::Cls_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	if(state == SIZE_MINIMIZED)
	{
		ShowWindow(hwnd, SW_HIDE); // ������ ����
		Shell_NotifyIcon(NIM_ADD, pNID); // ��������� ������ � ����
	}
}

// ���������� ����������������� ���������
void CWaitableTimerDlg::OnTrayIcon(WPARAM wp, LPARAM lp)
{
	// WPARAM - ������������� ������
	// LPARAM - ��������� �� ���� ��� ������������ ���������
	if(lp == WM_LBUTTONDBLCLK)
	{
		Shell_NotifyIcon(NIM_DELETE, pNID); // ������� ������ �� ����
		ShowWindow(hDialog, SW_NORMAL); // ��������������� ����
		SetForegroundWindow(hDialog); // ������������� ���� �� �������� ����
	}
}

BOOL CALLBACK CWaitableTimerDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_SIZE, ptr->Cls_OnSize);
	}
	// ���������������� ���������
	if(message == WM_ICON)
	{
		ptr->OnTrayIcon(wParam, lParam);
		return TRUE;
	}
	return FALSE;
}
