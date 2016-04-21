#pragma once
#include <Windows.h>
class Application
{
	HWND hEditPath;
	HWND hBtnRead;
	HWND hStaticOutputs[3];
public:
	static Application* _this;
	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	VOID Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	VOID Cls_OnClose(HWND hwnd);
	INT startProgramm(INT dlg);
	Application();
	~Application();
	
};

