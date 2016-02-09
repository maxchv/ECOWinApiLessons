// Lesson08.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//���������� ����������� ���������

/*
1)	��� ���� ������ ���������� ��������� �������� ����������, 
    ����� ��� Button, Check Box, Radio Button ?
2)	������ ��������� ����� ������� ������ �� ������� ?
3)	����� ��������� �������� � ���������� ��������� ��� ����������� �� 
    ������� ���������� ������� (��������, ��� ������� �� ������) ?
4)	����� �������������� ���������� �������� � ���������� WM_COMMAND ?
5)	����� ����������� �������� ������� ��� ������� �� ������ ?
6)	����� ������� ��������� ��������� ����� ����� �� ������� ���������� ?
7)	����� ������� ��������� �������� ���������� ���� (�������� ����������), 
    ����������� ������� ����� ?
8)	��� ����������� �������� ����� ���������� ����������� �� ������? 
    ����� ����� � ���� ������ ���������� ������ ������?
9)	����� ���������� ������� ����������� ������������� ��������� �������� 
    ���������� Check Box ?
10)	����� ������� ����� �������� ��������� ������ ?
11)	����� �������� �������� ���������� Radio Button ��������� ���������� � 
    ������ ��������� �������������� ?
12)	����� ���������� ������� ����������� ������������� ��������� ������������� ?
13)	����� ������� ����� �������� ��������� ������������� ?
*/

//������� ���������� ���������� ���� ����� (Edit Control)
/*
�� �������� ����������� ��������� ��������� ���� ����� � ����� ������� �������: 
�� ���������� ������������� ���� ����� �� �������������� �������� ���������� � 
�������������� ��������� �����, ��� � ��������� Microsoft Notepad. 

https://msdn.microsoft.com/en-us/library/windows/desktop/bb775456(v=vs.85).aspx

������� ��������� ���� ����� �� ����� ������� ����� ����� ���������:
�	� ������� �������  ��������������� ����� ����������     
    Microsoft Visual Studio;
�	����������� ������ ������� CreateWindow

����� Edit Controls
	
	ES_AUTOHSCROLL
	ES_AUTOVSCROLL
	ES_LEFT
	ES_CENTER
	ES_LOWERCASE
	ES_MULTILINE
	ES_NUMBER
	ES_PASSWORD


https://msdn.microsoft.com/en-us/library/windows/desktop/bb775464(v=vs.85).aspx
*/

// ��������� ��������� ����� �����

/* 
  ��� ���������� ��������� �������� �� �������������� ������ ���������� 
  ����� ���������� ��������� ��������� �������� ������� - ��� Edit Control

  ==============+============+===========+========================================================================
  ��� ���������	|	wParam	 |	lParam   |	�������� 
  ==============+============+===========+========================================================================
  EM_SETSEL		|	iStart	 |	iEnd	 |	�������� �����, ������� � ������� iStart � ���������� �������� iEnd 
  --------------+------------+-----------+------------------------------------------------------------------------
  EM_GETSEL		|	&iStart	 | 	&iEnd	 |	�������� ��������� � �������� ����-����� �������� ��������� 
  --------------+------------+-----------+------------------------------------------------------------------------
  EM_CANUNDO	|	0		 |	0		 |	���������� ����������� ������ ��-�������� ��������
  --------------+------------+-----------+------------------------------------------------------------------------
 EM_GETLINECOUNT|	0		 |	0		 |	�������� ����� ����� ��� ����������-���� ���� ��������������
  --------------+------------+-----------+------------------------------------------------------------------------
  WM_CLEAR		|	0		 |	0		 |	������� ���������� ����� 
  --------------+------------+-----------+------------------------------------------------------------------------
  WM_CUT		|	0		 |	0		 |	������� ���������� ����� � ��������� ��� � ����� ������ 
  --------------+------------+-----------+------------------------------------------------------------------------
  WM_COPY		|	0		 |	0		 |	����������� ���������� ����� � ����� ������ Windows 
  --------------+------------+-----------+------------------------------------------------------------------------
  WM_PASTE		|	0		 |	0		 |	�������� ����� �� ������ ������ � �����, ��������������� ������� ������  
  --------------+------------+-----------+------------------------------------------------------------------------
  WM_UNDO		|	0		 |	0		 |	�������� ��������� �������� 
  --------------+------------+-----------+------------------------------------------------------------------------
  WM_GETTEXT	|	nMax	 |	szBuffer |	����������� ����� (�� ����� nMax ��������) �� �������� ���������� � ����� szBuffer 
  --------------+------------+-----------+------------------------------------------------------------------------

*/



int main()
{
    return 0;
}

