// Lesson01.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <Windows.h>
#include <WinUser.h>
#include <iostream>
#pragma warning(disable: 4996)
using namespace std;

/*
	������ �1  �������� � Windows ���������������� � �������������� Win  API
	������� �1
*/

// Unicode
// ��� ������ wchar_t
void ex00()
{
	char ch;
	wchar_t wch;
	cout << "wide char: " << sizeof(wch) << endl;
	cout << "char: " << sizeof(ch) << endl;

	wch = 'h';
	wcout << wch << endl;
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
	/*strcat(words, word1);
	strcat(words, ", ");
	strcat(words, word2);
	strcat(words, "!");
	cout << words << endl;*/
	strcat(words, word1);
	strcat(words, ", ");
	strcat(words, word2);
	strcat(words, "!");
	cout << words << endl;

	// char * strchr(const char *, int);
	char * find = strchr(words, ',');
	find++;
	cout << find << endl;

	// int strcmp(const char *, const char *);
	cout << strcmp(word1, word2) << endl;
	cout << strcmp("word ", "word") << endl;

	// char * strcpy(char *, const char *);
	strcpy(words, word1);
	cout << words << endl;

	// size_t strlen(const char *);
	cout << strlen(words) << endl;

	wchar_t *uword1 = L"Hello";
	wchar_t *uword2 = L"Word";
	wchar_t uwords[80];
	uwords[0] = '\0';

	// ������������� Unicode-�������
	// ANSI �������, ������ �������� str �� wcs, �.�.
	// wide char string
	wcscat(uwords, uword1);
	wcscat(uwords, L", ");
	wcscat(uwords, uword2);
	wcscat(uwords, L"!");
	wcout << uwords << endl;
	// wcschr(const wchar_t *, int)
	// int wcscmp(const wchar_t *, const wchar_t *)
	// wchar_t * wcscpy(wchar_t *, const wchar_t *);
	// size_t wcslen(const wchar_t *);
	cout << sizeof(uwords) << endl;
	cout << wcslen(uword1) << endl;
}

// ������� ��� ������ � Unicode
void ex02()
{
#ifdef _UNICODE
	cout << "using unicode" << endl;
#else
	cout << "using multibyte" << endl;
#endif
	_TCHAR * str = _TEXT("My Unicode string");
	cout << "_TCHAR: " << sizeof(_TCHAR) << endl;

	// _TEXT

	// _tcscat
	_TCHAR wstr[50];
	wstr[0] = '\0';
	_tcscat(wstr, str);
	
	// ��������� _UNICODE
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
	char *str = "string";
	// ������������ ����� ������
	int len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	cout << len << endl;
	wchar_t *wstr = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, str, len, wstr, len);
	wcout << wstr << endl;
	delete[] wstr;
		
	/*
	����������� �������������� ��������� ������� �� �/�++ Run-Time Library
	size_t mbstowcs(
		wchar_t * wcstr,//��������������� Unicode-������
		const char * mbstr,//�������� ANSI-������
		size_t count //������������ ����� �������� �������� ������
		);
	*/
	wchar_t *ustr;
	// ������������ ����� ������
	len = mbstowcs(NULL, str, 0);
	ustr = new wchar_t[len];
	mbstowcs(ustr, str, 0);
	wcout << ustr << endl;
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
	ex04();
	return 0;
}

