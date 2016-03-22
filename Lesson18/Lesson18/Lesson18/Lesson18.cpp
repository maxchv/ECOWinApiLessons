// Lesson18.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// ������ ������������ (Toolbar Control)
/*
    ������ ������������ � ������ ������������� (��� �����������) ������������� ����������� ������, ������ 
    ������������ � ������. �������� �� ������ �������������� ����������� �����, � ������������ � 
    ����������� ������ ����������� ������ �������� � ����� ��������� �����������, �������� � ������� ����������. 
    ���� �������� ������, ��� ������ ��������� ���������, ������� ���� � ������� ��������. 
    ��� ���������� ��������� ������ ������ ����������� ���������� ���������� ����������������� ����������, 
    ���������� �������� ���������� ��� ��������� �������� ���� ������

    https://msdn.microsoft.com/en-us/library/windows/desktop/bb760443(v=vs.85).aspx
*/

// ��� 1. �������� � ����������� ������ ���� Toolbar.
/*
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

INITCOMMONCONTROLSEX iccx;
iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
iccx.dwICC = ICC_BAR_CLASSES;
if (!InitCommonControlsEx(&iccx))
{
    return FALSE;
}
*/

// ��� 2. �������� ������ ������������ (CreateWindow)
/*

��� �������� ������������ ����� ���� TOOLBARCLASSNAME

����� ������ ��������� �����:

TBSTYLE_FLAT		����� ������ ������������ ��� ����������.
                    ��� ��������������� ������� � ������������, 
                    ����� ������ ����
                    ���������� ����� ������������ ������ ������������.
TBSTYLE_TOOLTIP		����� �������� �������� ������ � ���� �������� ����������
                    Tool Tip
TBSTYLE_LIST		����� ������ ���������� ������ �� ��������.
TBSTYLE_TRANSPARENT ������� ���������� ������ ������������ 
                    (�� �� ���������� ������).
                    ����� ������ ������������ ��� ����������.
TBSTYLE_ALTDRAG		���� �� ������ ����� TBSTYLE_ALTDRAG, �� ������������ ����� 
                    ����������� ������ �� ����������� Toolbar ����� �������� ���� 
                    ��� ������� ������� <Shift>. ���� �� ���� ����� ������, ��� 
                    ����������� ������ ������������ ������� <Alt>. � ����� ������ 
                    ������ ����� ����������� ������ �����, ����� ������ ����� CCS_ADJUSTABLE
TBSTYLE_WRAPABLE	���� Toolbar ����� �������� �� ���������� �����. ����� ������ 
                    ��������� � ��� ������, ���� ��� ������ �� ���������� � ����� ������

https://msdn.microsoft.com/en-us/library/windows/desktop/bb760439(v=vs.85).aspx#TBSTYLE_LIST

�������������� �����:

CCS_ADJUSTABLE		���� ������ ���� �����, ������������ ����� �������� 
                    ������������ �������� ����������
CCS_BOTTOM			������� ���������� ������ ���� ���������� � ������ ����� ���������� 
                    ������� ����
CCS_TOP				������� ���������� ������ ���� ���������� � ������� ����� ���������� 
                    ������� ����

https://msdn.microsoft.com/en-us/library/windows/desktop/bb775498(v=vs.85).aspx#CCS_ADJUSTABLE

������:
    HWND hToolbar = CreateWindow(TOOLBARCLASSNAME, 0,
        TBSTYLE_FLAT | CCS_ADJUSTABLE | CCS_NODIVIDER | WS_CHILD | WS_VISIBLE,
        0, 0, 0, 0,
        hWnd, (HMENU)IDC_TOOLBAR, GetModuleHandle(0), 0);
*/

