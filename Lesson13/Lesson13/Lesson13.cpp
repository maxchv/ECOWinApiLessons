// Lesson13.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// ���������� ����������� ���������

/*
1)	��� ���� ������������� ������ ���������?
2)	����� ������� API ��������� ������� ������ ���������?
3)	��� ���������� ����������� ����� ������ ������ ��������� �� 
    �������� ������?
4)	����� ��������� ���������� ��������� ������ ��������� ��� 
    ��������� ��������� ������ ������?
5)	� ������� ������ ��������� ����� ��������� ������ ��������� 
    �� ��������� ������ ?
6)	����� ������� ����� ���������� ����� � ������ ���������?
7)	� ������� ������ ��������� ����� �������� ���������� ���������� 
    ������ ������ ���������?
8)	��� ���������� ����� ����������� ��������� ��� �������� ������?
9)	��� ���������� ������ �� �������� ������?
10)	� ������� ������ ��������� ����� ���������� ���� ���� 
    ������ ���������?
*/

// ����
/*
���� ������������ ����� ������ ������, ����������� ��������� 
����� ��������, ������������� �����������. 

��������� ��������� ���� ����:
�	������� ����;
�	��������� ����;
�	����������� ����.

https://msdn.microsoft.com/en-us/library/windows/desktop/ms647553(v=vs.85).aspx
*/

// ���� � ��������� ������� ����
/*
��������� ��� ���� ������� ����:

�	����� ���� ��������;
�	����� ���� ���������

����� ���� �������� � ��� �������� ����� �� ������������� ������ ����. 
��� ������ ������ ������ ���� ������ ����������� ��������� ��������. 
��� ���� � ����������� ���� ������ ���� �������� ����������� 
���������� ������������� �������������.

����� ���� ��������� � ��� ��������� ����������� ���� ����� ������� ������.

��������� � ��� ������� ����, �������  ������������ ����� 
�������������� �������������� �����.

������ ���� ����� ���� ������������ (enabled), ������������ (disabled) � 
������������ (grayed). 

�� ��������� ����� ���� �������� �����������. 
����� ���������� ����� �����, ������� �������� ������� ��������� ���������
WM_COMMAND ��� ����������  ��������������� �������, � ����������� �� 
���� ������.

����������� � ����������� ������ � ����� ������ ��������� ���������. 
�� ����� ��������, �� ������ �������, �.�. ��� ������ ����� ��� ��� 
������� ������� <Enter> ������ �� ����������. 

����������� ����������� � ����������� ������ ������ ������� �����. 
����������� ����� �������� ����� ��� ��, ��� �����������, 
� ����������� ����� ���� ������������ ����� ������.

������������� ������ ������������ �� ������ ����, ������������� 
������� � ������ ������ ������������ ��� ���� ����������� � ����� 
������ ������������ ������ ����������.

������ ����� ���� ����� �������������� � ���� ������ (check box). 
������ ����� ���� ���������� ��� �������. ��� ���� ������� �� ������ 
��������� � ������ ���������� ��� ������ ������ ������ ����.

������ ���� ����� �������������� ����� � ���� �������������� (radio button).
�������������, ��� � ������, ������ ������������ � ������. �  ������� 
�� �������, ������������� ����������� ������ � ������������������ �������, 
������� � ������ ����� ������� ������ ���� �������������.
*/

// �������� ����
/*
� ������� ������� Microsoft Visual Studio

��������� ���� � ���������� ������� ��������� �����:
    �	����������� ������� ���� � ����� �������� ��������;
    �	�������� ���� ��� �������� �������� ����;
    �	��������� ������� ����.
*/

// �����������  ������  ������������� ����  �  ��������  ����  ����������
/*
�������� ���� �� �������:

HMENU LoadMenu(          
    HINSTANCE hInstance, // ���������� ����������
    LPCTSTR lpMenuName // ��������� �� ������, ���������� ��� ���� � ��������
);

https://msdn.microsoft.com/en-us/library/windows/desktop/ms647990(v=vs.85).aspx

����� �������� ����, ��� ���������� ���������� � ������� ������� API SetMenu:

BOOL SetMenu(          
    HWND hWnd,	// ���������� ����, � �������� �������������� ����
    HMENU hMenu // ���������� ����
);

https://msdn.microsoft.com/en-us/library/windows/desktop/ms647995(v=vs.85).aspx
*/

// ��������� ����������� �������� ����/�������
/*
��� ��������� ����������� �������� ���� ������ ������� API GetMenu.

HMENU GetMenu(
    HWND hWnd	// ���������� �������� ���� ����������
);

https://msdn.microsoft.com/en-us/library/windows/desktop/ms647640(v=vs.85).aspx

���  ���������  �����������  �������  ������  ������� API GetSubMenu.

HMENU GetSubMenu ( 
    HMENU hMenu,	// ���������� ������������� ���� 
    int nPos		// ������� ������-������� � ������������ ���� 
);

https://msdn.microsoft.com/en-us/library/windows/desktop/ms647984(v=vs.85).aspx
*/

