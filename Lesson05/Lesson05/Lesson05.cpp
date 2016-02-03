// Lesson05.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

//���������� ����������� ���������
/*
1)	����� ������� � ���������� ����� ���������� ������?
2)	����� ���������� ������� ��������� ���������� �������?
3)	����� ������� ������ ����� ����������?
4)	� ������� ����� ������� ����� ����������, ����� ����������, 
	��������� �����, ����������� � ������ �����?
5)	����� ������� ������ �������, ������������� ���� �������� ������?
6)	����� ������� ����� ����������� ��� ���������������� ��������� 
	�������� ����?
7)	����� ������� ������ �������, ������������� �������� ����?
8)	����� ������� ������������ � �������� ����������? �������� �������.
9)	��� ����� ���� �������� ��������(resource script)?
10)	����� ���������� �������� � ������������ ����� resource.h?
11)	��� ���������� �������� ���������������� ������� �� �������� 
	�������������� �������, ������������ � ����������?
12)	��� ����� ���� ������������  ������ MAKEINTRESOURCE?
13)	������ ��������� ����� �������� ���������� ���������� � 
	������� ���������?
14)	��� ����� �����������(������)? ����� ������� ������� ������ 
	����������� ���� �����?
15)	��� ����� ������? � ������� ������ ����������� ����� ��������� 
	�������� �����?
16)	����� ������� ���������  �������������� ������� �����?
17)	����� ������� ������ ���  ������������� ��������� ����� ������� 
	� ����������� �� ��� ���������������?
18)	����� ������� ����� ����������������� ���������� ������ ������� API, 
	� ����� �������� �������� ������ ��� � ������������� � ���������� 
	������ �������?
*/

// �������� ����������� ����������
// �������� ���������� �� ������ ���������� �������
void ex01()
{
	/*
		���������� �� ������ ���������� ������� ������ ��������� 
		��� ������� ��� �������:
		�	WinMain � ������� �������
		�	DlgProc � ���������� ���������
	*/

	// �������� ���������� �������
	/*
		INT_PTR DialogBox(
			HINSTANCE hInstance,	// ���������� ���������� ����������, 
									// ����������� ������ ����������� ����
			LPCTSTR lpTemplate,		// ��������� �� ������, ���������� 
									// ��� ������� ����������� ����
			HWND hWndParent,		// ���������� ������������� ����
			DLGPROC lpDialogFunc	// ��������� �� ���������� ���������
		);

		������� ����������� �� ��� ���, ���� ���������� ��������� ��
		������� ��������� ���� ��������:
		
		BOOL EndDialog(
			HWND hDlg,		 // ���������� ����������� ����
			INT_PTR nResult  // ��������, ������������ �������� DialogBox
		);
	*/
	// ������� ���������� ��������� �� �������
	/*	
	�	���������� �������� ���� BOOL.
	�	���� ���������� ��������� �� ������������ ���������, 
	    �� ��� ���������� �������� FALSE (����� ������������ �����������
		���������).
	�	���� ���������� ��������� ������������ �����-��  ���������, 
	    �� ��� ���������� �������� TRUE (������ ������ ������������ 
		����������� ���������).
	�	��� �������� ����������� ���������� ���������� � ���������� 
	    ��������� ���������� ��������� WM_CLOSE.
	*/
}

// �������� ���������� �� ������ ������������ �������
void ex02()
{
	//����������� ���������� ���� ��������� ��� ������ �������
	/*
	HWND CreateDialog(
		HINSTANCE hInstance, // ���������� ���������� ����������, 
							 // ����������� ������ ����������� ����
		LPCTSTR lpTemplate,  // ��������� �� ������, ���������� 
							 // ��� ������� ����������� ����
		HWND hWndParent,	 // ���������� ������������� ����
		DLGPROC lpDialogFunc // ��������� �� ���������� ���������
	);

	������� CreateDialog DialogBox ����� �� ���������� ���������� 
	����������� ����, �� ��������� ��� ��������.
	
	���  ����  ����� ����������� ���� ��������� �� ������ ���������� 
	� ��������� ������� ����������� ���� ���������� �������� True 
	��� �������� Visible. 
	
	������ �������� ����������� ������������ ���� �������� ����� 
	������� ShowWindow.
		
	� ���� ������� WinMain ������� ������������� ���� ��������� 
	���������.
	*/
	/*
	��� �������� ����������, ���������� �� ������ ������������ 
	�������, ���������� � ���������� ��������� ��� ��������� 
	��������� WM_CLOSE ������ ������� DestroyWindow, � 
	���������� ���� ��������� ��������� � ������� ������� 
	PostQuitMessage	
	*/
}

