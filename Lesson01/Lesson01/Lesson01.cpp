// Lesson01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
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

	// char * strchr(const char *, int);
	/*char * find = strchr(words, ',');
	cout << find << endl;*/

	// int strcmp(const char *, const char *);
	/*cout << strcmp(word1, word2) << endl;*/

	// char * strcpy(char *, const char *);
	/*strcpy(words, word1);
	cout << words << endl;*/

	// size_t strlen(const char *);
	/*cout << strlen(words) << endl;*/

	// ������������� Unicode-�������

}

// ������� ��� ������ � Unicode
void ex02()
{
	// _TCHAR

	// _TEXT

	// _tcscat

	// ��������� __UNICODE
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

	/*����������� �������������� ��������� ������� �� � / �++ Run - Time Library :

	size_t wcstombs(
		char * mbstr, //��������������� ANSI-������
		const wchar_t * wcstr, //�������� Unicode-������
		size_t count //������������ ����� �������� �������� ������
		);
	*/
}

// ���������������� Windows - ����������.
// �	����������� ��������� ������������; 
// �	��������������� � ���������������;
// �	���������� �������;
// �	������������� �� ���������� �������.
// �������. ���������. ������� ���������.
// ����.

int main()
{
	return 0;
}

