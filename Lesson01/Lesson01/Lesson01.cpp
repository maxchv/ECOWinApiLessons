// Lesson01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#pragma warning(disable: 4996)
using namespace std;

/*
	Модуль №1  Введение в Windows программирование с использованием Win  API
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

	// Эквивалентные Unicode-функции

}

// Макросы для работы с Unicode
void ex02()
{
	// _TCHAR

	// _TEXT

	// _tcscat

	// константа __UNICODE
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

	/*Аналогичные преобразования выполняет функция из С / С++ Run - Time Library :

	size_t wcstombs(
		char * mbstr, //преобразованная ANSI-строка
		const wchar_t * wcstr, //исходная Unicode-строка
		size_t count //максимальное число символов исходной строки
		);
	*/
}

// Программирование Windows - приложений.
// •	графический интерфейс пользователя; 
// •	многозадачность и многопоточность;
// •	управление памятью;
// •	независимость от аппаратных средств.
// Событие. Сообщение. Очередь сообщений.
// Окно.

int main()
{
	return 0;
}

