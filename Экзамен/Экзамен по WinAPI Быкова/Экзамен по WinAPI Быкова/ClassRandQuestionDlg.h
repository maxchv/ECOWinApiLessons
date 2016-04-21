#pragma once
#include "Include.h"

class RandQuestionDlg
{
public:
	/***************************************************************************/
	RandQuestionDlg();
	~RandQuestionDlg();
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static RandQuestionDlg* _this;
private:
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	/*********************************************************************************/
	static DWORD WINAPI Thread(LPVOID lp);
	void OpenFileQuestions();
	/*********************************************************************************/
	HWND hParent, hStaticResult, hEditWay;
	HINSTANCE hInst;
	TCHAR filename[256];
	char strFile[MAX_PATH];
	int rand_num[3];
	std::wstringstream _sstr;
	HANDLE hThread;
};
