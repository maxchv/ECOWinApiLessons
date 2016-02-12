// Lesson09.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <bitset>
#include <iostream>
#include <vector>
#include <string>

// ���������� ����������� ���������
/*

1)	��� ���� ������ ���������� ��������� ���� �����?
2)	������ ��������� ����� ������� ��������� ���� �� �������?
3)	����� ��������� ����� � ���������� ��������� ��� ����� ������ � Edit Control?
4)	����� ����������� �� ���������� ���� �������� ������������� ���� (�������) 
    ��� ����� ������?
5)	����� ��������� ������������ ���������� ���� ����� ��� ������-�����, ��������� � 
    �������� ��������� ������?
6)	����� ��������� ���������� ��������� ���������� ����, ����� �������� ������� ��������� ������?
7)	����� ��������� ���������� ��������� ���������� ����, ����� �������� �������� ������? 
    ����� ������� ����� �������� ���� �����?
8)	��� ���������� ����� ������, ��������� � ��������� ����?
9)	����� ������� ��������� ����������, ������� �� ����� � ������ ��-����?
10)	����� ������� ��������� �������� ����� �������� ����������?
11)	����� ������� ��������� �������������� ����������� ������� ��������� �������� 
    ����������?
*/


// ������� ���������� ������� (List Box)

/*
    ������� ���������� List Box ������������ ����� ������ ���������,
    �� ������� ������������ ����� ������� ���� ��� �����. �������� 
    ������ ����� ���� ������������ ��������, ���������� �������� 
    ��� ����������� ������ � �����������.

    ����� �������:
        https://msdn.microsoft.com/en-us/library/windows/desktop/bb775144(v=vs.85).aspx

    �������� �������: ������ �������� �������� LISTBOX

    CreateWindowEx(WS_EX_CLIENTEDGE, 
                   TEXT("LISTBOX"), 0,
                   WS_CHILD | WS_VISIBLE | LBS_SORT | LBS_NOTIFY, 			
                   LEFT, TOP, WIDTH, HEIGHT, 
                   hDlg,
                   (HMENU)IDC_LIST			// ������������� ������ , 
                   hInstance, 
                   0);

    ����� �������:
        https://msdn.microsoft.com/en-us/library/windows/desktop/bb775149(v=vs.85).aspx

    ����������: � CommCtrl.h ���������� ������� ������� ��� �������
                ������� ��������� ����������
                ��. https://msdn.microsoft.com/en-us/library/windows/desktop/bb775491(v=vs.85).aspx#WC_LISTBOX
*/

// ��������� �������
/*
    �������� ���� ���������:
        https://msdn.microsoft.com/en-us/library/windows/desktop/bb775146(v=vs.85).aspx#Messages
                    

    ��� ���������:	LB_ADDSTRING	
           wParam:	0			
           lParam:  szString		
         ��������:  �������� � ������ ������ szString. ���� �������� Sort � 
                    ������ ���������, �� ������ ����� ��������� � ����� ������. 
                    ���� ��� �������� ��������, �� ����� ���������� ������ 
                    ������������ ���������� ������

    ��� ���������:	LB_FINDSTRING	
           wParam:	iStart		
           lParam:	szString		
         ��������:  ����� ������, ������������ ��������� szString. ����� 
                    ���������� � �������� � �������� iStart + 1. 
                    ���� wParam ����� -1, �� ����� ���������� � ������ ������. 
                    SendMessage ���������� ������ ��������� ������ ��� LB_ERR, 
                    ���� ����� ���������� ���������

    ��� ���������:	LB_GETCURSEL
           wParam:	0		
           lParam:	0		
         ��������:  �������� ������ �������� ���������� �������� ��� LB_ERR, 
                    ���� ������ �������� ��� (������ ��� ������� � ��������� �������)
                

    ��� ���������:	LB_GETSELCOUNT
           wParam:	0		
           lParam:	0		
         ��������:	�������� ���������� ��������� ��������� (��� ������ � 
                    ������������� �������)

    ��� ���������:	LB_GETSELITEMS
           wParam:	nMax		
           lParam:	pBuf		
         ��������:	��������� ����� pBuf �������� �������� ���������� ��������� 
                    ��� ������ � ������������� �������. �������� n��� ������ 
                    ������������ ���������� ����� ���������

    ��� ���������:	LB_INSERTSTRING
           wParam:	iIndex		
           lParam:	szString		
         ��������:	�������� ������ szString ����� ������ � �������� iIndex. 
                    ����������� ��� ������ � ����������� ��������� Sort

    ��� ���������:	LB_SELECTSTRING
           wParam:	iStart		
           lParam:	szString		
         ��������:	���������� ��������� LB_FINDSTRING, �� ������������� 
                    ���������� ��������� ������

    ��� ���������:	LB_SETSEL
           wParam:	wParam		
           lParam:	iIndex		
         ��������:	������� ������� � �������� iIndex (� ������ � ������������� 
                    �������). ���� wParam ����� TRUE, ������� ���������� � 
                    ����������,���� FALSE � ����� ����������. ���� lParam 
                    ����� -1, �� �������� ����������� �� ���� ��������� ������
        
    ��� ���������:	LB_GETTEXT
           wParam:	iIndex		
           lParam:	szString		
         ��������:	����������� ������ � �������� iIndex � ����� szString
       
    ��� ���������:	LB_DELETESTRING
           wParam:	iIndex		
           lParam:	0		
         ��������:	������� ������ � �������� iIndex.
        
    ��� ���������:	LB_GETCOUNT
           wParam:	0		
           lParam:	0		
         ��������:	�������� ���������� ��������� � ������
        
    ��� ���������:	LB_GETTEXTLEN
           wParam:	iIndex		
           lParam:	0		
         ��������:	�������� ����� ������ � �������� iIndex

    ��� ���������:	LB_RESETCONTENT
           wParam:	0		
           lParam:	0		
         ��������:	������� ��� �������� �� ������
                
    ��� ���������:	LB_SETCURSEL
           wParam:	iIndex		
           lParam:	0		
         ��������:	������� ������� � �������� iIndex (� ������ � ��������� 
                    �������)
        
    ������� ��� ������ �� ��������:
        https://msdn.microsoft.com/en-us/library/windows/desktop/ff485966(v=vs.85).aspx
*/

