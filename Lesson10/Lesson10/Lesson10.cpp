// Lesson10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// ���������� ����������� ���������
/*
1)	��� ���������� ������� ������ �� ���������������� ������?
2)	������ ��������� ����� ������� ������ �� �������?
3)	����� ��������� ����� � ���������� ��������� ��� ������ �������� ������?
4)	����� ����������� �� ������ �������� ������������� ���� (�������) ��� 
    ��������� �������� ������?
5)	����� ��������� ���������� ��������� ������ ��� ����������, ������� 
    � �������� ������?
6)	����� ��������� ���������� ��������� ������ ��� ������ � ��� ��������� ������?
7)	����� ��������� ���������� ��������� ������, ����� ���������� ������ 
    ���������� �������� ������?
8)	��� ���������� ������� ������� ������?
9)	����� ��������� ���������� ��������� ������, ����� ���������� 
    ���������� ��������� � ���?
10)	����� ��������� ���������� ��������� ������, ����� ��� ��������?
11)	����� ��������� ���������� ��������� ������, ����� �������� ����� 
    ���������� ��������?
12)	����� ������� ���������� ������� ����� ���������� ������, 
    ������� �������� � ������ ������?
13)	����� ������� ���������� ��� ���������� �� ��������� ����� 
    ��������� ����?
*/

// ������������ �����.
/*
	������������ ��������� (Message crackers) �������� ��������� 
	������� ���������, � ���� ������� ������ ���� �������� 
	�������� switch, ���������� ������� ����� ����� ����, ��� 
	�������� �������� ������� ����� ����������������. 
	
	������������ ��������� ��������� ������� �������� switch �� 
	��������� ������� � �� ����� �� ������� ���������. 
	��� ����������� �������� ���������� ��������� ����.

	������ (windowsx.h)

	#define	HANDLE_MSG(hwnd, message, fn)   
		case (message): 
			return HANDLE_##message((hwnd), (wParam), 
			                         (lParam), (fn))
*/
/*
	��� ��������� ��������� WM_CLOSE ���������� � ��������� 
	switch ������� ��������� ������� ������ HANDLE_MSG

	BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch(message)
		{
			HANDLE_MSG(hwnd, WM_CLOSE, Cls_OnClose);			
		}
		return FALSE;
	}

	� ���� ���������� ������������� ������������������ 
	��������� WM_CLOSE:

	void Cls_OnClose(HWND hwnd)
	{
		EndDialog(hwnd, 0);
	}
*/

/*
	������� HANDLE_##message (��������, HANDLE_WM_CLOSE, 
	HANDLE_WM_COMMAND � �.�.) ������������ ����� ������������ 
	���������. ��� ������������� ���������� ���������� 
	wParam � lParam, ��������� ������ �������������� ����� � 
	�������� ��������������� ������� � ���������� ��������� 
	(��������, Cls_OnClose). 
	
	��������, ������ HANDLE_WM_CLOSE �������� ��������� �������:

	#define HANDLE_WM_CLOSE(hwnd, wParam, lParam, fn) 
									((fn)(hwnd), 0L)

	������� FORWARD_WM_* - ��� ������������� ��������� 
	(message forwarder), ������� ������������ � ��� ������, 
	�����  ��� ��������� ��������� ���������� ������� 
	����������� ���������� �� ���������.

	// ��������� �� ���������
	FORWARD_WM_COMMAND(hwnd, id, hwndCtl, codeNotify, DefWindowProc);
*/

/*
������������ ������������� ���������:
�	���������� ����� ����� �������������� ����� � 
	���� ����������, � ����� ����������� ��� ���� ������;
�	������������� ����;
�	�������� � �������� � ������������� ��� ���������� 
	����������.
*/

// ����� �������� ����������.
/*
	����� �������� ����������, ���������� � ���������� 
	��������� ���������� ������ ����������� 
	(common control library),  ��������� ������� �������� 
	����������  �  ��������� ������� ����������� ����� 
	����������� ���. 
	
	� ����� ��������� ���������� ��������� 
		- ������ ������������ (Toolbar)
		- ���� ��������� (Tooltip)
		- ��������� (Progress Bar)
		- ������� (Spin Control)
		- ������ ��������� (Status Bar) � ������. 
	
	���������� ��������� ���������� ������ ����������� 
	����������� � ���� ����������� ����������� 
	���������� comctl32.dll.
*/

