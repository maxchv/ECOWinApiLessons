// Lesson16.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

// ���������� ����������� ���������
/*
1.	��� ����� ����������� ����?
2.	��� ����� ������� � ������� ��������� �������� 
	��������� WM_CONTEXTMENU?
3.	����� ������� API ��������� ���������� ����������� 
	����?
4.	��� ����� ������������?
5.	��� ��������� ������������ � �������?
6.	����� ������� API ��������� ��������� � ������ 
	���������� ������� �������������?
7.	� ����� ����� � ���������� ������������ ������� 
	API TranslateAccelerator?
*/

// �������������� ��������� �������
/*
������ �������������� ���������� ���� ������������� ��� 
������� ����������� �������� ����������.
���� ����� �������������� ������� ���������� ��� ������ 
������� ����, � ������� � ����� �������� ����� ���������.

����� �������� ��������������� ����������� ���� ��������  
������  �Property Pages�  ���  ��������  ��������  �������  
�  �����  Microsoft Visual Studio.

������� ��������� �������������� �������� ����� ������� �������
���������, ���������� ���, ������ ���������� ��������.
*/

// ������������ ����� ������
/*
���������� ���� ������ ���������� � ������������. 

�������� ����� ������������ ��������� ���������� ����. 
��� ��������, ��� ���������� ���������� ���������� ������� � 
������ ����� ��� ���������� ����� ����������. 
��� ���� ��������� ������ �� ������ ���������� �� ��������� 
������������ �������� � ������� ������ ����� �� ����������, 
������ ��������� ������������� �� ������ � ������� ������������.

��� �������� � ����������� ��������������� ���������� ����������� 
���� ��������� ��������� ��������� ��������:
�	���������� ������ � ����� �������� ��������;
�	���������� � ���������� ���������� ���������,  
	�������������� ��������� ��������� ��� ��������������� 
	����������� ����;
�	������� ������� API DialogBox  ��� ����������� ���������� 
	�������.

������� �������� ��� ������� �������� ������ ��������������� 
����������� ����:
	�	�������� ������ ����� public-���� ������
		���������������  �������;
	�	�������� ������ ����� ��������������� ����������� 
		������ ���������������  �������.

������� �������� ��� ������� �������� ������ �������� 
����������� ����:
	�	�������� ������ ����� public-���� ������   
		���������������  �������;
	�	���������������� ��������� � �������� ���� ����������.
		
������ ������� ������������ ��������� ����������� �������� ���� 
���������� � ������� ������� API GetParent

HWND GetParent(          
     HWND hWnd // ���������� ��������� ����
);
*/


// ����������� ������� ��������� � ���������� ���
/*
����� ����������� �������
https://msdn.microsoft.com/en-us/library/windows/desktop/ff468806%28v=vs.85%29.aspx

�������� �������, �������
https://msdn.microsoft.com/en-us/library/windows/desktop/ms646960%28v=vs.85%29.aspx

����������� ������ ��������� ������������� ������������ 
����������� ������ ����� ��� ������ ������ ��� ��������. 
��� �������� � ����������� ���������� ������� ��������� 
������������� ������� API GetOpenFileName.

BOOL GetOpenFileName(
	LPOPENFILENAME lpofn // ��������� �� ��������� OPENFILENAME, 
						 // ������� �������� ����������, 
						 // ������������ ��� ������������� �������
);
https://msdn.microsoft.com/en-us/library/windows/desktop/ms646927%28v=vs.85%29.aspx

������:
https://msdn.microsoft.com/en-us/library/windows/desktop/ms646829%28v=vs.85%29.aspx#open_file

������ ������� ������ ��������� ��������, ���� ��� ������ ����� 
����� ������ ������ OK (�������).

����������� ������ ���������� ��� ������������� ��������-���� ����������� ������ ����� ��� ����������. ��� �������� � ����-������� ���������� ������� ���������� ��� ������������� ����-��� API GetSaveFileName.

BOOL GetSaveFileName(
	LPOPENFILENAME lpofn // ��������� �� ��������� OPENFILENAME,
						 // ������� �������� ����������, 
						 // ������������ ��� ������������� �������
);
https://msdn.microsoft.com/en-us/library/windows/desktop/ms646928%28v=vs.85%29.aspx

������ ������� ������ ��������� ��������, ���� ��� ������ ����� 
����� ������ ������ OK (���������).
*/

