#include "InheritHandleDlg.h"

CInheritHandleDlg* CInheritHandleDlg::ptr = NULL;

CInheritHandleDlg::CInheritHandleDlg(void)
{
	ptr = this;
	// InheritHandle_ChildProcess.exe 101
	lstrcpy(CommandLine, GetCommandLine()); // ������� ��������� ������
	MessageBox(NULL, CommandLine, TEXT("Command line"), MB_OK);
	TCHAR seps[]   = TEXT(" ");
	TCHAR *token, *last;
	token = _tcstok(CommandLine, seps); // ��������� ��������� ������ �� ������� (����������� "������")
	while( token != NULL )
	{
		token = _tcstok(NULL, seps); // ��������� ��������� ������ �� ������� (����������� "������")
		if(token)
			last = token; // ��������� �� ��������� �������, �.�. �� ���������� ������� ����
	}
	hHandle = HANDLE(_tstoi(last));
}

CInheritHandleDlg::~CInheritHandleDlg(void)
{

}

void CInheritHandleDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

void MessageAboutError(DWORD dwError)
{
	LPVOID lpMsgBuf = NULL;
	TCHAR szBuf[300]; 
	//������� FormatMessage ����������� ������ ���������
	BOOL fOK = FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM /* ���� �������� �������, ��� ����� ������, ��������������� ���� ������, ������������ � ������� */
		| FORMAT_MESSAGE_ALLOCATE_BUFFER, // ����� �������� ��������������� ���� ������ ��� �������� ������
		NULL, // ��������� �� ������, ���������� ����� ���������
		dwError, // ��� ������
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // ����, �� ������� ��������� �������� ������ (���� ������������ �� ���������)
		(LPTSTR)&lpMsgBuf, // ��������� �� �����, � ������� ����� ������� ����� ���������
		0, // ����������� ������ ������ ��� ��������� ������ - ������ �������� �������
		NULL // ������ ���������� ��������������
		);
	if(lpMsgBuf != NULL)
	{
		wsprintf(szBuf, TEXT("������ %d: %s"), dwError, lpMsgBuf); 
		MessageBox(NULL,  szBuf, TEXT("��������� �� ������"), MB_OK | MB_ICONSTOP); 
		LocalFree(lpMsgBuf); // ����������� ������, ���������� ��������
	}
}

void CInheritHandleDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_BUTTON1)
	{
		TCHAR buf[100] = {0};
		DWORD dwRead = 0;
		/*
			������ �� �����

			BOOL WINAPI ReadFile(
				HANDLE hFile,				// ���������� �����
				LPVOID lpBuffer,			// ��������� �� �����, � ������� ����� �������� ������, 	
											// ��������� �� �����
				DWORD nNumberOfBytesToRead, // ������������ ���������� ���� ��� ������
				LPDWORD lpNumberOfBytesRead, // ��������� �� ����������, � ������� �����   	
				                             // �������� ����������� ���������� ��������� ����
				LPOVERLAPPED lpOverlapped	// ��������� �� ��������� OVERLAPPED
			);

		*/
		ReadFile(hHandle, buf, sizeof(buf), &dwRead, NULL); // ������ ������ �� �����, ���������� �������� ��� ����������� �� "��������"
		DWORD dwError = GetLastError();
		if ( dwError != 0 ) // ������ ������ �� �����
			MessageAboutError(dwError);
		else
		{
			MessageBox(hwnd, buf, TEXT("������������ ���������"), MB_OK | MB_ICONINFORMATION);
			CloseHandle(hHandle); // ��������� ��������� ������� ���� �����
		}
	}
}

BOOL CALLBACK CInheritHandleDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}