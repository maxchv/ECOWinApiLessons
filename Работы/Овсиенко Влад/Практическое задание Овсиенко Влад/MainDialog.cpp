#include "stdafx.h"
#include "MainDialog.h"

CMainDialog* CMainDialog::ptr = NULL;

CMainDialog::CMainDialog(void)
{
	ptr = this;
}

CMainDialog::~CMainDialog(void)
{

}

void CMainDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

void CMainDialog::Static_1(HWND hwnd)
{
	r_line1 = rand() % 87;

	ifstream file("Вопросы на экзамен.txt");//путь к файлу
	char open_file1[255];
	TCHAR buf1[255];
	int index1 = -1;
	do
	{
		index1++;
		if (index1 == r_line1)
		{
			file.getline(open_file1, 255);//считывает одну строку файла
			//MultiByteToWideChar(CP_UTF8, 0, open_file1, 255, buf1, 255);
			//wcstombs(open_file1, buf1, 255);
			SetWindowText(hStatic1, (LPWSTR)open_file1);
		}
	} while (!file.eof());
}

void CMainDialog::Static_2(HWND hwnd)
{
	r_line2 = rand() % 87;
}

void CMainDialog::Static_3(HWND hwnd)
{
	r_line3 = rand() % 87;
}

BOOL CMainDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hStatic1 = GetDlgItem(hwnd, IDC_STATIC1);
	hStatic2 = GetDlgItem(hwnd, IDC_STATIC2);
	hStatic3 = GetDlgItem(hwnd, IDC_STATIC3);

	Static_1(hwnd);
	Static_2(hwnd);
	Static_3(hwnd);

	/*
	int name;
	int i;
	ifstream file("Вопросы на экзамен.txt");//путь к файлу
	while (!file.eof())
	{
		file.getline(name, sizeof(name));
		i--;
		if (i == r_line1)break;
	}
	cout << name;*/

	/*ifstream file("Вопросы на экзамен.txt");
	char open_file1[255] = { '\0' };
	TCHAR buf1[255] = { '\0' };
	int index1 = -1;
	do
	{
		index1++;
		if (index1 == r_line1)
		{
			MultiByteToWideChar(CP_UTF8, 0, open_file1, 255, buf1, 255);
			SetWindowText(hStatic1, buf1);
			file.getline(open_file1, 255);
		}
	} while (!file.eof());*/

	/*TCHAR* b = 0;
	ifstream file("Вопросы на экзамен.txt");
	while (file)
	{
		string str;
		getline(file, str);
		b = new TCHAR[str.size() + 1];
		copy(str.begin(), str.end(), b);
		SetWindowText(hStatic1, b);
	};*/
	return TRUE;
}

void CMainDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
}

BOOL CALLBACK CMainDialog::DlgProc(HWND hwnd, UINT mes, WPARAM wParam, LPARAM lParam)
{
	switch (mes)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
	}
	return FALSE;
}
