// SynchronizeThreads3.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

//
/*
1.	��� ����� �������?
2.	� ��� ����������� ������� ������������� ������� � ������� 
	���������?
3.	� ��� ������� �������� ������� �������� �� ����������� ������?
4.	����� ������� WinAPI ������������� ��� �������� ��������?
5.	����� ������� WinAPI ��������� �������� ���������� �������������
	��������?
6.	����� ������� WinAPI ������������ ��� ��������� ������� � 
	������������ �������?
7.	����������� ����� ������� WinAPI ����� ����������� ����������� 
	�������?
8.	����� ������� WinAPI ��������� ����� ������������ ����� 
	���������� �������� �������������?
9.	��� ����� �������? ��� �� ���������� �� ��������?
10.	� ��� ������� ������� ������������� ������ ������� � 
	�������������� ���������?
11.	����� ������� WinAPI ������������� ��� �������� ��������?
12.	����� ������� WinAPI ��������� �������� ���������� 
	������������� ��������?
13.	����� ������� WinAPI ��������� ��������� ������� �������� 
	����� ��������?
*/

// 1.	�������.
/*
������� (event) � ��� ������ ����, ��������������� ��� ������������� 
������ �������. 

���� ����� ������� ������������ ��� ����������� �� ��������� 
�����-���� ��������.

������� ������ ���� �����:
	�	�� ������� ������� (manual-reset events);
	�	� �������������� ������� (auto-reset events).
������� � ������ ������� ��������� ����������� ���������� ����� 
���������� ������ �������, � �� ����� ��� ������� � ��������������
�������  ������������ ���������� ������ ������ ������.

������ ���� �������� ��������� �������� API CreateEvent.

HANDLE CreateEvent(
	LPSECURITY_ATTRIBUTES eventAttributes,	// �������� �������
	BOOL bManualReset,						// ��� ������
	BOOL bInitialState,						// ��������� ���������
	LPCTSTR pszName							// ��� �������
);

�������� bManualReset ���������� ��� ��������������. 

�������� TRUE  ������� ������� �� ������� �������, 
� �������� FALSE � ������� � �������������� �������. 

�������� blnitialState ���������� ��������� ��������� ������� � 
��������� (TRUE) ��� ������� (FALSE). 

�������� pszName �������� ��������� �� ������, � ������� ����������
��� �������. 

���� pszName ����� �������� NULL, �� ��������� ������������� ������.

������������� ������ ������� � �������������� ������� ������� 
� ���������. 

�����������, ��� ��������� �����, ��������� ������ ���� ��������,
��������� ��� � ������� ��������� � ���������� � ����� ���������. 

�������� ������, ����� ���������� ������� � ��������� ���������. 
� ���� ������ ������ �����, ������� ���� �������� ������� � 
��������� ���������, ������������ � ���������� �����������.

������� ����� �������������� ��� ������������� ������� ������ 
���������.

�������� ���������� ������������� �������-������� ����� ������� 
�������  CreateEvent, ���� ������� ������� OpenEvent, ������ � 
��������� pszName ��� ������������� �������.

HANDLE OpenEvent(
	DWORD dwDesiredAccess,	// ����� ������� (EVENT_ALL_ACCESS �
							//������ ������)
	BOOL blnheritHandle,	// �������� ����������, ����� �� 
							// �������������
							// ���������� ������� (���� TRUE � 
							// ���������� �����������)
	LPCTSTR pszName			// ��� �������
);

������ �������, ���������� ����������� �������� ��������� ��� 
����������.  

��� �������� ������� � ��������� ��������� ������������ ������� API  
SetEvent.

BOOL SetEvent(
	HANDLE hEvent // ���������� ������� ���� ��������
);

��� �������� ������� � ������� ��������� ������������ ������� API 
ResetEvent.

BOOL ResetEvent(
	HANDLE hEvent // ���������� ������� ���� ��������
);

������� ��������, ��� ��� ������� � �������������� ������� ��������� 
��������� �������. 

����� �������� ������� ������������ ������� ������� �����������, 
�� �������������  ������������� ������������ � ������� ���������. 

��� ������� �� ������� ������� ��������������� ����������� �� 
����������, ������� ��� �������� � ������� ��������� ���������� 
������� ������� ResetEvent.

������� API PulseEvent, ������� ����� ����� �������������� ��� 
���������� ���������� �������.

BOOL PulseEvent(
	HANDLE hEvent // ���������� ������� ���� ��������
);

������� PulseEvent ����������� ������� � ��� �� ��������� ��� 
������� � ������� ���������. 

����� ������ ������� ����������� ����������������� ������ �������
SetEvent � ResetEvent. ��� ������ ������� PulseEvent ��� ������� 
�� ������� �������, ����� ������, ������ ���� ������, ���������� 
������������. 

��� ������ ���� ������� ������������� � ������� � �������������� 
������� ������������ ������ ���� �� ������ �������.
*/
// ������


