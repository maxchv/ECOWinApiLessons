#include "InheritHandleDlg.h"

CInheritHandleDlg* CInheritHandleDlg::ptr = NULL;

CInheritHandleDlg::CInheritHandleDlg(void)
{
	ptr = this;
}

CInheritHandleDlg::~CInheritHandleDlg(void)
{

}

void CInheritHandleDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

void CInheritHandleDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_BUTTON1)
	{
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES); // ������ ���������
		sa.lpSecurityDescriptor = 0; // ������� ������ �� ���������
		sa.bInheritHandle = TRUE; // ���������� ������� ���� "����" ����������� !!!
		HANDLE hHandle = CreateFile(
			TEXT("Test.txt"), // ���� � �����
			GENERIC_READ, // ������ ������
			0, // ������ ����������� ������������� �����
			&sa, // ������� ������
			OPEN_EXISTING, // �������� ������������� �����
			FILE_ATTRIBUTE_NORMAL, // ��������� ��� 
			NULL // ������ ������������ � ������-��������� ����������
			);
		if (hHandle == INVALID_HANDLE_VALUE) // ������ �������� �����
		{
			MessageBox(hwnd, TEXT("������ �������� ����� Test.txt"), TEXT("������"), MB_OK | MB_ICONERROR);
			return;
		}
		STARTUPINFO startin = {sizeof(STARTUPINFO)};
		PROCESS_INFORMATION info={0};
		TCHAR cmd[200];
		// ���������� ������� ���� ���������� ��������� �������� ����� ��������� ������
		wsprintf(cmd, TEXT("%s %d"), TEXT("InheritHandle_ChildProcess.exe"), hHandle);
		CreateProcess(
			NULL, // � �������� ����� ����� ��������� ������ ���������� ��������� ������� �� 2-�� ���������
			cmd, // ��������� ��������� ������, ����������, � ��� �����, ��� ������������ �����
			NULL, // �������� ������ �������� �� ���������
			NULL, // �������� ������ ������ �� ���������
			TRUE, // ������������ ��������� !!!
			0, // ����� ���������� �� ��������� - NORMAL_PRIORITY_CLASS 
			NULL, // ����� ��������� ����������� � ������������� �������� 
			NULL, // ������� ������� ����������� � ������������� �������� 
			&startin, // ������ ����������� �������� ����, � ����� ������ � ��������� ����
			&info // ���������� � ���������� ��������
			);
		CloseHandle(hHandle); // ����������� ��������� ������� ���� �����
		CloseHandle(info.hThread); // ����������� ��������� ������� ���� ������
		CloseHandle(info.hProcess); // ����������� ��������� ������� ���� ��������
	}
	else if(id == IDC_BUTTON2)
	{
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES); // ������ ���������
		sa.lpSecurityDescriptor = 0; // ������� ������ �� ���������
		sa.bInheritHandle = FALSE; // ���������� ������� ���� "����" ������������� !!!
		HANDLE hHandle = CreateFile(
			TEXT("Test.txt"), // ���� � �����
			GENERIC_READ, //������ ������
			0, // ������ ����������� ������������� �����
			&sa, // ������� ������
			OPEN_EXISTING, // �������� ������������� �����
			FILE_ATTRIBUTE_NORMAL, // ��������� ��� 
			NULL // ������ ������������ � ������-��������� ����������
			);
		if ( hHandle == INVALID_HANDLE_VALUE ) //������ �������� �����
			return;
		STARTUPINFO startin = {sizeof(STARTUPINFO)};
		PROCESS_INFORMATION info = {0};
		TCHAR cmd[200];
		// ���������� ������� ���� ���������� ��������� �������� ����� ��������� ������
		wsprintf(cmd, TEXT("%s %d"), TEXT("InheritHandle_ChildProcess.exe"), hHandle);
		CreateProcess(
			NULL, // � �������� ����� ����� ��������� ������ ���������� ��������� ������� �� 2-�� ���������
			cmd, // ��������� ��������� ������, ����������, � ��� �����, ��� ������������ �����
			NULL, // �������� ������ �������� �� ���������
			NULL, // �������� ������ ������ �� ���������
			TRUE, // ������������ ��������� !!!
			0, // ����� ���������� �� ��������� - NORMAL_PRIORITY_CLASS 
			NULL, // ����� ��������� ����������� � ������������� �������� 
			NULL, // ������� ������� ����������� � ������������� �������� 
			&startin, // ������ ����������� �������� ����, � ����� ������ � ��������� ����
			&info // ���������� � ���������� ��������
			);
		CloseHandle(hHandle); // ����������� ��������� ������� ���� �����
		CloseHandle(info.hThread); // ����������� ��������� ������� ���� ������
		CloseHandle(info.hProcess); // ����������� ��������� ������� ���� ��������
	}
	else if(id == IDC_BUTTON3)
	{
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES); // ������ ���������
		sa.lpSecurityDescriptor = 0; // ������� ������ �� ���������
		sa.bInheritHandle = TRUE; // ���������� ������� ���� "����" ����������� !!!
		HANDLE hHandle = CreateFile(
			TEXT("Test.txt"), // ���� � �����
			GENERIC_READ, // ������ ������
			0, // ������ ����������� ������������� �����
			&sa, // ������� ������
			OPEN_EXISTING, // �������� ������������� �����
			FILE_ATTRIBUTE_NORMAL, // ��������� ��� 
			NULL // ������ ������������ � ������-��������� ����������
			);
		if ( hHandle == INVALID_HANDLE_VALUE ) // ������ �������� �����
			return;
		STARTUPINFO startin = {sizeof(STARTUPINFO)};
		PROCESS_INFORMATION info={0};
		TCHAR cmd[200];
		// ���������� ������� ���� ���������� ��������� �������� ����� ��������� ������
		wsprintf(cmd, TEXT("%s %d"), TEXT("InheritHandle_ChildProcess.exe"), hHandle);
		CreateProcess(
			NULL, // � �������� ����� ����� ��������� ������ ���������� ��������� ������� �� 2-�� ���������
			cmd, // ��������� ��������� ������, ����������, � ��� �����, ��� ������������ �����
			NULL, // �������� ������ �������� �� ���������
			NULL, // �������� ������ ������ �� ���������
			FALSE, // ������������ ��������� !!!
			0, // ����� ���������� �� ��������� - NORMAL_PRIORITY_CLASS 
			NULL, // ����� ��������� ����������� � ������������� �������� 
			NULL, // ������� ������� ����������� � ������������� �������� 
			&startin, // ������ ����������� �������� ����, � ����� ������ � ��������� ����
			&info // ���������� � ���������� ��������
			);
		CloseHandle(hHandle); // ����������� ��������� ������� ���� �����
		CloseHandle(info.hThread); // ����������� ��������� ������� ���� ������
		CloseHandle(info.hProcess); // ����������� ��������� ������� ���� ��������
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