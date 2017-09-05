// программа работает только с  алькул€тором который прилагаетс€ к проэкту

#pragma once
#pragma warning (disable: 4996)
#include <Windows.h>
#include<vector>
#include<sstream>
#include<ctime>
#include<string>
#include <algorithm>

using namespace std;

#define INTERVAL 100      // интервал перемещени€ окна в мс
#define X_INDENT 300      // x - отступ по горизонтали
#define Y_INDENT 300      // y - отступ по вертикали
#define PRINT_INDENT 30   // отступ внутри окна дл€ вывода текста
#define WIDTH_WINDOW 450  // ширина окна
#define HEIGHT_WINDOW 250 // высота окна
#define ID_MYTIMER 1

/*«адание 2.
Ќаписать программу в которой при нажатии на кнопку Enter в
открытом приложении  алькул€тор в случайном пор€дке начинают
по€вл€тьс€/пропадать кнопки.*/