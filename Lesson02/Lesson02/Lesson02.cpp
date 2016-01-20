// Lesson02.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

// ������� Spy++
// ������ ���� ������
void ex01()
{
	// ����� ����
	/*
	BOOL		��������� ��� ������.����� ��������� ���� �� ���� �������� TRUE ��� FALSE.�������� 4 �����.
	BYTE		1 - ������� ����� ��� �����.
	INT			4 - � ������� ����� �� ������.
	LONG		4 - � ������� ����� �� ������.
	UINT		4 - � ������� ����� ��� �����.
	WORD		2 - � ������� ����� ��� �����.
	DWORD		4 - � ������� ����� ��� �����.
	*/
	WORD w;

	// ���������
	/*
	LPARAM		���������� ����� ���� ���������� � �������� ��������������� ��������� � ������� -
				���������� ������ - ���� ���������.� ��� ������ ���������� ����������
				������������� ��� ������� �������.�������� 4 �����.
	WPARAM		���������� ����� ���� ���������� � �������� ��������������� ��������� � ������� -
				���������� ������ - ���� ���������.� ��� ������ ���������� ����������
				������������� ��� ������� �������.
				�������� 4 �����.
	*/

	// ����
	// COLORREF	��� ������, ������������ ��� ������ � ������.�������� 4 �����.
	
	// �����������
	/*
	HANDLE		4 - � ������� �����, ������������ � �������� �����������.
	HBITMAP		���������� ���������� �����������.
	HBRUSH		���������� �����.
	HCURSOR		���������� �������.
	HDC			���������� ����������.
	HFONT		���������� ������.
	HICON		���������� ������.
	HINSTANCE	���������� ���������� ����������.
	HMENU		���������� ����.
	HWND		���������� ����.
	*/
	
	// ���������
	/*
	LPCSTR		4 - � ������� ��������� �� ����������� ������ ��������.
		        ��������� � ���������� LP ������ �������� �������� �����������.
	LPCWSTR		4 - � ������� ��������� �� ����������� Unicode - ������.
	LPSTR		4 - � ������� ��������� ������ ��������.
	LPWSTR		4 - � ������� ��������� �� Unicode - ������.
	LRESULT		�������� ���� LONG, ������������ ������� ����������
	*/	
}

// ���������� �������
void ex02()
{
	/*
	b	���������� ���(bool ��� BOOL)
	i	����� �����(������)
	n	����� �����(���������� ���� - ����)
	u	����� ����� ��� �����
	d	����� � ������� ���������
	sz	��������� ����������, ������������ �����
	p	���������
	lp	������� ���������
	a	������
	lpfn	������� ��������� �� �������
	h	����������
	cb	������� ������
	C	�����
	*/
	BOOL bIsShow;

	LPSTR lpszWinName = "MyWindow";

	//....

	bIsShow = true;
}

// ����� �������� ������� �Win32 Project�
// ����������� WinAPI-����������
void ex03()
{
	// �������� ������� ������� WinMain
	/*
	INT WINAPI WinMain(
		HINSTANCE hInst,	// ���������� ���������� ����������
		HINSTANCE hPrevInst,//����� 0 � ��������� ��� �������������
		LPTSTR lpszCmdLine, // ��������� �� ������, � ������� ���������� 
							//��������� ����������, ���� ��� �������� � ������ ��������� ������
		int nCmdShow		// ������ ������������ ���� ��� ������� ���������
	);
	*/
	/*
	������������ WINAPI ���������� ���������� � ������ �������.
	1. __cdecl � �� ������� ��������� ���������� ������� ���� ������� 
	   ���� ����� ���������� �������.
	2. __stdcall (WINAPI, CALLBACK) � �������� ����� ��������� ���������� 
	   ������� ���� �� ����� ������� ����.
	*/

	// ����� ���� WNDCLASSEX
	/*
	typedef struct tagWNDCLASSEX {
		UINT cbSize;			// ������ ������ ��������� � ������
		UINT style;				// ����� ������ ����
		WNDPROC lpfnWndProc;	// ��������� �� ������� ���� (������� ���������)
		int cbClsExtra;			// ����� �������������� ������, ������� ������
								//���� ������������ � ����� ��������� ������
		int cbWndExtra;			// ����� �������������� ������, ������� ������
								//���� ������������ ����� �� ����������� ����
		HINSTANCE hInstance;	// ���������� ���������� ����������, � �������
								//��������� ������� ��������� ��� ����� ������
		HICON hIcon;			// ���������� ������
		HCURSOR hCursor;		// ���������� �������
		HBRUSH hbrBackground;	//���������� �����, ������������ ��� �������� ���� ����
		LPCTSTR lpszMenuName;	// ��������� �� ������, ���������� ��� ����,
								//������������ �� ��������� ��� ����� ������
		LPCTSTR lpszClassName;	// ��������� �� ������, ���������� ��� ������ ����
		HICON hIconSm;			// ���������� ����� ������
	} WNDCLASSEX;

	*/

	// LoadIcon, LoadCursor, GetStockObject 

	// ����������� ������ ����
	/* ATOM RegisterClassEx(
		CONST WNDCLASS * lpWClass // ����� ��������� WNDCLASSEX
	 );*/

	// �������� ����.
	/*
	HWND CreateWindow(	
		LPCTSTR lpClassName, // ��� ������ ����
		LPCTSTR lpWinName, // ��������� ����
		DWORD dwStyle, // ����� ����
		int x, int �, // ���������� �������� ������ ����
		int Width, int Height, // ������� ����
		HWND hParent, // ���������� ������������� ����
		HMENU hMenu, // ���������� �������� ����
		HINSTANCE hThisInst, // ���������� ����������
		LPVOID lpszAdditional // ��������� �� �������������� ����������
	);*/

	// ����� ����
	/*
		WS_OVERLAPPED	����������� ���� � ������
		WS_MAXIMIZEBOX	������� ������ ���������
		WS_MINIMIZEBOX	������� ������ �����������
		WS_SYSMENU	������� ���������� ����
		WS_HSCROLL	������� �������������� ������ ���������
		WS_VSCROLL	������� ������������ ������ ���������
	*/

	// ����������� ����
	/* BOOL ShowWindow(
			HWND hWnd, //���������� ����
			int nCmdShow //������ ����������� ����
		);
	*/
	/*
		������ ����������� ����:
		SW_HIDE	������ ����
		SW_MAXIMIZE	���������� ����
		SW_MINIMIZE	�������� ����
		SW_SHOW	�������������� ���� � �������� � ��� ������� �������� � �������
		SW_RESTORE	���������� ���� � ���������� �������������
	*/
	/*
		UpdateWindow �������� ������� ��������� ��������� WM_PAINT, 
		������������ ���� ������������ ���� ���������� �������.

		BOOL UpdateWindow( HWND hWnd );
	*/

	// ���� ��������� ���������
	/*
		BOOL GetMessage(
		LPMSG lpMsg,//����� ��������� MSG, � ������� ���������� ��������� ���������
		HWND hwnd,	// ���������� ����, ������������ ���������
					// ������ �������� ����� ��������� ����� NULL, ��� ��������� ������� 
					// ��������� ��� ������ ���� ����������. 
		UINT min,	// ����������� ����� ������������  ���������
		UINT max	// ������������ ����� ������������ ���������
					// ���� ��� ��������� ��������� ����� ����, �� ������� �������� �� ������� 
					// ����� ��������� ���������. 
		);

		// ���������� ���������
		BOOL WINAPI TranslateMessage(
			_In_ const MSG *lpMsg
		);

		// ��������������� ���������
		LRESULT WINAPI DispatchMessage(
			_In_ const MSG *lpmsg
		);
	*/

	// ������� ���������
	// LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
	// PostQuitMessage(0) - ������� ��������� WM_QUIT
	// DefWindowProc - ��������� ������� ��������� ���������

}

