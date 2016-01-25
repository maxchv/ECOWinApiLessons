// Lesson03.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <bitset>
#include <Windows.h>
using namespace std;

// ���������� ����������� ���������
/*
1)	��� ����� ���� ������ ������� Spy++ ?
2)	������ ������������� ������������� ���������� ������� ��� ���������� ���������� ?
3)	��� ���������� ������������ __cdecl �� __stdcall (WINAPI, CALLBACK) ?
4)	������ ��������� ������������ WinAPI - ���������� ?
5)	����� �������� �������� ����������� � ������� ������� ��������� ?
6)	����� �������� ����������� � ����� ��������� ���������, � ��� ����� ������� ���� ���� ����������� ?
7)	����� ���� � ���������� ������ ������� ��������� ?
8)	��� ����� ������� ��������� ������(CALLBACK��������) ?
9)	����� �������� ������ ������� ������� ���������, ���� ��� ��������� ��������� ��������� ?
10)	����� �������� ������ ������� ������� ���������, ���� ��� ��������� ��������� �� ����������� ?
11)	��� ����� ���� ��������� ?
*/

// �������� ��������� ��������� ����
void ex01()
{
	// ��������� ����
	/*
		WM_LBUTTONDOWN � ������ ����� ������ ����;
		WM_MBUTTONDOWN  - ������ ������� ������ ����;
		WM_RBUTTONDOWN � ������ ������ ������ ����;
		WM_LBUTTONUP � �������� ����� ������ ����;
		WM_MBUTTONUP � �������� ������� ������ ����;
		WM_RBUTTONUP � �������� ������ ������ ����.
		WM_LBUTTONDBLCLK � ������� ������ ����� ������� ����;
		WM_MBUTTONDBLCLK � ������� ������ ������� ������� ����;
		WM_RBUTTONDBLCLK - ������� ������ ������ ������� ����.
		WM_MOUSEWHEEL - ��������� �������� �������� ���������.

		��� ���� ���� ��������� �������� ��������� lParam �������� ��������� ����. 
		��� ���� � ������� ����� (������� 2 �����) ��������� �������� ���������� �, 
		� � ������� ����� (������� 2 �����) � �������� ���������� �.

		��� �������� ����� ������� �� lParam ��� ������ �������� 
		LOWORD � HIWORD.
	*/
	// ������: ������������ � ����� 32 ������ ����� ��� 16 ������ �����
	int lParam;
	short x = 10;
	short y = 20;
	
	lParam = x;	
	cout << lParam << " " << bitset<32>(lParam) << endl;
	lParam = lParam << 16;
	cout << lParam << " " << bitset<32>(lParam) << endl;
	cout << "y "<< y << " " << bitset<32>(y) << endl;
	lParam = lParam | y;
	cout << lParam << " " << bitset<32>(lParam) << endl;
	
	int hWord = HIWORD(lParam); //(lParam >> 16) & 0xffff;
	int lWord = LOWORD(lParam); // lParam & 0xffff;	
	
	cout << hWord << " " << lWord << endl;/**/
}

// ����������� ����� ������ ���� 
void ex02()
{	
	// ��������� � ������� ������ ����� �������� ������ � ��� ������,
	// ���� ����� ���������������� ������ ���� �������� ���� CS_DBLCLKS
	// 
	// ������� ����� ������������ ������ ���� �����  ��������� ���� style
	// ���� CS_DBLCLKS ��� �������� ����� ����� ������������ ����

	
	// ������ ����� ����
	/*
	DWORD SetClassLong(
		HWND hWnd,		// ���������� ����
		int nIndex,		// ��������, ������������, ��� ����� ��������, ��������:
						// GCL_STYLE � �������� ����� ����,
						// GCL_HICON � �������� ���������� �������,
						// GCL_HCURSOR � �������� ���������� ������
		LONG dwNewLong	// ����� 32-������ ��������
	);

	*/

	// �������� ����� ����
	/*
	DWORD GetClassLong(
		HWND hWnd, // ���������� ����
		int nIndex // ��������, ������������, ��� ����� �������� �� WNDCLASSEX
		);
	*/

	// ������ ��������� ����� ������ ���� :
	/*
		UINT style = GetClassLong(hWnd, GCL_STYLE);
		SetClassLong(hWnd, GCL_STYLE, style | CS_DBLCLKS);
	*/
}


