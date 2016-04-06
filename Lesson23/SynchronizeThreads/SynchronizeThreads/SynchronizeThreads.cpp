// SynchronizeThreads.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

// ���������� ����������� ���������
/*
1.	��� ����� �����? ����� ������ ������?
2.	��� ����� ���������������? ��� ���������� ��������������� �� ���������������?
3.	� ��� ����������� ������������ ���������� ������������� ���-�������?
4.	��  ����� ��������� ������� �����?
5.	��� ����� ��������� �������?
6.	����� ������� API ��������� ������� ��������� �����?
7.	����� ���������� ������� ���������� ������?
8.	����� ������ ���������� ������ ��������� �������� �������-���?
9.	����� ������� API ��������� ������������� ����� �� ���������-��� ������ �������?
10.	����������� ����� ������� API ����� ��������� �����?
11.	����������� ����� ������� API ����� ����������� ������ ����-��?
12.	� ��� ������� ���� ������������ ������������ �� ������ ����-�������?
13.	��� ������������ ��������� ��������� ������?
14.	����� ������� API ������������� ��� ��������� ������ ������-���� ��������?
15.	����� ������� API ������������� ��� ��������� ������ ������-���� ��������?
16.	����� ������� API ��������� �������� ������������� ��������� ������?
17.	����� ������� API ��������� �������� ������������� ��������� ������?
18.	����� ������� API ������������ ��� ��������� ����������� ��-������ ��������?
19.	����� ������� API ������������ ��� ��������� ����������� ��-������ ������?
20.	����� ������� API ������������ ��� ��������� �������������� �������� ��������?
21.	����� ������� API ������������ ��� ��������� �������������� �������� ������?
22.	��� ����� ��������� ������ ������? ����� ���������� ���� TLS?
23.	����� ������� ���������� Tool Help API  ��������� �������� ���������� � ������� � ������ �������?
*/

// 1.	������������ ������������� �������
/*
	��� ������ � ������� ������ ����� ������ � ��������� ��������� �������� �
	�����, ���������������� ������, ������, ����� � �.�. ���� ���� �� �������
	�������� ����������� ������ � ������-���� �������, ������ �������, �������
	���� ����� ���� ������, �� ������� ��������� ���� ������.

	� ������ �������, ������ �����������, ����� ������ �������������
	������������ ���������. ��������, ���� ���� ����� ���������� ���������� �
	����, ��� ������ ������ �� ������ � ���� ������ ������� ������������
	������ ����.

	����� �������, ��������� ������������� ���������������� ������ �������,
	�������� �������� ������  � ������ � ���� �� �������.
*/

LONG ballance = 100000;

DWORD WINAPI Credit(LPVOID arg)
{
	for (int i = 0; i < 100000; i++)
	{
		ballance -= 1;
	}
	return 0;
}

DWORD WINAPI Debet(LPVOID arg)
{
	for (int i = 0; i < 100000; i++)
	{
		ballance += 1;
	}
	return 0;
}

void ex01()
{
	Credit(NULL);
	Debet(NULL);

	_tprintf(TEXT("ballance: %d"), ballance);
}

/*
	������ �������� ����� ���� �������� ����� ������� ���������� �������,
	������� ����� ��������� ���� ��� ���������� ������� ������.

	��� ����� ������� ������ ���� ������������� ����������� ��������,
	� ������� ������� ������ ����� ����� ��������� � ��������� �������� ��
	������������� ���������������� �������, � ����� ����� ��������� ����������.

	����� �������, ������� �������� ��� �������� ������, ����� ������ ������
	����������������� ���� � ������:
		�	���������� ������������� ������������ ������� (����� �� ��������� ���);
		�	������������� ����������� ������ ������� � ���������� �����-����
			��������.

	C������������ ������� ������ ������������ � �������������� ����������
	�������������, ����� ���:
		�	��������� �������� API-������;
		�	����������� ������;
		�	�������;
		�	��������� �������;
		�	��������;
		�	��������.

	�� ���� � ����������� �������� �� �������� �����������
	� ������ �� ����������������� ���������� �������������.
*/