// ���� ���������
void ex04()
{
	// MessageBox
	/*
	int MessageBox(
		HWND hWnd,			// ���������� ������������� ���� 
							// ���� ���� �������� ����� 0, �� ���� ��������� �� ����� ���� ���������. 
		LPCTSTR lpText,		// ��������� �� ������, ���������� �����, ������� ������ ���� 
							// ��������� � ���� 
		LPCTSTR lpCaption,	// ��������� �� ������, ������� ������������ � ���������  
							// ����������� ����
						    // ���� ���� �������� ����� NULL, �� �����������  �������� �� ��������� 
							// ��������� Error. 
		UINT uType			// ���� �������� �������� ����������� ��������, ������� ���������� �������� 
							// ���� ���������, ���������� ���� ������, ������� ������ ��������������, � 
							// �������������� ������ ����� � ������� ��������� 
	);
	*/

	// ���� ������
	/*
		MB_OK				���� �������� ������ ������ OK (�������������)
		MB_OKCANCEL			���� �������� ��� ������: OK (�������������) � Cancel (������)
		MB_RETRYCANCEL		���� �������� ��� ������: Retry � Cancel (������ � ������)
		MB_ABORTRETRYIGNORE	���� �������� ��� ������: Abort, Retry � Ignore (����, ������ � ����������)
		MB_YESNO			���� �������� ��� ������: Yes � No (�� � ���)
		MB_YESNOCANCEL		���� �������� ��� ������: Yes, No � Cancel (��, ��� � ������)
	*/

	// ������
	/*
		MB_ICONEXCLAMATION				// ������������ ������ ���������������� ����
		MB_ICONINFORMATION				// ������������ ������ ������������
		MB_ICONQUESTION					// ������������ ������ ��������������� ����
		MB_ICONSTOP (��� MB_ICONHAND)	// ������������ ������ � �����
	*/

	// ������������ ��������
	/*
		IDOK		// ���� ������ ������ OK
		IDCANCEL	// ���� ������ ������ Cancel (��� ������� <Esc>)
		IDABORT		// ���� ������ ������ Abort
		IDIGNORE	// ���� ������ ������ Ignore
		IDYES		// ���� ������ ������ Yes
		IDNO		// ���� ������ ������ No
		IDRETRY		// ���� ������ ������ Retry
		0			// ��������� ������ ��� �������� ���� ���������
	*/
}

// �������� �������
/*
1.	�������� ����������, ����������� ������� �� ����� ������� ������ � ������� ������������������ ���� 
��������� (���������� ���� ��������� � �� ����� ���). 
�� ��������� ���������� ���� ��������� ������ ������������ ������� ����� �������� �� �������� 
(����� ����� �������� � ������ �������� �� ���������� ���� ���������).

2.	�������� ����������, ������� ���������� ���������� ������������� ����� �� 1 �� 100. 
��� ������� � ������������ ������������ ���� ���������. ����� ����, ��� ����� ��������, 
���������� ������� ���������� �������, ��������������� ��� �����, � ������������ ������������ 
����������� ������� ��� ���, �� �������� ���������. ���� ��������� ������� �������� �������� 
� �������� � ������������ � ���������� ���������.

*/

int main()
{
    return 0;
}