/*
	������� ����� �������� ���������� ���������� � ������ 
	���������� ���������� ������� � ���� ���������� 
	�������������� ���������. 
	
	������� �������� ���������� �������� ��������� 
	WM_COMMAND, � ����� ��������  ����������  ����� ������ 
	�������� ��������� WM_NOTIFY.
*/
/*
	����� ������������ � ���������� �����-���� ������� 
	���������� ������ �����������, ������� ����� ������� 
	������� API InitCommonControlsEx, ������� ������������ 
	������� ������ ��������� ����������.

	BOOL InitCommonControlsEx(
		LPINITCOMMONCONTROLSEX lpInitCtrls
	);
	https://msdn.microsoft.com/en-us/library/windows/desktop/bb775697%28v=vs.85%29.aspx

	��������� INITCOMMONCONTROLSEX ����� ��������� �����������:

	typedef struct tagINITCOMMONCONTROLSEX {
		DWORD dwSize; // ������ ��������� � ������
		DWORD dwICC; // ����� �������� ������� �� DLL
	} INITCOMMONCONTROLSEX, *LPINITCOMMONCONTROLSEX;


	������ �������� ����� ��������� ���� ��� ��������� ��������:
	ICC_ANIMATE_CLASS			animate
	ICC_BAR_CLASSES				toolbar, status bar, 
								slider, tooltip
	ICC_LISTVIEW_CLASSES		list view, header
	ICC_PROGRESS_CLASS			progress bar
	ICC_TAB_CLASSES				tab, tooltip
	ICC_TREEVIEW_CLASSES		tree view, tooltip
	ICC_UPDOWN_CLASS			up-down
	ICC_WIN95_CLASSES			animate, header, hot key, 
								list view, progress bar, 
								status bar, tab, tooltip, 
								toolbar, slider, tree view, 
								up-down
	https://msdn.microsoft.com/en-us/library/windows/desktop/bb775507%28v=vs.85%29.aspx
		
	���  ����  �����  ������������  �  ����������  �������
	InitCommonControlsEx ���������� ���������� ������������ 
	���� commctrl.h, � ������� ��� �������. 
	
	������ ����� ������� ������� ������������ ������������ 
	������������� ����� comctl32.lib, ����������� ������ �� 
	DLL � �������� ����������� � ��� �������.
	
			#pragma comment(lib,"comctl32")
*/

// ������� ���������� ���������� ��������(Progress Control).
/*
	������� ���������� Progress Control ������ ������������ � 
	����������� ��� �����������  �������� ���������� ��������� 
	���������� ��������

	��������
	https://msdn.microsoft.com/en-us/library/windows/desktop/bb760816%28v=vs.85%29.aspx

	HWND hProgress1 = CreateWindowEx(0, PROGRESS_CLASS, NULL,
								WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
								LEFT, TOP, WIDTH, HEIGHT,
								hwndParent, NULL, GetModuleHandle(NULL), NULL);
								
	�����
	https://msdn.microsoft.com/en-us/library/windows/desktop/bb760820%28v=vs.85%29.aspx

*/

// ��������� ���������� ��������.
/*
	��� ���������� ����������� �������� ������������ ���������
	https://msdn.microsoft.com/en-us/library/windows/desktop/ff485990%28v=vs.85%29.aspx
	
	��� ���������	wParam		lParam		��������
	============== ======== ============= =============================
	PBM_SETRANGE	0		MAKELPARAM
							(wMin, wMax)	��������� ��������� ��� 
											����������
	PBM_SETPOS		nNewPos		0			���������  �������  ������� 
											����������
	PBM_DELTAPOS	nInc		0			��������� ������� ������� 
											������������ �������� nInc
	PBM_SETSTEP		nStepInc	0			��������� ���� ���������� 
											��� ����������
	PBM_STEPIT		0			0			��������� ������� ������� 
											������������ ���� nStepInc
	PBM_SETBARCOLOR	0		(COLORREF)
							 clrBar			��������� ����� ����������� 
											���������������
	PBM_SETBKCOLOR	0		(COLORREF)
							clrBk			��������� ����� ���� ����������

*/

/*
	��� ��������� ��������� ���������� ������� ��������� ��� 
	��������� PBM_SETRANGE, ������ � ���������   lParam ������� 
	���������. 
	
	��� ���� ����� ��������� �������������� ���������� � ��������� 
	wParam � lParam ������ ������������ ��������� �������:

		WPARAM MAKEWPARAM( WORD wLow, WORD wHigh );
		
		LPARAM MAKELPARAM( WORD wLow, WORD wHigh );
*/


// ������������ �����.
/*
	����������� ���� ��������� � ����������� ��������, ������� 
	����� ���������� ������� ��������� ���������, �.�. 
	����������, ����� ���������� ������ � ���������� 
	��������� ��������� �� ����� ������.
*/

// �������� �������.


int main()
{
    return 0;
}

