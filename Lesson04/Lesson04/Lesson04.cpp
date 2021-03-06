//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#pragma warning(disable: 4996)
using namespace std;
// ���������� ����������� ���������

/*
1)	����� ������ ��������� ����? ����� �������������� ���������� 
    �������� � ����� �����������?
2)	����� ���������� ������������ ���������? ����� �������������� ���������� 
    �������� � ����� �����������?
3)	� ����� ������ ������� ������������ ��������� WM_CHAR, 
    � � ����� ������ � WM_KEYDOWN � WM_KEYUP?
4)	����� �������� ����� ���������� ��������� ��������� ����������� �������?
5)	����� �������� ����� ������� ����� � ��������� ����?
6)	��� ���������� ������� GetWindowRect �� ������� GetClientRect?
7)	��� ������������� �������� ���������� ��������� ����� � ���������� 
    ���������� ������������ ������ �������� ���� ������� ������� ��������� ���� ?
8)	��� ��������� �������� ��������������?
9)	����� ������� ����� ����������� ����, � ����� �������� ��� ������� ?
10)	����� ������� ��������� �������� ���������� ���� �������� ������? 
    ����� ���������� ���������� �������� � ��� �������?
11)	����� ������� ��������� �������� ���������� ��������� ����? 
    ����� ���������� ���������� �������� � ��� �������?
12)	� ������� ������ �������� ����� ���������� ��������� � ����� ����?
*/

// ������ � ��������
void ex01()
{
	//��� ��������� ������� ���������� ������������ ������� API SetTimer:
	/*
	UINT SetTimer(
		HWND hwnd,		// ���������� ����, ������� ���������� ������������ ������
		UINT nID,		// ������������� ���������������� ������� 
		UINT wLength,	// ��������� �������� ��� ������� � �������������
		TIMEPROC lpTFunc// ��������� �� ������� - ���������� ���������� �������
		);

	�������-���������� ������� ������ ����� ��������� ��������:

	VOID CALLBACK TimerProc(
		HWND hwnd,			// ���������� ����, ������� ���������� ������������ ������
		UINT uMsg,			// ������������� ��������� WM_TIMER
		UINT_PTR idEvent,	// ������������� ���������������� �������
		DWORD dwTime		// ��������� �������� ��� ������� � �������������
	)
	*/
	/*
	���� ��������� lpTFunc ����� NULL, ��, ��� ��������� ��������� ������� ����� 
	���������� ������� ��������� �������� ���� ����������. 
	� ���� ������ ������ ��� �� ��������� ��������� ���������� ��������� � ������� 
	��������� ��������� ����� ���������� ��������� WM_TIMER
	*/

	/*
	������� �������:

	BOOL KillTimer(
			HWND hwnd, // ���������� ����, ������������� ������
			UINT nID   // ������������� �������
		);
	*/
}

// ������������ ����.
void ex02()
{
	//��� ������������ ���� ���� �������� ������:
	/*
	
	BOOL EnumWindows(
		WNDENUMPROC lpEnumFunc, // ��������� �� ������� ��������� ������
		LPARAM lParam // ��������, ������������ � ������� ��������� ������
		);
		
	�������� ������� ��������� ������ ����� ��������� ���:

	BOOL CALLBACK EnumWindowsProc(
		HWND hwnd, // ���������� ���������� �������������� ���� �������� ������
		LPARAM lParam  // ��������, ���������� � CALLBACK-�������
		);

	��� ����������� ������������ ����, ������� ������ ���������� TRUE, � 
	��������� ������ ������������ �����������.
	*/

	//��� ������������ �������� ���� ���������� ���� �������� ������:
	/*
	BOOL EnumChildWindows(
		HWND hWndParent, // ���������� ������������� ����
		WNDENUMPROC lpEnumFunc, // ��������� �� ������� ��������� ������
		LPARAM lParam // ��������, ������������ � ������� ��������� ������
		);

	�������� ������� ��������� ������ ����� ��������� ���:

	BOOL CALLBACK EnumChildProc(
		HWND hwnd, // ���������� ���������� �������������� ����
		LPARAM lParam  // ��������, ���������� � CALLBACK-�������
		);
	
	��� ����������� ������������ ����, CALLBACK�������� ������ ���������� TRUE, 
	� ��������� ������ ������������ �����������.
	*/

	/*
	�������� ���������� � ����:

	������� GetWindowText �������� ����� ������ ��������� ������������� ���� 
	(���� ��� ����� ��) � �����. ���� ������������ ���� - ������� ����������, 
	����� �������� ���������� ����������.

	int GetWindowText
	(
		HWND hWnd,			// ���������� ���� ��� �������� ���������� � �������
		LPTSTR lpString,	// ����� ������ ��� ������
		int nMaxCount 		// ������������ ����� �������� ��� �����������
	);

	������� GetClassName �������� �������� ������ ���������� ����.

	int GetClassName(
		HWND hWnd,			// ���������� ����
		LPTSTR lpClassName,	// ����� ������ ��� ����� ������
		int nMaxCount 		// ������ ������ � ��������
	);
	*/

}