// ����������� ������
/*
    ��� ����������� �� List Box (��������, ��� ������ �������� ������), 
    � ���������� ��������� DlgProc ��������� ��������� WM_COMMAND, � 
    �������  LOWORD (wParam) �������� ������������� ������, HIWORD (wParam) 
    �������� ��� ����������� (��������, LBN_SELCHANGE), � lParam � 
    ���������� ������.

    ������ ���� �����������:
    https://msdn.microsoft.com/en-us/library/windows/desktop/bb775146(v=vs.85).aspx#Notifications
    
    ��������� �� ����� ����������� �� ������:
    
    LBN_SETFOCUS	���� �������� ����� �����
    LBN_KILLFOCUS	���� �������� ����� �����
    LBN_SELCHANGE	������� ����� ��� ������� (�������� Notify ������ 
                    ����� �������� True)
    LBN_DBLCLK		�� ������ ������ ������ ��� ������� ������ ���� 
                    (�������� Notify ������ ����� �������� True)
    LBN_ERRSPACE	�������� ������ ������, ���������� ��� ������
*/

// ������� ���������� ���������������� ������ (Combo Box)
/*
    ��������������� ������ (Combo Box) �������� ����������� ������ 
    � ���������� ���� �����.

    �����:
        https://msdn.microsoft.com/en-us/library/windows/desktop/bb775791(v=vs.85).aspx

    ������ �������� Combo Box ���������� ��������� �������� ���������� 
    List Box. �� ���� � ��������� ��������. � ���������, ����� 
    ���������������� ������ ������� ��������� ����, ������� ��������� 
    ���� �� ��������� ��������:	
        Simple (CBS_SIMPLE), 
        Dropdown (CBS_DROPDOWN), 
        Drop List (CBS_DROPDOWNLIST)

    �������� ���������������� ������: ����� COMBOBOX

    CreateWindowEx(WS_EX_DLGMODALFRAME, 
                   TEXT("COMBOBOX"), 0,
                   WS_CHILD | WS_VISIBLE | CBS_SORT | CBS_DROPDOWNLIST,
                   LEFT, TOP, WIDTH, HEIGHT, 
                   hWnd, 
                   0, 
                   hInstance, 
                   0);
    ��� �����:
        https://msdn.microsoft.com/en-us/library/windows/desktop/bb775796(v=vs.85).aspx


*/