// ����� �������� �� ��������� ����������
void ex03()
{
	/*
		Windows ������������ ������� �������� ����������:
			- ������ (Button)
			- ������ (Check Box)
			- ������������� (Radio Button)
			- ������ (List Box)
			- ���� ����� (Edit Control)
			- �������-�������� ������ (Combo Box)
			- ����������� �������� (Static Text)
			- ������ ��������� (Scroll Bar)
			- ����� (Group Box)

		����� �������� ����������, ���������� � ���������� 
		��������� ���������� ������ ����������� 
		(common control library), ����� ��������:
			- ������ ������������ (Toolbar)
			- ���� ��������� (Tooltip)
			- ��������� (Progress Control)
			- ������� (Spin Control)
			- ������ ��������� (Status Bar) � ������.
	*/
	/*
		������ ������� ���������� ����������� � ���� ���� 
		���������������� ������. 
		��������, ��� ������ ��������� � ������ BUTTON. 
		��������� ������ ��������������� ������� ��� 
		��������� ���������� �������� STATIC, LISTBOX, 
		EDIT, COMBOBOX � ������.
	*/
	/*
		��� �������� �������� ���������� ����������� ���� �����
		��������������� �������� CreateWindow.

		��� ���� ������ �� ������ ��������� ������� ���������� 
		��� ����������������� �������� ������

		������:
			CreateWindowEx(0, TEXT("STATIC"), 0,
							WS_CHILD | WS_VISIBLE | WS_BORDER | 
							SS_CENTER |	WS_EX_CLIENTEDGE,	
							LEFT, TOP, WIDTH, HEIGHT, hWnd, 0, hInst, 0);
		
		����� ����: https://msdn.microsoft.com/ru-ru/library/czada357.aspx
		����������� ����� ����: https://msdn.microsoft.com/ru-ru/library/61fe4bte.aspx
		����������� �����: https://msdn.microsoft.com/ru-ru/library/9h0ay857.aspx		
	*/
	/*
	�������� ���������� ����� ���� ������������ (enabled) 
	��� ������������ (disabled). 
	
	��������� ������� ��������� ���������� �������������� ��� 
	������ ������� EnableWindow:

		BOOL EnableWindow(
			HWND hWnd,   // ���������� ����
			BOOL bEnable // ���� ������ �������� ����� TRUE, �� ���� �����
						 // �����������, � ��������� ������ - �����������
	    );
	*/
}

// ����������� ������� ���������� Static Text
void ex04()
{
	/*
	 ������������ ����� �������� �������� ����-���� � ������� � 
	 ���� ����� ������ ������������ � ���� ������.
	*/
	/*
	�������� ������������ �������� ���������� Static Text:
	�	Caption �������� ��������� ������, ������� ����� ������������ ������ ��������������� �������������� �������� Static Text. ��� ���� � ������ ����� �������������� ��������-��� ������� \t (���������) � \n (������� ������).
	�	Border �� ��������� True ��������� ���������� ������ ����� ������ �������� ����������.
	�	Align text ��������� ������ ������������ ������ �� ��-���������. ����� ������������ �������� Left (�� ���������), Center ��� Right.
	�	Center Image ��������� ������ ������������� ������ �� ���������.
	*/
}

// ����������� ������� ���������� Picture Ctrl
void ex05()
{
	/*
	 PictureCtrl ������������ ��� ���������� ����������� �� 
	 ���������� ����.
	 
	 ������ ��� ��������� ����������� ����������  �������  
	 �������� ��� � ������ �������� �������.
	 
	 ����� ����� �������� �� ����� ������� ������� 
	 ���������� PictureCtrl.
	 */
}

//������������ �����
/*
	������� ����������� ���������� ����������, ����������� ���������� ������, 
	�������������� �� ����� �������.
	
	��� ����������� ������� ������� ������������ ����.
*/

// �������� �������
/*
����������� ����������, ��������� �� ������ ����������� ����, 
� ���������� ��������� �����������������:

�	������������ �������� ����� ������� ���� �� ����� ������� �, 
    �� �������� ������, ���� �� ��� �����, � � ������ ���������� 
	������ �� ���������� ����������� ��������������
	(��� ��������, ���� ����� �� ��������� �������� - �� ��� 
	�������� ��������������) �������� �������, ������� �������� 
	���� ���������� ����� (������� � ���� ������� ��������� �������� 
	�� �����).

�	����������� ������ �������� ���������� 10�10, � ��� ������� 
    �������� �������� ���������� ������� �������� ������������ ������ 
	������� ��������������� ��������������.

�	��� ������ ������ ������� ���� ��� ������������ �������� � 
    ��������� ���� ������ ��������� ���������� � ������� (���������� 
	����� ��������, ������ � ������, � ����� ���������� �������� 
	������������ ������������� ����).
	� ������ ���� � ����� ������ ��������� ��������� ���������, 
	�� ������������ �������� �������� � ���������� ���������� �������.

�	��� ������� ������ ����� ������ ���� ��� ������������ �������� 
    �� ������ ��������� � ����� (��� ����� ����� ��������������� 
	�������� DestroyWindow, ������� � ��� ���������������� ������� 
	��������).
	� ������ ���� � ����� ������ ��������� ��������� ���������, 
	�� ������������ �������� �������� � ���������� ���������� �������.

	��� ���������� ���������� ������������� ������������ ���������� STL.
*/


int main(int argc, TCHAR* argv[])
{
	return 0;
}