// ��� 3. ��������� � �������� ������ � ������ ������������.
/*
3.1 ����� �������� ���������� ��������� ��������� TB_BUTTONSTRUCTSIZE � ������ ������������. 
���� ���������� ���������� ������� CreateWindow ��� �������� ������ ������������, 
���������� ��������� ��� ��������� ����� ����������� TB_ADDBITMAP ��� TB_ADDBUTTONS. 

�������� ��������� TB_BUTTONSTRUCTSIZE, �������� ������ ��������� TBBUTTON.

������:
    SendMessage(hToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
    
3.2 �������� ����������� (TBADDBITMAP, TB_ADDBITMAP)

����� ��������� ��������� TBADDBITMAP:
    typedef struct
    {
        HINSTANCE hInst;				// ������������� ����������
        UINT nID;						// nID - ������������� ����������� ������
    } TBADDBITMAP, *LPTBADDBITMAP;

����� ������������ ���������������� ��������� �����������, ����� hInst ������ ����
����� HINST_COMMCTRL, � �������� nID ���������� �� ������

IDB_STD_LARGE_COLOR				����������� ������� ������� �����������
IDB_STD_SMALL_COLOR				����������� ��������� ������� �����������

������ ����������� �������� nID: https://msdn.microsoft.com/en-us/library/windows/desktop/bb760475(v=vs.85).aspx
 
������:
    TBADDBITMAP tbAddBmp = {0};
    tbAddBmp.hInst = HINST_COMMCTRL;
    tbAddBmp.nID = IDB_STD_SMALL_COLOR;

����� ����������� ��������� ���� TBADDBITMAP �������� � 
�������� ���������� ��������� TB_ADDBITMAP.

������:
    SendMessage(hToolbar, TB_ADDBITMAP, 0, (WPARAM)&tbAddBmp);

3.3 ���������� ������ (TBBUTTON, TB_ADDBUTTONS)

����� ���������� ������� ������ �������� TBBUTTON , ������� ��������� 
������ � ����������� ����� �������� ������. 
� ���� ������� ���������� ��������������� �� ����� ��������� ��� ������ 
������ � ��� ������� ����������� ����� ������.

� ����� commctrl.h ��������� ����� ����������� ��������� TBBUTTON:

typedef struct _TBBUTTON
{
    int   iBitmap;			// ������ ����������� ������
    int   idCommand;		// �������������, ������� ����� ������������ ������������� ���� � 
                            // ���������� WM_COMMAND
                            // ���� ������� ������� �������� TBBUTTON ��������� ����������� 
                            // ������ ������, � ���� idCommand ����� �������� ������� ��������.
    BYTE  fsState;			// ���� ��������� ��������� ������
    BYTE  fsStyle;			// ����� ������
    DWORD dwData;			// �������������� ������, ������� ����� �������� � �������� 
                            // ������ � �������������� ��� �������������
    int   iString;			// ������ ��������� ����� ������
} TBBUTTON, NEAR * PTBBUTTON, FAR * LPTBBUTTON;
typedef const TBBUTTON FAR * LPCTBBUTTON;

��� �������� ���������� � ���������� ������ � Windows ������� ��� ������ ������� ��� 
������������� ������� �������. ������ ����� �������� ����������� 15 ������, 
��������������� �������� ���� File � Edit, ������ �� � ������������ ����������� �����������. 

�������������� ������ ������ �������� �� ����������:
    STD_CUT,		STD_COPY,		STD_PASTE,		STD_UNDO,		STD_REDOW, 
    STD_DELETE,		STD_FILENEW,	STD_PRINTPRE,	STD_PROPERTIES, STD_HELP, STD_FIND, 
    STD_FILEOPEN,	STD_FILESAVE,	STD_REPLACE,	STD_PRINT.	

������ ��������������
    https://msdn.microsoft.com/en-us/library/windows/desktop/bb760433(v=vs.85).aspx

���� ��������� ��������� ������ fsState:
TBSTATE_ENABLED			������ ��������� � ���������������� ���������. 
                        ���� ���� ���� �� ����������, ������ ������������� � ������������ 
                        ����� ������
TBSTATE_CHECKED			������ ������������ � ������� ���������. ���� ���� ������������ 
                        ��� ������ � ���������
TBSTATE_HIDDEN			������� ������, �� ������������
TBSTATE_INDETERMINATE	������ ������������ ����� ������
TBSTATE_PRESSED			������ ������������ � ������� ���������
TBSTATE_WRAP			������, ������������� ����� ���, ��� ����� ���� TBSTATE_WRAP, 
                        ������������ �� ����� ������. ����� �������, �� ������ ������� 
                        ������������� Toolbar . ���� ���� ����� ��������� ������ �����, 
                        ����� ���������� ���� TBSTATE_ENABLED

������ ���������: https://msdn.microsoft.com/en-us/library/windows/desktop/bb760437(v=vs.85).aspx

����� ������ fsStyle:

TBSTYLE_BUTTON		����������� ������
TBSTYLE_CHECK		������ � ���������. ��� ������ "��������", ����� ������������ �������� �� ���. ��� ���� ����� ������� ������ � �������� ���������, ���������� ������ �� ��� ��� ���
TBSTYLE_CHECKGROUP	������ � ���������, ������� �������� ������� �� ��� ���, ���� ������ ������ ������ �� ���� �� ������
TBSTYLE_GROUP		����������� ������, ������� �������� ������� �� ��� ���, ���� ������ ������ ������ �� ���� �� ������
TBSTYLE_SEP			����������� ����� �������� ������

������ �����: https://msdn.microsoft.com/en-us/library/windows/desktop/bb760439(v=vs.85).aspx

������ ��������� ������ �� 7 ������:

    const int numButtons = 7;
    TBBUTTON tbButtons[numButtons] =
    {
        { STD_FILENEW, NULL, TBSTATE_ENABLED,
            BTNS_AUTOSIZE, 0, 0, (INT_PTR)TEXT("New") },
        { STD_FILEOPEN, NULL, TBSTATE_ENABLED,
            BTNS_AUTOSIZE, 0, 0, (INT_PTR)TEXT("Open") },
        { STD_FILESAVE, NULL, 0,
            BTNS_AUTOSIZE, 0, 0, (INT_PTR)TEXT("Save") },
        { 0, NULL, 0, TBSTYLE_SEP, 0, 0, (INT_PTR)TEXT("") }, // �����������
        { STD_COPY, NULL, TBSTATE_ENABLED,
            BTNS_AUTOSIZE, 0, 0, (INT_PTR)TEXT("Copy") },
        { STD_CUT, NULL, TBSTATE_ENABLED,
            BTNS_AUTOSIZE, 0, 0, (INT_PTR)TEXT("Cut") },
        { STD_PASTE, NULL, TBSTATE_ENABLED,
            BTNS_AUTOSIZE, 0, 0, (INT_PTR)TEXT("Paste") }
    };

��������� ������ � ������ ������������:
    
    SendMessage(hToolbar, TB_ADDBUTTONS, numButtons, (LPARAM)tbButtons);
*/

// ��� 4. �������� ��������� ������������� ���������� � ���������� 
//        ������ ������������. (TB_AUTOSIZE)
/*

������:
    SendMessage(hToolbar, TB_AUTOSIZE, 0, 0);
*/

// ��� 5. ���������� ��������� �� ������ ������������
/*
Toolbar �������� � ������������ ���� ��������� WM_COMMAND � WM_NOTIFY.

�������� lParam ��������� WM_NOTIFY �������� ��������� �� ��������� 
TBNOTIFY (���������� � ����� ������ ��������� NMHDR ):
    typedef struct
    {
        NMHDR    hdr;
        int      iItem;
        TBBUTTON tbButton;
        int      cchText;
        LPTSTR   pszText;
    } TBNOTIFY, FAR * LPTBNOTIFY;

� ���� ��������� ���� iItem �������� ����� ������, �� ������� ������ ��������� 
(��������� ������ ���������� � ����).
��������� tbButton ���� TBBUTTON �������� �������� ������.

� ���� cchText ��������� ����� ��������� ������, ��������������� ������. 
����� ���� ������ ���������� ����� �������� pszText.

*/
int _tmain(int argc, _TCHAR* argv[])
{
    return 0;
}