// ��������� ��������������� �������
/*
    ����� ����������� � ��������������� ������� �� ������ ����� �� �����  
    ����������� � ���������� ���������� Edit Box � List Box. 
    ��� ���� �������������� ���������, ������������ �������� ���������� 
    Combo Box, ���������� � �������� ��_, � �������������� �������������� 
    ���������, ���������� �� Combo Box ������ ������������� ����, ����� 
    ������� CBN_.

    ��������� ��������� Edit Control, List Box � Combo Box
    ========================== ===============================
        ��� ��������� ���
    Edit Control ��� List Box	��� ��������� ��� Combo Box
    ========================== ===============================
        EM_GETSEL						CB_GETEDITSEL
    -------------------------- -------------------------------
        EM_SETSEL						CB_SETEDITSEL
    -------------------------- -------------------------------
        LB_ADDSTRING					CB_ADDSTRING
    -------------------------- -------------------------------
        LB_DELETESTRING					CB_DELETESTRING
    -------------------------- -------------------------------
        LB_GETCOUNT						CB_GETCOUNT
    -------------------------- -------------------------------
        LB_GETCURSEL					CB_GETCURSEL
    -------------------------- -------------------------------
        LB_GETTEXT						CB_GETLBTEXT
    -------------------------- -------------------------------
        LB_SETCURSEL					CB_SETCURSEL
    -------------------------- -------------------------------


    ������������� ������ ����� �����������.
    ========================== ===============================
        ��� ����������� ���
    Edit Control ��� List Box		��� ����������� ��� Combo Box
    ========================== ===============================
    EN_SETFOCUS, LBN_SETFOCUS			CBN_SETFOCUS
    -------------------------- -------------------------------
    EN_KILLFOCUS, LBN_KILLFOCUS			CBN_KILLFOCUS
    -------------------------- -------------------------------
    EN_UPDATE							CBN_EDITUPDATE
    -------------------------- -------------------------------
    EN_CHANGE							CBN_EDITCHANGE
    -------------------------- -------------------------------
    EN_ERRSPACE, LBN_ERRSPACE			CBN_ERRSPACE
    -------------------------- -------------------------------
    LBN_SELCHANGE						CBN_SELCHANGE
    -------------------------- -------------------------------

    �������:
    https://msdn.microsoft.com/en-us/library/windows/desktop/bb775792(v=vs.85).aspx#Macros
*/


std::string drive_type(LPCTSTR type)
{
    std::string str_type;
    switch (GetDriveType(type))
    {
    case DRIVE_NO_ROOT_DIR:
        str_type = "NO ROOT DIR";
        break;
    case DRIVE_REMOVABLE:
        str_type = "REMOVABLE";
        break;
    case DRIVE_FIXED:
        str_type = "FIXEDR";
        break;
    case DRIVE_REMOTE:
        str_type = "REMOTE";
        break;
    case DRIVE_CDROM:
        str_type = "CDROM";
        break;
    case DRIVE_RAMDISK:
        str_type = "RAMDISK";
        break;
    case DRIVE_UNKNOWN:
    default:
        str_type = "UNKNOWN";
    }
    return str_type;
}

void ex()
{
    /*
    ������� http://www.softzenware.com/visual/visual24.html
            https://shinigamiblog.wordpress.com/2011/02/27/getlogicaldrivestrings-%D1%87%D1%82%D0%BE-%D1%8D%D1%82%D0%BE-%D0%B8-%D1%81%D0%BE%D0%B1%D1%81%D0%BD%D0%B0-%D0%B7%D0%B0%D1%87%D0%B5%D0%BC/
    */
    /*
        ������� GetLogicalDrives ���������� ������� ����� ���������� ������,
        ������� �������� � ������ ������. ��� ���� ������ ��� ����� 
        ������������ ����� ���������� ����. ���� ��� ����������, �� 
        ���������� ���� ��������, � ��������� ������ ��� ����� �������. 
        ��� 0 ������������� ����� A, ��� 1 � ����� B, ��� 2 � ����� � � �.�

        https://msdn.microsoft.com/en-us/library/windows/desktop/aa364972(v=vs.85).aspx
    */
    DWORD drivers = GetLogicalDrives();
    std::vector<std::string> strdrivers;
    std::bitset<26> drivers_map = drivers;
    std::cout << drivers_map << std::endl;
    for (int i = 0; i < 26; i++) {
        if ((drivers >> i) & 0x00000001)
        {
            char ch[2] = { 'A' + i, '\0' };
            strdrivers.push_back(std::string(ch) + std::string(":\\"));			
        }
    }

    for (auto drive : strdrivers)
    {

        /*
        ������� GetDriveType ���������� ��� ���������� �� ��������� �����
        ��������� ���� (��������, �C:\\�).

        https://msdn.microsoft.com/en-us/library/windows/desktop/aa364939(v=vs.85).aspx
        */
        std::cout << drive << " " << drive_type(LPCTSTR(drive.c_str())) << std::endl;
    }

    /*
        ������� GetLogicalDriveStrings ��������� ����� ��������, ������� 
        ���������� �������������� ���������� ����� � �������.

        https://msdn.microsoft.com/en-us/library/windows/desktop/aa364975(v=vs.85).aspx
    */
    DWORD dwSize = GetLogicalDriveStrings(0, NULL);	//���������� ����� ������ c �������, ������� ������� �� � �����	
    TCHAR* szDrives = new TCHAR[dwSize];
    GetLogicalDriveStrings(dwSize, szDrives);
    std::wcout << szDrives << std::endl;
}

int main()
{
    ///ex();
    return 0;
}