// ��������� ��������� ����
/*
������������ �������  Windows �������� ��������� WM_COMMAND ��� 
������ ������ ������ ����, ������������� �������.  

��� ���� LOWORD(wParam) �������� ������������� ������ ����, 
� HIWORD(wParam) � lParam �������� ������� ��������. 

��� ������ ������� ���������� ���� ������ ���������� ��������� ������������ 
��������� WM_SYSCOMMAND. 

https://msdn.microsoft.com/en-us/library/windows/desktop/ms646360(v=vs.85).aspx

������ � ��������� ����� ������������� ��������� ��������� WM_INITMENU � 
WM_INITMENUPOPUP. ��� ������������ ��������������� ����� ������������ 
�������� ���� ��� ����������� ����. 

��� ��������� ��������� ���������� �������� ���� ����� ���, ��� ��� ����� 
���������� �� ������. 

��� ��������� �� ���� ������� ���������� ����� ��������� WM_MENUSELECT.

https://msdn.microsoft.com/en-us/library/windows/desktop/ms646352(v=vs.85).aspx

��� ����� ������������ �� ��������� � WM_COMMAND, ��� ��� ������������ 
���� �����, ����� ������� ����������� ��� ����������� ����� ����. 

��� ��������� ����� �������������� ��� ������������ ����������� ������� ����, 
������� ������������ � ������ ��������� ����������.
*/

// ��������� ��������� ������� ����
/*
��� ��������� ������� ������� ���� ����������� ������� API EnableMenuItem.

BOOL EnableMenuItem(
    HMENU hMenu,		// ���������� ����
    UINT uIDEnableItem, // ������������� ��� ������� ������ ����
    UINT uEnable		// ������������� ������� ��������� �
                        // ����������� ��������
);

https://msdn.microsoft.com/en-us/library/windows/desktop/ms647636(v=vs.85).aspx

������ �������� uEnable �������� ��� ��������� �������� ����������� ���� ������. 

������ ���� ����� ��������� ���� �� ��������� ��������: 
    �	MF_BYCOMMAND � � ���� ������ ������ �������� ������ ��������� 
        ������������� ������ ����;
    �	MF_BYPOSITION � � ���� ������ ������ �������� ������ 
        ��������� ������������� ������� ������ ���� � �������� �� ����. 

������ ���� ����� ��������� ���� �� ��������� ��������: 
    �	MF_ENABLED � ����� ���� ��������;
    �	MF_DISABLED � ����� ���� ��������;
    �	MF_GRAYED � ����� ���� ����������.

���� � ���������� ���������� ������� ���������� ������ ������ �������� ����, 
�� ������� ����������� ������� ������� API DrawMenuBar ��� ���������� 
����������� ������������ ������ ����.

BOOL DrawMenuBar(
          HWND hWnd // ���������� �������� ���� ����������
);

https://msdn.microsoft.com/en-us/library/windows/desktop/ms647633(v=vs.85).aspx
*/

/*
��� ��������� ��� ������ ������� �� ������ ����:

DWORD CheckMenuItem(
    HMENU hMenu,		// ���������� ����
    UINT uIDCheckItem,	// ������������� ��� ������� ������ ����
    UINT uCheck			// ������������� ������� ��������� � ����������� ��������
);

https://msdn.microsoft.com/en-us/library/windows/desktop/ms647619(v=vs.85).aspx

������� ��������� ������� uIDCheckltem ���������� ���� ������������� ������ ����, 
���� ������� ������ ����. ����� �������� ������������� �������� � ������� ���������. 

������ �������� uCheck �������� ��� ��������� �������� ����������� ���� ������. 
������ ���� ����� ��������� ���� �� ��������� ��������: 
    �	MF_BYCOMMAND � � ���� ������ ������ �������� ������ ��������� ������������� 
        ������ ����;
    �	MF_BYPOSITION � � ���� ������ ������ �������� uIDCheckltem ������ ��������� 
        ������������� ������� ������ ���� � �������� �� ����. 

������ ���� ����� ��������� ���� �� ��������� ��������: 
    �	MF_CHECKED - ��������� ������� ����� �� ����� ������ ����;
    �	MF_UNCHECKED - ����� ������� ����� �� ����� ������ ����.

� �������� CheckMenuItem � EnableMenuItem ������� ������������� ������������� ����� 
MF_BYCOMMAND

��� ���������� ������� �������-�������������� (������ �������
�� ��������� ������ � ������� �� ���� ��������� ������� � ���������
������) ������������ ������� CheckMenuRadioItem(), �� ��������:

BOOL CheckMenuRadioItem(
    HMENU hMenu,	//���������� ����
    UINT idFirst,	//������������� ��� ������� �������
                    //������ � ������
    UINT idLast,	//������������� ��� ������� //���������� ������ � ������
                    //���������� ������ � ������
    UINT uFlags		//������������� ���������� idFirst,
                    //idLast � idCheck
);

������� ������ ���� ��� ������ ��������������, �������
���������, ��� �� �������������� � ����� resource.h
����� �������� ��������� � ����������� � ������������ 
� ��������� ���� ������� �� ������ ����.

������ ������� ����:

https://msdn.microsoft.com/en-us/library/windows/desktop/ff468865(v=vs.85).aspx
*/

// ������ ������� �����. 
/* 
������� ����� ������������ ����� ������ �����, ��������� � �����������  
�������������� ����������������. 

��� �������� ������ �� ������� ������� ����� ������������� ������� API LoadString.

int LoadString( 
    HINSTANCE hInstance,	// ���������� ����������, ����������� ������� �����
    UINT uID,				// ������������� ������, ������� ������ ���� ���������
    LPTSTR lpBuffer,		// ��������� �� �����, � ������� ����� �������� ������
    int nBufferMax			// ������ ������
);
https://msdn.microsoft.com/ru-ru/library/windows/desktop/ms647486(v=vs.85).aspx
*/

int main()
{
    return 0;
}