// ��������� OPENFILENAME
/*
��� ������������� ������� � �������� ��������� ��������� 
��������� �� ��������� OPENFILENAME, ������� �������� 
����������, ������������ ��� ������������� �������.
https://msdn.microsoft.com/en-us/library/windows/desktop/ms646839%28v=vs.85%29.aspx

typedef struct tagOFN {
	DWORD         lStructSize;		// ������ ��������� � ������
	HWND          hwndOwner;		// ���������� ����, ������� ������� 
									// ��������
	HINSTANCE     hInstance;		// ���������� ����������, ���� 
									// ���������� ����   
									// OFN_ENABLETEMPLATE, ���� ���������� 
									// ������� ������, ����������� ������   
									// ����������� ����, ���� ���������� 
									// ���� OFN_ENABLETEMPLATEHANDLE
	LPCTSTR       lpstrFilter;		// ��������� �� �����, ���������� ���� 
									// ��� ��������� ��� ��������� �����, 
									// �������� ������� ��� ������ ���� ������
	LPTSTR        lpstrCustomFilter; // ��������� �� ����������� �����, 
									// ������� �������� ���� ��������� ����� 
									// ������� ��� ���������� ������ �������,  
									// ���������� �������������
	DWORD         nMaxCustFilter;	// ������ ������ � ������
	DWORD         nFilterIndex;		// ������ �������� ���������� �������
	LPTSTR        lpstrFile;		// ��������� �� �����, ���������� ��� ����� ���  // ������������� ���������� ���� File Name �������. ����� ������ ����� �    // �������� ������� ����� ����� ��������� ������ ���� � ���������� �����
	DWORD         nMaxFile;			// ������ ������ � ������
	LPTSTR        lpstrFileTitle;	// ��������� �� �����, ���������� ��� �            // ���������� ���������� �����
	DWORD         nMaxFileTitle;	//  ������ ������ � ������
	LPCTSTR       lpstrInitialDir;	// ��������� �� ������, ������� ����������
									// ��������� �������
	LPCTSTR       lpstrTitle;		// ��������� �� ������, ������� 
									// ���������� ��������� ����������� ����
	DWORD         Flags;			// ���������� �� ������ ��� ���������� ������,
									// ������������  � ������� �������� 
									// ���������� "���" (|), �����������       
									// ��������� ������� ��� �������
	WORD          nFileOffset;		// ������������� �� ���� �������� �� ������ 
									// ���� �� ����� ����� � ������ lpstrFile
	WORD          nFileExtension;	// ������������� �� ���� �������� �� ������ 
									// ���� �� ���������� ����� ����� � ������ 
									//	lpstrFile
	LPCTSTR       lpstrDefExt;		// ������ ��� ��������� �� �����, �������  
									// ��������  ���������� ����� �����, 
									// ������������ �� ���������
	LPARAM        lCustData;		// ������, ������� ���������� � HOOK-���������
	LPOFNHOOKPROC lpfnHook;			// ����� HOOK-��������� (������ ���� ������� 
									// ���� OFN_ENABLEHOOK)
	LPCTSTR       lpTemplateName;	// ��������� �� ������, ������� �������       
									// ������ ������� ������� � ������, 
									// ������������������ ����� hInstance
#if (_WIN32_WINNT >= 0x0500)
	void *        pvReserved;		// �������������� � ������ ���� 0
	DWORD         dwReserved;		// �������������� � ������ ���� 0
	DWORD         FlagsEx;			// ������� �������� ���� ���� OFN_EX_NOPLACESBAR
#endif // (_WIN32_WINNT >= 0x0500)
} OPENFILENAME, *LPOPENFILENAME;


���� Flags ��������� OPENFILENAME ������������ ����� ���������� �� ������ ���
���������� ������, ������������ � ������� ����������� �������� ���Ȼ, 
� ����������� ���������  ������� ��� �������. ���� ������������ �������� 
����� ������������ �����.

�	OFN_ALLOWMULTISELECT - ��������� ����� ���������� ���-��� ������������.
�	OFN_CREATEPROMPT -	���� ������������ ���������� ������-�������� ����, 
						�� ��������� ������, � ������� ������������ ������� ����.
�	OFN_EXTENSIONDIFFERENT - ��������������� ����� �������� �������  � ���������, 
						��� ���������� ���������� ����� ������-���� �� ����, 
						������� ���� ����� ���������� � ���� lpstrDefExt. 
						���� ���� �� ���������������, ���� � ���� lpstrDefExt 
						��� ���������� NULL ��� ���� �� ����� ����������.
�	OFN_FILEMUSTEXIST - ����������, ��� � ���� FileName ����-�������� ����� �������
						������ ����� ������������ ������. � ��������� ������ �� 
						����� ����� ���������� ��������������� ���������. ���� 
						���� ���� ���������, �� ������������� ��������������� 
						���� OFN_PATHMUSTEXIST.
�	OFN_HIDEREADONLY -	������������ ������ �� ������� ���-��� Read Only (������ 
						������).
�	OFN_NONETWORKBUTTON - �������� � ��������� ������ Network (����).
�	OFN_NOREADONLYRETURN - ����������, ��� ��������� ���� �� ����� �������� 
						������� ������ � �� ������������� � ����-������ �� ������ 
						��������.
�	OFN_NOTESTFILECREATE - ����������, ��� ���� �� ��������� ����� ��������� 
						�������.
�	OFN_NOVALIDATE -	����������, ��� ����������� ������� ��-������� ������� 
						������������� �������� � ������ ���������-��� ������.
�	OFN_OVERWRITEPROMPT - ������������ ������� ������-���� ��� �������� ���� 
						������� �� ����������, ���� ������-��� ���� ��� ����������.
�	OFN_PATHMUSTEXIST - ����������, ��� ������������ ����� ������������ ������ 
						��������� ���� � ����� ������. � ��������� ������ �� 
						����� ����� ���������� ��������������� ���������.
�	OFN_READONLY -		��� ����������� ������� ������ Read Only (������  ������) 
						����� ����������.
*/

// ������������ �����
/*
����������� ���������� ���������� ��������, ����������  ��������� 
�����������������:

�	����������� �������� ������ ���������� ���������;
�	����������� �������� ������������� ���������� ���������;
�	����������� ���������� �������� ���������;
�	����������� ���������� �������� ��������� ��� ����� ������.

*/


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