// ������� ����������.
void ex03()
{
	/*
		��� ������������� ������� ������ ���� ���������� � ����� �������� �������� 
		(resource script), ������� �������� ASCII-������ � ����������� .��.
	*/

	// �����������.
	/*
		����������� (������) � ��� ��������� ��������� �����������, ����������� Windows 
		��� ����������� ������������� ����������, ������ � �����. ���� ����� ��� 
		���������� ������� ������ ��������� ������� ��������:        
			16 x 16 �������� ��� ����� ������ � 
			32 � 32 ������� ��� ����������� ������.
	*/

	/*
	��� �������� ������ ����������� � �������� ���������� ���������� ������ LoadIcon:

	HICON LoadIcon(
		HINSTANCE hInst, //���������� ���������� ����������, ����������� ������
		LPCTSTR lpszName //������, ���������� ��� ������
		);

	HMODULE GetModuleHandle(
		LPCTSTR lpModuleName // ��� DLL ������ 
		);

	���� �������� ������� GetModuleHandle �������, �� ������������ ���������� ����������
	����������.

	��������� ��� ������ ������������ ����� ������������� ������������� 
	(��������, IDI_ICON1), �� ��� ����� ������������� � ������ � ������� �������  
	MAKEINTRESOURCE (make an integer into resource string):

		#define MAKEINTRESOURCE(i)  (LPTSTR) ((DWORD) ((WORD) (i)))
	*/

	// ������.
	/*
		������ � ��� ����������� �������� 32 � 32 �������, ������� ��������  ���������  
		��������� ����. ������ �� ������ ����� �� ������. ������� ������� ����������� 
		� ������� �������� ����� (hotspot).
	*/
	/*
	��� ������������� � ��������� �������, ������������ � �������� ����������, ������ 
	������� ��������� � ������� ������� LoadCursor:

		HCURSOR LoadCursor (
			HINSTANCE hInst, // ���������� ���������� ����������, ����������� ������
			LPCTSTR lpszName // ������, ���������� ��� �������
		);

	��� ������������� ��������� ����� ������� � ����������� �� ���
	��������������� ����������� ������� SetCursor:

		HCURSOR SetCursor(
			HCURSOR hCursor // ���������� �������
		);
	*/

	/*
	��� ��������� ����� ���� ����������� ������� SetClassLong. ������:

		HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
		SetClassLong(hWnd, GCL_HICON, LONG(hIcon));
	
		HCURSOR hCursor1 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
		SetClassLong(hWnd, GCL_HCURSOR, LONG(hCursor1));


	*/
}

