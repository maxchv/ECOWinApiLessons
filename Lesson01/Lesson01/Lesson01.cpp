// Lesson01.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <Windows.h>
#include <WinUser.h>
#include <iostream>
#pragma warning(disable: 4996)
using namespace std;

/*
	Модуль №1  Введение в Windows программирование с использованием WinAPI
	Занятие №1
*/

// Unicode
// тип данных wchar_t
void ex00()
{
	
}

// Строковые функции Unicode
void ex01()
{
	char *word1 = "Hello";
	char *word2 = "Word";
	char words[80];
	words[0] = '\0';

	// Строковые функции ANSI C
	// char * strcat( char *,  const char *);
	

	// char * strchr(const char *, int);


	// int strcmp(const char *, const char *);
	

	// char * strcpy(char *, const char *);
	

	// size_t strlen(const char *);


	// Эквивалентные Unicode-функции
	// ANSI функции, только заменить str на wcs, т.е.
	// wide char string
	
	// wcschr(const wchar_t *, int)
	// int wcscmp(const wchar_t *, const wchar_t *)
	// wchar_t * wcscpy(wchar_t *, const wchar_t *);
	// size_t wcslen(const wchar_t *);
	
}

// Макросы для работы с Unicode
void ex02()
{

}

// Строковые функции Windows
void ex03()
{
	// lstrcat	Выполняет конкатенацию строк	

	// lstrcmp	Сравнивает две строки с учетом регистра букв

	// lstrcmpi	Сравнивает две строки без учета регистра букв

	// lstrcpy	Копирует строку в другой участок памяти

	// lstrlen	Возвращает длину строки в символах

}

// Перекодировка строк из ANSI в Unicode
void ex04()
{
	/*int MultiByteToWideChar(
		UINT CodePage,         // кодовая страница, например CP_ACP
		DWORD dwFlags,         // дополнительные настройки, влияющие на   
							   // преобразование букв с диакритическими знаками
		LPCSTR lpMultiByteStr, // указатель на преобразуемую строку
		int cbMultiByte,       // длина строки в байтах
		LPWSTR lpWideCharStr,  // указатель на буфер, куда запишется Unicode-строка 
		int cchWideChar        // размер буфера
	);*/
	
		
	/*
	аналогичные преобразования выполняет функция из С/С++ Run-Time Library
	size_t mbstowcs(
		wchar_t * wcstr,//преобразованная Unicode-строка
		const char * mbstr,//исходная ANSI-строка
		size_t count //максимальное число символов исходной строки
		);
	*/
	
}

// Перекодировка строк из Unicode в ANSI
void ex05()
{
	/* Для преобразования Unicode - строк в ANSI  используется следующая функция :

	int WideCharToMultiByte(
		UINT CodePage,          // кодовая страница, yfghbvth
		DWORD dwFlags,          // дополнительные настройки, влияющие на 
						        //преобразование букв с диакритическими знаками
		LPCWSTR lpWideCharStr,  // указатель на преобразуемую Unicode-строку
		int cchWideChar,        // количество символов в строке.
		LPSTR lpMultiByteStr,   // указатель на буфер, куда запишется новая строка
		int cbMultiByte,        // размер буфера
		LPCSTR lpDefaultChar,   // функция использует символ по умолчанию, если //преобразуемый символ не представлен в кодовой странице
		LPBOOL lpUsedDefaultChar// указатель на флаг, сигнализирующий об успешном //преобразовании всех символов (в этом случае – FALSE)
		);
	*/

	/*Аналогичные преобразования выполняет функция из С/С++ Run-Time Library 

	size_t wcstombs(
		char * mbstr,		    //преобразованная ANSI-строка
		const wchar_t * wcstr,  //исходная Unicode-строка
		size_t count            //максимальное число символов исходной строки
		);
	*/
}

// Программирование Windows - приложений.
// •	графический интерфейс пользователя; 
// •	многозадачность и многопоточность;
// •	управление памятью;
// •	независимость от аппаратных средств.
// Событие. 
// Сообщение. (winuser.h)
// Очередь сообщений.
// Окно. дескриптор (handle)

int main()
{
	//cout << "Привет!!!" << endl;
	//ex00();
	//ex01();
	//ex02();
	//ex04();
	return 0;
}

