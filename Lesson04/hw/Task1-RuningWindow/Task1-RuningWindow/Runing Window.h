#pragma once
#pragma warning (disable: 4996)
#include <Windows.h>


using namespace std;

#define STEP_RUN 10       // ��� ����������� ����
#define INTERVAL 300      // �������� ����������� ���� � ��
#define X_INDENT 30       // x - ������ �� �����������
#define Y_INDENT 30       // y - ������ �� ���������
#define WIDTH_WINDOW 400  // ������ ����
#define HEIGHT_WINDOW 250 // ������ ����
#define ID_MYTIMER 1


//������� 1.
//������� ���������� � ������� ��� ������� �� ������ Enter ����
//�������� ������������ �� ��������� ������(������� � ������ ��������
//	����) �� �����.��� ���������� ������� ���� �������� ����� ����
//	�������� �������� ���� � �.�.
//	�������� ����������� : 10 �������� �� 300 ��.
//	��� ������� ������ Esc �������� ������������
