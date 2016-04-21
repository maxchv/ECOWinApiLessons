#pragma once
#include "header.h"
#include "resource.h"
class Generate_Text
{
public:
	Generate_Text(void);
public:
	~Generate_Text(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static Generate_Text* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);

	void Read(HWND hwnd);
	void Write(HWND hwnd);
	HWND hEdit_1, hEdit_2, hEdit_3, hBTNGenerate, hBTNStart, hEdit_Path, hEdit_Get_text, hStatic;

	TCHAR buffFile[100];//, buffCopy[100];
	std::wstringstream _sstr;
	int num_rand[3];
};
