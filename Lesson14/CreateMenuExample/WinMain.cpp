#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include "resource.h"

#pragma comment(lib, "comctl32")

class Application
{	
	HWND hStatus;	
	bool isStatusEnabled = true;	
	const HINSTANCE hInstance;	
	const int id_dlg;
	static Application* _this;
	int width;
	int height;
	HMENU hMenu;
	HMENU hEdit;
public:
	
	Application(int id_dialog) : hInstance(GetModuleHandle(0)), id_dlg(id_dialog)
	{	
		_this = this;
	}

	
	int Run()
	{
		return DialogBox(hInstance, MAKEINTRESOURCE(id_dlg), NULL, Application::DlgProc);
	}

	static INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			HANDLE_MSG(hDlg, WM_INITDIALOG, _this->Cls_OnInitDialog);
			HANDLE_MSG(hDlg, WM_MENUSELECT, _this->Cls_OnMenuSelect);
			HANDLE_MSG(hDlg, WM_COMMAND, _this->Cls_OnCommand);
			HANDLE_MSG(hDlg, WM_CLOSE, _this->Cls_OnClose);
			HANDLE_MSG(hDlg, WM_SIZE, _this->Cls_OnSize);
		}
		return FALSE;
	}

	void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy)
	{
		width = cx;
		height = cy;
		SendMessage(hStatus, WM_SIZE, 0, 0);
	}

	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
	{
		// Create Menu Here
		


		// Status Bar
		hStatus = CreateStatusWindow(WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, hwnd, IDD_STATUSBAR);
		
		return FALSE;
	}

	void Cls_OnMenuSelect(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags)
	{		
		switch (item)
		{
		case ID_FILE_NEW:			
			SendMessage(hStatus, WM_SETTEXT, 0, (LPARAM)TEXT("New file"));
			break;
		case ID_FILE_OPEN:
			SendMessage(hStatus, WM_SETTEXT, 0, (LPARAM)TEXT("Open file"));
			break;
		case ID_FILE_SAVE:
			SendMessage(hStatus, WM_SETTEXT, 0, (LPARAM)TEXT("Save file"));
			break;
		case ID_FILE_SAVE_AS:
			SendMessage(hStatus, WM_SETTEXT, 0, (LPARAM)TEXT("Save file as..."));
			break;
		case ID_FILE_PRINT:
			SendMessage(hStatus, WM_SETTEXT, 0, (LPARAM)TEXT("Print..."));
			break;
		case ID_FILE_PAGE_SETUP:
			SendMessage(hStatus, WM_SETTEXT, 0, (LPARAM)TEXT("Page setup..."));
			break;
		case ID_FILE_EXIT:
			SendMessage(hStatus, WM_SETTEXT, 0, (LPARAM)TEXT("Close the program"));
			break;
		default:
			SendMessage(hStatus, WM_SETTEXT, 0, (LPARAM)TEXT("Ready"));
			break;
		}
	}

	void Cls_OnClose(HWND hDlg)
	{
		EndDialog(hDlg, 0);
	}

	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
	{
		switch (id)
		{
		case ID_FILE_EXIT:
			SendMessage(hwnd, WM_CLOSE, NULL, NULL);
		default:
			break;
		}
	}
};

Application* Application::_this = nullptr;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdArgs, int nCmdOpt)
{
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);

	Application app(IDD_DIALOG1);

	return app.Run();
}