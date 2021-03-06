// Lesson12.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

// ���������� ����������� ���������
/*
1)	��� ���� ����������� ������� ���������� Slider Control?
2)	����� ������� ����� ���������� �������� �������� (������ � ������� �������)?
3)	� ������� ������ ��������� ����� �������� ������� ������� ��������?
4)	� ������� ������ ��������� ����� ���������� ����� ������� ��������?
5)	����� ���������� �������� ���������� ������������ ���� (������) 
    � ��������� ������������?
6)	��� ���������� ������� Slider Control?
7)	����� ��� �������� ���������� �������� ���� � ����������?
8)	����� ������� ����� ���������� ����������� � ������������ ������� ��������?
9)	� ������� ������ ��������� ����� �������� ������� ������� ��������?
10)	� ������� ������ ��������� ����� ���������� ����� ������� ��������?
11)	��� ���������� ���������� ��� ��������?
12)	� ������� ������ ��������� ����� ���������� �������, �� ��������  ����� 
    �������������� ���������� ��������?
13)	����� ��������� Spin Control �������� ������  ������������� ���� ��� 
    ������� ����� �� �������? ����� �������������� ���������� �������� � ���� ����������?
14)	����� ������� ����� ���������� ������� Spin Control?
*/

// ����� ������� ���������� ������� ���������� (Status Bar)
/*
    ������ ��������� (Status Bar) � ��� ����, ������ ��������������� � ������ 
    ����� �������� ���� ����������, ������� ������������� ��� ������ ���������� 
    � ������� ��������� ���������, � ����������� ��������� � �������. 

    https://msdn.microsoft.com/en-us/library/windows/desktop/bb760728(v=vs.85).aspx
*/

// �������� ������ ���������
/*
� ������� ������� CreateWindow(Ex). 
���  �����������������  ��������  ������ �  STATUSCLASSNAME.

HWND hStatusBar = CreateWindowEx( 0, STATUSCLASSNAME, 0, 
    WS_CHILD | WS_VISIBLE | SBT_TOOLTIPS | CCS_BOTTOM | SBARS_SIZEGRIP,
    0, 0, 0, 0, hDialog, HMENU(WM_USER), GetModuleHandle(NULL), 0);
*/
/*
����� ��������������� �������� API CreateStatusWindow:

HWND CreateStatusWindow(          
    LONG style,			// ����� ��� ������ ���������
    LPCTSTR lpszText,	// ��������� �� ������, ���������� ����� ��� ������ 	
                        // ������ ������ ���������
    HWND hwndParent,	// ���������� ������������� ����
    UINT wID			// ������������� ������ ���������
);
*/

// �����
/*
����� ��� ����� ��������� ����������:
    https://msdn.microsoft.com/en-us/library/windows/desktop/bb775498(v=vs.85).aspx

����� ��� ����� ���������:
    https://msdn.microsoft.com/en-us/library/windows/desktop/bb760730(v=vs.85).aspx

    ��������� �����:

    CCS_BOTTOM		������� ���������� ������������� ����� ���������� ������� 
                    ������������� ���� � ����� ������, ������ ������ ������������� ����.  
                
    SBARS_SIZEGRIP	������ �������  ������������� ������� � ������ ���� ������ ���������. 
                    ���� ������������ �������  ������� �������, �� ������� ����� ���������� 
                    ��� ��������� ������� ����  ����������.

    SBARS_TOOLTIPS	�������� �������� ����� ����������� ��������� ��� ������ ���������. 
                    ��������� ���������� � ����� �� ���� �������: 
                        �	� ������ ������������ ������ ������;
                        �	����� ��������� �� ���������� � ������.
*/


/*
������ ��������� ����� �������� � ����� �� ���� �������: � ����������� ������ ���� � ������� ������.

��� ������ � ����������� ������ ������ ��������� ����������� �� ��������� ������, 
� ������ �� ������� ��������� ��������� ������ ������ ��� ������. 

��� ������ � ������� ������ ������ ��������� ����������� ��� ������ ������� � ���������� 
������ ���� ������. 
*/

// ��������� ������ ���������
/*
��� ���������
    https://msdn.microsoft.com/en-us/library/windows/desktop/ff486035(v=vs.85).aspx
*/

// ������������ �������
/*
������������ ����� �������� �������������� �������� ��������� SB_SIMPLE ������ ���������. 
��� ���� ���� � wParam ����������� �������� TRUE, �� ��������������� ������� �����, 
� ��������� ������ ��������������� ����������� �����.
*/

// ���������� ������
/*
���� ������ ��������� ������������ � ����������� ������, �� � ���������� ��������� 
�� ��������� ������ ��� ������ ��������� SB_SETPARTS. 

��� �������� ����� ��������� � wParam ����������� ���������� ������ ������ ���������, 
� � lParam ����������� ����� �������������� �������, ������ ������� �������� 
���������� ������� (� ���������� �����������) ������ ������� ��������������� ������. 

���� ������� ������� ����� -1, �� �������� ��������������� ������ ��������� ������ 
������� ������ ���������.
*/

// ����������� ������
/*
��� ����������� ������  � ������ ���������, �� ���������� ����-����� SB_SETTEXT. 
� ���� ���������� � wParam ��������� ����� ������ � ������ ��������� 
(������ ������ � ����)
� ����������� ����� ������, � � lParam � ��������� �� ������, ���������� �����.

����������� ����� ������ ����� ����� ���� �� ��������� ��������:
===========================  ===================================================	
        �����								��������
===========================  ===================================================
� (�������� �� ���������)		������ �������� � ���������� ������
SBT_NOBORDERS					������ �������� ��� �����
SBT_POPOUT						������ �������� � �������� ������
SBT_OWNERDRAW					�� ���������� ������ �������� ������������ ����
===========================  ===================================================
*/

// ����������� �������� ����������
/*
������ � ������ ������ ������ ��������� ��������� ��������� ��������� ���������. 
������ ����� ���������� � ������ ������� ����������, �������� ��������� ��������. 
��� ����� ���������� ���������� ����� ���������� ���������� ���� ������, ������� 
����� ���� �������� ���  ������ �������� ��������� SB_GETRECT. 

��� ������� ����� ��������� � wParam ����������� ����� ������ � ������ ���������, 
� � lParam � ����� ��������� ���� RECT,  ����������� ���������� ������.

��������� �������� ���� ������������� ���������� ���������� � ������ ���������:

RECT r;
SendMessage(hStatus, SB_GETRECT, 1, (LPARAM)&r); 

hProgressBar = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_CHILD | WS_VISIBLE,
                                r.left + 3, r.top + 3, r.right - r.left, r.bottom - r.top, 
                                hStatusBar, NULL, GetModuleHandle(NULL), NULL);

*/

// ������ ���������
/*
===============  ============  ===============  ===========================================
��� ���������		wParam		lParam				��������
===============  ============  ===============  ===========================================
SB_SETTIPTEXT		iPart		(LPCTSTR)			������������� ����� ����������� 
                                lpszTooltip			��������� ��� �������� ������
---------------  ------------  ---------------  -------------------------------------------
SB_SETICON			iPart		(HICON)				������������� ������  �� �������� ������
                                hIcon				
---------------  ------------  ---------------  -------------------------------------------
SB_SETBKCOLOR		0			(COLORREF)			������������� ���� ���� ��� ������ 
                                clrBk				���������
---------------  ------------  ---------------  -------------------------------------------													
SB_GETTEXT			iPart		(LPSTR)				�������� ����� �� ��������� ������
                                szText	
===============  ============  ===============  ===========================================
*/

int main(int argc, char* argv[])
{
    return 0;
}

