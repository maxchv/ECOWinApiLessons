#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include "resource.h"

#pragma comment(lib, "comctl32")

class Application
{
	// Дескриптор строки состояния
	HWND hStatus;
	// Указатель на видимость строки состояния
	bool isStatusEnabled = true;
	// Дескриптор экземпляра приложения
	const HINSTANCE hInstance;	
	// 
	const int id_dlg;
	const int LANG = 100;
	static Application* _this;

	HMENU hMenu;
	HMENU hEdit;
public:
	// Конструктор
	Application(int id_dialog): hInstance(GetModuleHandle(0)), id_dlg(id_dialog)
	{
		INITCOMMONCONTROLSEX icc;
		icc.dwSize = sizeof(icc);
		icc.dwICC = ICC_WIN95_CLASSES;
		InitCommonControlsEx(&icc);
		_this = this;
	}

	// Запустить приложение
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
		}
		return FALSE;
	}

	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
	{
		hMenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));
		SetMenu(hwnd, hMenu);

		hStatus = CreateStatusWindow(WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP | SBARS_TOOLTIPS, TEXT("Ready"), hwnd, IDC_STATUSBAR);
		hEdit = GetSubMenu(hMenu, 1);

		EnableMenuItem(hEdit, 0, MF_BYPOSITION | MF_GRAYED);
		EnableMenuItem(hEdit, ID_EDIT_PASTE, MF_BYCOMMAND | MF_GRAYED);
		EnableMenuItem(hEdit, ID_EDIT_CUT, MF_BYCOMMAND | MF_GRAYED);

		DrawMenuBar(hwnd);

		return FALSE;
	}

	void Cls_OnMenuSelect(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags)
	{
		TCHAR statusMessage[50];
		switch (item)
		{
		case ID_FILE_NEW:
			LoadString(GetModuleHandle(0), IDS_CREATEFILE + LANG, statusMessage, 50);
			SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)statusMessage);
			break;
		case ID_FILE_OPEN:
			SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)TEXT("Open file"));
			break;
		case ID_FILE_SAVE:
			SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)TEXT("Save file"));
			break;
		case ID_FILE_EXIT:
			SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)TEXT("Close the program"));
			break;
		default:
			SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)TEXT("Ready"));
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
		case ID_EDIT_STATUSBAR:
			if (isStatusEnabled)
			{
				CheckMenuItem(hMenu, ID_EDIT_STATUSBAR, MF_BYCOMMAND | MF_UNCHECKED);
				ShowWindow(hStatus, SW_HIDE);
			}
			else
			{
				CheckMenuItem(hMenu, ID_EDIT_STATUSBAR, MF_BYCOMMAND | MF_CHECKED);
				ShowWindow(hStatus, SW_SHOW);
			}
			isStatusEnabled = !isStatusEnabled;
			break;
		case IDOK:
		case ID_FILE_EXIT:
			SendMessage(hwnd, WM_CLOSE, NULL, NULL);
			break;
		}
	}
};

Application* Application::_this = nullptr;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdArgs, int nCmdOpt)
{
	Application app(IDD_DIALOG1);

	return app.Run();
}