// 2.	������������� ������
/*
	������� ����� ������������� ������� ������� � ��������� ��������
	(atomic access) � ����������� �������� ������� ������������ � ���� �������.

	���������� ��������� ������:

	LONG g = 0; // ���������� ���������� ����������

	DWORD WINAPI Thread1( LPVOID lp )
	{
		++g;
		return 0;
	}

	DWORD WINAPI Thread2( LPVOID lp )
	{
		++g;
		return 0;
	}

	��� ����� ��������� ������� ���������: ��� ������� ����������� ��������
	���������� ���������� g �� 1. ��������� ��������� �������� ���������� g
	����� 0, ��, ����� ��� ������ �������� ���� ������, �������� ������
	���������� ������ ������ 2.

	������ � ���������� �������� ����� ���� ��������� ����.

	���������� ��� ��������� �������, ���������� �� ����������.

	--------------------------------------------------------------------------
	; �����1
	mov ax, g; � ������� ���������� �������� ���������� g
	inc ax; �������� �������� ������������� �� 1
	mov g, ax; � ���������� g ���������� �������� ��������

	; �����2
	mov ax, g; � ������� ���������� �������� ���������� g
	inc ax; �������� �������� ������������� �� 1
	mov g, ax; � ���������� g ���������� �������� ��������
	--------------------------------------------------------------------------

	������ ��� ������������ ������ ������� ������ ��������� ���������
	������������������ ���������� ������������� ����.

	--------------------------------------------------------------------------
	MOV EAX, g; ����������� ����� 1 - � ������� ���������� 0
	INC EAX; ����������� ����� 1 - �������� �������� ������������� �� 1
	MOV EAX, g; ����������� ����� 2 - � ������� ���������� 0
	INC EAX; ����������� ����� 2 - �������� �������� ������������� �� 1
	MOV g, EAX; ����������� ����� 1 - �������� 1 ���������� � ���������� g
	MOV g, EAX; ����������� ����� 2 - �������� 1 ���������� � ���������� g
	--------------------------------------------------------------------------

	� ����� ������ ���������� ���������� � ���������� g �������� 1.

	��� ������� ������ �������� ��������� ��������, ������������� ����������
	�������� ���������� g �� ������ ���������� �������, �. �. ��� ����������
	������� ��������.
*/
/*
	Win32 API ������������� ��������� Interlocked-������� ��� ����������
	������� ������������� ��������. ��� ���� ��� Interlocked-������� ��������
	��������� ������ ��� �������, ��� �� ��������� ��������� �� �������
	�������� ����� (DWORD).

	��� ���������� �������� ���������� �� ������� ������������� �������
	API Interlockedlncrement.

	LONG InterlockedIncrement(
		LPLONG lpAddend // ����� ����������, �������� �������
						// ����������������
	);

	��� ���������� �������� ���������� �� ������� ������������� �������
	API InterlockedDecrement.

	LONG InterlockedDecrement(
	LPLONG lpAddend		// ����� ����������, �������� ������� ����������������
	);

	������� API InterlockedExchange ���������� �������� �������
	�������� ���������� ���� LONG, ����� �������  ���������� � ������
	���������, ���������, ������������ �� ������ ���������.

	LONG InterlockedExchange(
		PLONG plTarget,// ����� ����������, �������� ������� ����������
		LONG lValue // �������� ��� ������
	);

	������� API InterlockedExchangeAdd ��������� � ��������
	����������, ����� �������  ���������� � ������ ���������,
	��������, ������������ �� ������ ���������:

	LONG InterlockedExchangeAdd(
		PLONG plAddend, // ����� ����������, �������� ������� ����������
		LONG lIncrement // ��������, �� ������� ������������� ����������
	);

	������� API InterlockedCompareExchange ��������� �������� ��������� �
	������������ �� ���������� ���������:

	LONG InterlockedCompareExchange(
		LPLONG  plDestination, // ����� ����������, �������� �������
								// ����������
		LONG lExchange,		   // �������� ��� ������
		LONG lComperand		   // �������� ��� ���������
	);

	���� �������� ����������, ����� ������� ���������� � ������ ���������,
	��������� �� ���������, ������������ � ������� ���������, �� ���
	����������  ���������, ������������ �� ������ ���������.

*/

// ������

DWORD WINAPI Credit2(LPVOID arg)
{
	for (int i = 0; i < 100000; i++)
	{
		ballance -= 1;
	}
	return 0;
}

DWORD WINAPI Debet2(LPVOID arg)
{
	for (int i = 0; i < 100000; i++)
	{
		ballance += 1;
	}
	return 0;
}

void ex02()
{
	HANDLE t[2];
	t[0] = CreateThread(NULL, 0, Credit2, NULL, NULL, NULL);
	t[1] = CreateThread(NULL, 0, Debet2, NULL, NULL, NULL);

	WaitForMultipleObjects(2, t, TRUE, INFINITE);

	_tprintf(TEXT("ballance: %d"), ballance);
}

// 3.	����������� ������

/*
	����������� ������ (critical section) � ��� ��������� ������� ����,
	��������� ������������ ������� � ����� - �� ����� ������.

	��� ��������� ������� ���, ����� ������������� ������ ���� �����
	������� ������ � ������������� �������.

	���� � ������������ ������ ������� ��������� ������� ����������
	�������� ������ � ����������� ������, ��  �������� ��� ��� �����
	������������ ������ ������ �� �������, � ��� ��������� �����
	���������� � ��������� �������� �� ��� ���, ���� ������� ��
	�����������.

	��� ������������� ����������� ������ ���������� ����������
	���������� ���� CRITICAL_SECTION.

	��������� ��� ���������� ������ ���������� � ������� ���������
	���  ������� ������������� �� ������, ������ �� ��������� ����������.

	����� ����, ���  ���������� ������� ���������������� �� �� �������
	���������� � �������  ������� API InitializeCriticalSection :

	void InitializeCriticalSection(
		LPCRITICAL_SECTION lpCriticalSection // ��������� �� ������
											 // �����������
											 // ������
	);

	����� ��������� ����������� �������, ����� ������ ������� ������� API
	EnterCriticalSection.


	void EnterCriticalSection(
		LPCRITICAL_SECTION lpCriticalSection // ��������� �� ������ �����������
											 // ������
	);

	����� ��������, ��� ���� ����������� ������ �� ������������ � ������
	������ ������ �������, �� ������� ����� ����������� �� � ���������
	���������� ���� ������, ������� ������� ����� ����� ������ �������
	EnterCriticalSection.

	��� ���� ����������� ������ ������������ �������� ��� �������.

	���� ����������� ������ � ������ ������ ��� ������������ ������ �������,
	�� ������� ����� ����������� �� ��� ���, ���� ������ �� ����� �����������
	�������� API LeaveCriticalSection.


	void LeaveCriticalSection(
		LPCRITICAL_SECTION lpCriticalSection // ��������� �� ������ �����������
											 // ������
	);

	������� �����������, ��� ����� ������� LeaveCriticalSection
	���������� ����� ����������� ������.

	��� ���� ����������� ������ ������������ �������� ��� ���������.

	��� ������ ����� �������� �������� ��� ����������� �������, ������
	������ ������� � ���� ������ �����������.

	��� ���� ����� �����, ����� ����� ���������� ����������� ������ ����
	�����������.

	��� �������� �������� ��������� ����������� ������ ����������.

	���� ����������� ������ ������ �� �����, �� ������������ �� �������
	���������� ���������� ������� ������� DeleteCriticalSection.

	void DeleteCriticalSection(
		LPCRITICAL_SECTION lpCriticalSection // ��������� �� ������
											 // �����������
											 // ������
	);

	����� ������������� ���� ������� WinAPI ������������� �������
	TryEnterCriticalSection, ������� ��������� ����������� �������
	���������  ����������� ������.

	void TryEnterCriticalSection(
		LPCRITICAL_SECTION lpCriticalSection // ��������� �� ������
											 //�����������
											 // ������
	);

	��������:

	CRITICAL_SECTION cs;
	...
	BOOL bAcquired = TryEnterCriticalSection(&cs);
	if(bAcquired)
	{
		// ���������� ���� ����������� ������ (�����������
		// ������ � �������)
	}
	else
	{
		// �������� ��� ����������� ������� ����������
	}

	��� ������� �� ���������������� �������, ���� ����������� ������
	��������, �� ����� ������ � ��� ������ � ��������� �� ���, �������
	����������� ������ � �������� �������.

	���� ������ ����������, �� ����� �� �����������, ��� � ������
	���������� ������� EnterCriticalSection, � ���������� ������ �������,
	�� ��� �������� ����� else.

*/

CRITICAL_SECTION cs;

DWORD WINAPI Credit3(LPVOID arg)
{
	for (int i = 0; i < 100000; i++)
	{

		ballance -= 1;

	}
	return 0;
}

DWORD WINAPI Debet3(LPVOID arg)
{
	for (int i = 0; i < 100000; i++)
	{

		ballance += 1;

	}
	return 0;
}
// ������
void ex03()
{
	HANDLE t[2];
	t[0] = CreateThread(NULL, 0, Credit3, NULL, NULL, NULL);
	t[1] = CreateThread(NULL, 0, Debet3, NULL, NULL, NULL);

	WaitForMultipleObjects(2, t, TRUE, INFINITE);

	_tprintf(TEXT("ballance: %d"), ballance);
}

/*
	������� � ������������ �������� ��� �������� Interlocked-�������,
	��������� �� ������������� � ����� ����.

	������� ��� ���� ������������� �������� �������������� �
	���������������� ������.

	��� ���������� ������� ��������� ����������. ������ �������
	����������� ����� ������������� �������� ������������� ��
	���������� ��� �������, ������������� ������ ���������.
*/

int main()
{

	//ex01();
	//ex02();
	ex03();
	return 0;
}

