// ��������� �������� ������ � ������������� ������� ����������� � �������

#pragma once
#pragma warning (disable: 4996)
#include <Windows.h>
#include<vector>
#include<sstream>
#include<ctime>
#include<string>
#include <algorithm>

using namespace std;

#define INTERVAL 100      // �������� ����������� ���� � ��
#define X_INDENT 300      // x - ������ �� �����������
#define Y_INDENT 300      // y - ������ �� ���������
#define PRINT_INDENT 30   // ������ ������ ���� ��� ������ ������
#define WIDTH_WINDOW 450  // ������ ����
#define HEIGHT_WINDOW 250 // ������ ����
#define ID_MYTIMER 1

/*������� 2.
�������� ��������� � ������� ��� ������� �� ������ Enter �
�������� ���������� ����������� � ��������� ������� ��������
����������/��������� ������.*/