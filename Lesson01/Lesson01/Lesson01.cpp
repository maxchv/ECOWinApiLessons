// Lesson01.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <Windows.h>
#include <WinUser.h>
#include <iostream>
#pragma warning(disable: 4996)
using namespace std;

/*
	������ �1  �������� � Windows ���������������� � �������������� WinAPI
	������� �1
*/

// Unicode
// ��� ������ wchar_t
void ex00()
{
	
}

// ��������� ������� Unicode
void ex01()
{
	char *word1 = "Hello";
	char *word2 = "Word";
	char words[80];
	words[0] = '\0';

	// ��������� ������� ANSI C
	// char * strcat( char *,  const char *);
	

	// char * strchr(const char *, int);


	// int strcmp(const char *, const char *);
	

	// char * strcpy(char *, const char *);
	

	// size_t strlen(const char *);


	// ������������� Unicode-�������
	// ANSI �������, ������ �������� str �� wcs, �.�.
	// wide char string
	
	// wcschr(const wchar_t *, int)
	// int wcscmp(const wchar_t *, const wchar_t *)
	// wchar_t * wcscpy(wchar_t *, const wchar_t *);
	// size_t wcslen(const wchar_t *);
	
}

// ������� ��� ������ � Unicode
void ex02()
{

}

// ��������� ������� Windows
void ex03()
{
	// lstrcat	��������� ������������ �����	

	// lstrcmp	���������� ��� ������ � ������ �������� ����

	// lstrcmpi	���������� ��� ������ ��� ����� �������� ����

	// lstrcpy	�������� ������ � ������ ������� ������

	// lstrlen	���������� ����� ������ � ��������

}

// ������������� ����� �� ANSI � Unicode
void ex04()
{
	/*int MultiByteToWideChar(
		UINT CodePage,         // ������� ��������, �������� CP_ACP
		DWORD dwFlags,         // �������������� ���������, �������� ��   
							   // �������������� ���� � ��������������� �������
		LPCSTR lpMultiByteStr, // ��������� �� ������������� ������
		int cbMultiByte,       // ����� ������ � ������
		LPWSTR lpWideCharStr,  // ��������� �� �����, ���� ��������� Unicode-������ 
		int cchWideChar        // ������ ������
	);*/
	
		
	/*
	����������� �������������� ��������� ������� �� �/�++ Run-Time Library
	size_t mbstowcs(
		wchar_t * wcstr,//��������������� Unicode-������
		const char * mbstr,//�������� ANSI-������
		size_t count //������������ ����� �������� �������� ������
		);
	*/
	
}

// ������������� ����� �� Unicode � ANSI
void ex05()
{
	/* ��� �������������� Unicode - ����� � ANSI  ������������ ��������� ������� :

	int WideCharToMultiByte(
		UINT CodePage,          // ������� ��������, yfghbvth
		DWORD dwFlags,          // �������������� ���������, �������� �� 
						        //�������������� ���� � ��������������� �������
		LPCWSTR lpWideCharStr,  // ��������� �� ������������� Unicode-������
		int cchWideChar,        // ���������� �������� � ������.
		LPSTR lpMultiByteStr,   // ��������� �� �����, ���� ��������� ����� ������
		int cbMultiByte,        // ������ ������
		LPCSTR lpDefaultChar,   // ������� ���������� ������ �� ���������, ���� //������������� ������ �� ����������� � ������� ��������
		LPBOOL lpUsedDefaultChar// ��������� �� ����, ��������������� �� �������� //�������������� ���� �������� (� ���� ������ � FALSE)
		);
	*/

	/*����������� �������������� ��������� ������� �� �/�++ Run-Time Library 

	size_t wcstombs(
		char * mbstr,		    //��������������� ANSI-������
		const wchar_t * wcstr,  //�������� Unicode-������
		size_t count            //������������ ����� �������� �������� ������
		);
	*/
}

// ���������������� Windows - ����������.
// �	����������� ��������� ������������; 
// �	��������������� � ���������������;
// �	���������� �������;
// �	������������� �� ���������� �������.
// �������. 
// ���������. (winuser.h)
// ������� ���������.
// ����. ���������� (handle)

int main()
{
	//cout << "������!!!" << endl;
	//ex00();
	//ex01();
	//ex02();
	//ex04();
	return 0;
}