// 2.	������ �������������
/*
������ ������������� ��� ��������� ������ (waitable timer) - ��� 
������ ����, ������� �������������� ��������� � ��������� ��������� 
� ������������ ����� ��� ����� ���������� ���������� �������.

��������� ������ ���������� ������� ������ ���� �����:
	�	�� ������� �������;
	�	� �������������� �������.

������ � ������ ������� ��������� ����������� ���������� ����� 
���������� ������ �������, � �� ����� ��� ������ � ��������������
�������  ������������ ���������� ������ ������ ������.

��� �������� ������� ������������� ���������� ������� ������� API 
CreateWaitableTimer.

HANDLE CreateWaitableTimer(
	LPSECURITY_ATTRIBUTES psa,	// �������� �������
	BOOL bManualReset,			// ��� ������
	LPCTSTR pszName				// ��� �������
);

�������� bManualReset ���������� ��� ������� �������������. 
�������� TRUE  ������� ������ �� ������� �������, � �������� 
FALSE � ������ � �������������� �������. 

�������� pszName �������� ��������� �� ������, � ������� ���������� 
��� ������� �������������. 

���� pszName ����� �������� NULL, �� ��������� ������������� ������.

�������� ���������� ������������� ������� ������������� ����� 
������� �������  API OpenWaitableTimer, ������ � ��������� pszName
��� ������������� �������.

HANDLE OpenWaitableTimer(
DWORD dwDesiredAccess,		// ����� ������� (TIMER_ALL_ACCESS � ������ ������)
	BOOL blnheritHandle,	// �������� ����������, ����� ��  �������������
							// ���������� ������� (���� TRUE � ���������� �����������)
	LPCTSTR pszName			// ��� �������
);

������ ���������� ������ ������ ��������� � ������� ���������. 
����� �������� �������, � ����� ������ �� ������ ������� � ���������
���������, ���������� ������� ������� API SetWaitableTimer.

BOOL SetWaitableTimer(
	HANDLE hTimer,					// ���������� �������
	const LARGE_INTEGER pDueTime,	// ����� ������� ������������ 
									// �������
	LONG lPeriod,					// ������ ������� � �������������
	PTIMERAPCROUTINE pfnCompletionRoutine,// ����� ���������� ����������                  // APC-��������� (asynchronous procedure call), ������� ���������� � ������ // �������� ������� � ���������� ���������
	LPVOID lpArgToCompletionRoutine,// ��������� �� ���������, 
									// ������������ � 
									// APC-���������
	BOOL fResume					// ���� ������ �������� �����
									// TRUE, ��� ������������ ������� 
									// ��������� ������ �� ������ ���
									// (���� �� ��������� � ������ 
									// ������), �    
									// ������������ ������, ���������
									// ���� ������.
);

��������� pDueTime � lPeriod ������������ ���������: ������ �� ��� 
������, ����� ������ ������ ��������� � ������ ���, ������ ����������,
��������� ����� ��� ������ ����������� � ����������.

������� ��������, ��� ���� ����� ����������, ����� ������ ��������
������ ���� ��� - ����� ������������ ����� ������� � ���������
��������� � ��� ������ ������� �� ����������. ��� ����� ����������
�������� 0 � ��������� lPeriod. ����� ����� ������� CloseHandle,
����� ������� ������, ���� ������������� ������ ��-������� �������
SetWaitableTimer � ������� �����������.

��� ������ ���������� ������� ����������� ������� API 
CancelWaitableTimer.

BOOL CancelWaitableTimer(
	HANDLE hTimer // ���������� ������� �������������
);
*/
// ������

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