// �������� ��������� ������� ������
void ex03()
{
	// ���������:
	//		WM_KEYDOWN	- ������� ������ ��� ������
	//		WM_CHAR		- ������� ������
	//		WM_KEYUP	- ������� ������ ��� ��������
	//

	// ��� ��������� ��������� WM_CHAR �������������� ����������
	// ���������� � ����������:
	//
	//		1) wParam �������� ASCII-��� ������� �������
	//
	//		2) LOWORD (lParam) �������� ���������� ��������, 
	//						������������ ��� ����������� ������� 
	//						� ������� ���������
	//
	//		3) HIWORD (lParam) ������������ ����� ������� �����: 
	//			�	15:  ����� 1, ���� ������� ��������, � 0, ���� ��� ������.
	//			�	14:  ���������������, ���� ������� ��� ���� ������ ����� 
	//					 �������� ���������.
	//			�	13:  ��������������� � 1, ���� ������������� ������ 
	//                   ������� <Alt>.
	//			�	12 - 9 : ������������ ��������.
	//			�	8 :  ��������������� � 1, ���� ������ ������� 
	//                   �������������� ��� �������������� ����� ����������.
	//			�	7 - 0 : ��� ������� (scan - ���).
	
	// ��� ��������� ��������� WM_KEYDOWN � WM_KEYUP � wParam ���������� 
	// ����������� ���� ��� ������ ���������� ��������, ������ <Shift>,<Ctrl>,
	// <Alt> �������������� ������ (VK_LEFT, VK_DOWN, VK_SHIFT, VK_CTRL, 
	// VK_MENU, VK_RETURN, VK_TAB � �.�.). 
	// 
	// �������� ��������� ��������� ����������� ������� ����� � �������
	// ������� API GetKeyState.
	//
	//	SHORT GetKeyState(int nVirtKey);
	//	
	// �������� nVirtKey ����� ��� ����������� �������.
	// ������������ �������� � ��������� �������, ������� ������������ 
	// � ���� �����.
	// ���� ������� ��� ����� 1, �� ������� ������, � ���� ������, ��� ��������.
	// ���� ������� ��� ����� 1, �� ������� �����������, 
	// �.�.���������� �� ���������� ���������.
}

// ����� ������ � ����
void ex04()
{
	// ��������� ���� ���������� ��� ��������� ��������� WM_PAINT
	
	// � Windows ��� �������, ��������� ���-���� � ����, ���������� 
	// � �������� ��������� ���������� ��������� ���������� hdc, 
	// ������� ������������ ����� ��������� ���� HDC, ����������� �������� 
	// ������� ���������� ������. 
	// ��� ��������� ��������� ���������� ������������ �������:
	// 
	// HDC WINAPI BeginPaint(HWND hWnd, LPPAINTSTRUCT lpPaint);
	//
	// ��� ����������� ���������� ��� ����������� ���� ����� ������������ � 
	// ��������� PAINTSTRUCT:
	//		
	//		struct PAINTSTRUCT {
	//			HDC hdc; //�������� ����������
	//			BOOL fErase; //���� TRUE � ��� ���� ����������������
	//			RECT rcPaint; //�� �������������� �������������
	//			BOOL tRestore; // ������
	//			BOOL fIncUpdate; //������
	//			BYTE rgbReserved[32]; //������
	//		};
	
	//  ��������� ���������� ��������� ������� EndPaint():
	/*	
		BOOL WINAPI EndPaint(HWND hWnd, CONST PAINTSTRUCT *lpPaint);
		
		������� ������������ ������������ ��������� ����������.
	*/

	// �������� ����� � ���� ����� � ������� ������� Textout():
	//
	// BOOL WINAPI TextOutW(HDC hdc, int x, int y, LPCWSTR str, int len);

	// ����� ���������� ������������ ����, ��� ��������� ����������������. 
	// ��� ����� ������� ������� InvalidateRect():
	// 
	// BOOL WINAPI InvalidateRect(HWND hWnd, CONST RECT *lpRect, BOOL bErase);
	//
	// ������� ��������� ���������������� ������������� *lpRect � ���� hWnd.
	// ���� ������ ���������� ������� NULL, �� ��� �������� � ����������� 
	// ����� ����.
	// �������� TRUE �������� ��������� �������� ��������� ������������ 
	// ��� ����.
}