// ��������� ������.
void ex04()
{
	/*��� ������������� ������ �������� ���� ��� � 32-������ �����, 
	������� ����� ��������, ������ ������� GetLastError.
	
	���� GetLastError ���������� ������� ��������, ��� ��������, ��� ��������������
	����� ������� Windows ���������� �������.
	*/
	FILE *f = fopen("somefile.txt", "r");
	DWORD error = GetLastError();
	if (error)
	{
		cout << "Error: " << error << endl;
		LPVOID lpMsgBuf = NULL;
		TCHAR szBuf[300];		
		//������� FormatMessage ����������� ������ ���������
		BOOL fOK = FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM, 
			NULL,
			error,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // ������������� �����, �� 	������� ��������� �������� ������ ,
			szBuf, // ��������� �� �����, � ������� ��������� ����� � 	��������� ������ ,
			299, // ������ �������� �������
			NULL // ������ ���������� ��������������
			);
		char buff[300]; 
		AnsiToOem(szBuf, buff); // ��������������� � 866
		cout << buff << endl;
	}
	/*
	��� ��������� �������� ������ �� ������ ���� ������ ����������  FormatMessage:

	DWORD FormatMessage(
		DWORD dwFlags,      // ����� ������� ������, ������� ���������� ���������   	// ������� �������� ��������������, � ����� ������ �������������      	// 2-�� ��������� lpSource
		LPCVOID lpSource,   // ��������� �� ������, ���������� ��������� �� ������
		DWORD dwMessageId,  // ��� ������
		DWORD dwLanguageId, // ������������� �����, �� ������� ��������� 		
		                    // �������� ������
		LPTSTR lpBuffer,    // �������� �����, ������� ���������� ��������, ����
						    // � 1-� ��������� ������ ���� FORMAT_MESSAGE_ALLOCATE_BUFFER
		DWORD nSize,        // ����� ��������, ������������ � �������� �����,
					        // ���� ����������� ������ ����������� ������, ����
					        // � 1-� ��������� ������ ���� FORMAT_MESSAGE_ALLOCATE_BUFFER
		va_list* Arguments // ������ ���������� ��������������
	);

	������:
	DWORD dwError = GetLastError(); // ������� ��� ��������� ������
	LPVOID lpMsgBuf = NULL;
	TCHAR szBuf[300];
	//������� FormatMessage ����������� ������ ���������
	BOOL fOK = FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM // ���� �������� �������, ��� ����� ������, 	��������������� ���� ������, ������������ � ������� 
			| FORMAT_MESSAGE_ALLOCATE_BUFFER // ���������� �������� ��������������� 	���� ������ ��� �������� ������ � ��������� ������ ,
			NULL // ����� � ��������� ������ ����� ���������� � ������, ���������� 	��������. ����� �������� � 5-� ��������� ,
			dwError // ��� ������ ,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT) // ������������� �����, �� 	������� ��������� �������� ������ ,
			(LPTSTR)&lpMsgBuf // ��������� �� �����, � ������� ��������� ����� � 	��������� ������ ,
			0, // ������ �������� �������
			NULL // ������ ���������� ��������������
			);
			if (lpMsgBuf != NULL)
			{
				wsprintf(szBuf, TEXT("������ %d: %s"), dwError, lpMsgBuf);
				MessageBox(hDialog, szBuf, TEXT("��������� �� ������"), MB_OK | MB_ICONSTOP);
				LocalFree(lpMsgBuf); // ��������� ������, ���������� ��������
			}
	*/
}

// ������������ �����.
/*
�������� ����������, ���������� ��������� �����������������:
�	����� ������� ������� <Enter> ����� ������ ������� (��� ���� �����-����� �������) ���������� ���� �� ������ �������������,  ��������� ��������� �������;
�	����� ������� ������� <Esc> ������ ������� ���������������.
*/

// �������� �������.
/*
1.	��������  ����������,  ����������  ��������� �����������������:
	��� ������� ������� <Enter> ������� ���� ��������������� � ����� ������� ���� 
	������ � ��������� (300�300) � �������� ������������ �� ��������� ������ 
	� ����������� ���������;
	��� ������� ������� <Esc> ����������� ���� ������������.

2.	��������  ����������,  ����������  ���������    �����������������:
	��� ���������������� ������� ������� <Enter> �������� ���� �������� ���� 
	���������� ������������ ��������������;
	��� ���������������� ������� ������� <Esc> �������� ���� ����������������� � 
	�������� �������, �.�. �������� ����, ������� ���������������� ���������, 
	������ ����� �������������.
*/


int main(int argc, TCHAR* argv[])
{
	ex04();
	return 0;
}