// ������ � ������
void ex05()
{
	// ����� ������ � ��������� ����
	/*
	BOOL SetWindowText (
		HWND hWnd,		 // ���������� ����, � ������� ������ ���� ������� �����
		LPCTSTR lpString //��������� �� ������, ���������� ����� �����
	);
	*/

	// GetWindowRect ��������� �������� ������� �������������� ����
	/*
	BOOL GetWindowRect(
		HWND hWnd,		//���������� ����
		LPRECT lpRect	//��������� �� ��������� RECT
	);
	*/

	// GetClientRect ��������� �������� ������� ��������������, 
	// ������������� ���������� (�������) ������� ����
	/*
	BOOL GetClientRect(
		HWND hWnd,		//���������� ����
		LPRECT lpRect	//��������� �� ��������� RECT
	);

	*/

	// MoveWindow ��������� ����������� ����, � ����� �������� ��� �������
	/*
	BOOL MoveWindow(
		HWND hWnd,//���������� ����
		int X, //����� ���������� � ������ �������� ���� ����
		int Y, //����� ���������� Y ������ �������� ���� ����

		int nWidth, //����� ������ ����
		int nHeight, //����� ������ ����
		BOOL bRepaint //������������� ����������� ����������� ����
	);
	*/

	// BringWindowToTop ������������ ���� � ��������� ��� � ������� ���������, 
	// ���� ��� ��������� ������ ������ ����
	/*
	BOOL BringWindowToTop(
		HWND hWnd //���������� ����
	);
	*/

	// FindWindow ������  ����  ��������  ������
	/*
	HWND FindWindow(
		LPCTSTR lpClassName, //��� ������ ����
		LPCTSTR lpWindowName // ��������� ����
	);
	*/

	// FindWindowEx, ������� ������ ��� ������ �������� ���� (��������, 
	// ��� ������ ��������� ���������� ����������� ����)
	/*
	HWND FindWindowEx(
		HWND hwndParent,		//���������� ������������� ����
		HWND hwndChildAfter,	//���������� ��������� ����, ����� �������� �������    //������ �����, ���� 0 � ��� ������, ������� � ������� ��������� ����
		LPCTSTR lpszClass,		//��� ������ ����
		LPCTSTR lpszWindow		// ��������� ����
	);

	*/
}


// ������������ �������
/*
1)	�������� ����������, � ������� ������ ������� ���������� ������� �����, 
    ������ � ������� ������ ����. ����������� ���������� ���������� �������� � ��������� ����.
2)	�����������, ��� ���������� �������������, ������� �������� �� 10 �������� ������� �� 
    ������ ���������� ������� ����. ���������� ��� ������� ����� ������ ���� �������� � ���������
	���� ��������� � ���, ��� ��������� ������ �����: ������ ��������������, ������� ��� �� ������� 
	��������������. ��� ������� ������ ������ ���� ���������� �������� � ��������� ���� ����������
	� ������� ���������� ������� ���� (������ � ������ ���������� ������� ����).
*/

// ��������� �������
/*
1)	�������� ����������, ����������� ��� ������� ����� ������ ���� �������� ����� � ��������� 
	���� ������������ ���������� ������������, � ��� ������� ������ ������ ���� �������� 
	������ ������ �����, ������� �� ��� �������.

2)	�������� ����������, ���������� ��������� �����������������:
	�	��� ������� ������ <Enter> ���� ��������������� � ����� ������� ���� 
		������ � ��������� (300�300);
	�	� ������� ������ ���������� �������� �������������� ����������� ����.
*/

int main()
{
	ex01();
    return 0;
}

