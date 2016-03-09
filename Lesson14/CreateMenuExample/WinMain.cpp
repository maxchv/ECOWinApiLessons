#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include "resource.h"
#include "Defines.h"

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
	HMENU hContextMenu;
	HMENU hEdit;
	HWND hButton;

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
			HANDLE_MSG(hDlg, WM_CONTEXTMENU, _this->Cls_OnContextMenu);
		}
		return FALSE;
	}

	void Cls_OnContextMenu(HWND hwnd, HWND hwndContext, UINT xPos, UINT yPos)
	{
		//if (hwndContext == hButton) 
		{
			TrackPopupMenu(hContextMenu, TPM_BOTTOMALIGN, xPos, yPos, 0, hwndContext, 0);
		}
		
	}

	void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy)
	{
		width = cx;
		height = cy;
		SendMessage(hStatus, WM_SIZE, 0, 0);
	}

	void CreateMainMenu(HWND hwnd)
	{
		// Главное меню
		hMenu = CreateMenu();

		// Подменю файл
		HMENU hFileSubMenu = CreatePopupMenu();

		AppendMenu(hFileSubMenu, MF_STRING, ID_FILE_NEW, TEXT("&New file"));
		AppendMenu(hFileSubMenu, MF_BITMAP, ID_FILE_NEW, (LPCWSTR) "&Open");
		AppendMenu(hFileSubMenu, MF_STRING, ID_FILE_OPEN, TEXT("&Open file"));
		AppendMenu(hFileSubMenu, MF_STRING, ID_FILE_SAVE, TEXT("&Save file"));
		AppendMenu(hFileSubMenu, MF_STRING, ID_FILE_SAVE_AS, TEXT("S&ave as..."));
		AppendMenu(hFileSubMenu, MF_STRING, ID_FILE_PRINT, TEXT("&Print..."));
		AppendMenu(hFileSubMenu, MF_STRING, ID_FILE_PAGE_SETUP, TEXT("Pa&ge setup..."));
		AppendMenu(hFileSubMenu, MF_STRING, ID_FILE_EXIT, TEXT("E&xit"));

		InsertMenu(hFileSubMenu, ID_FILE_EXIT, MF_BYCOMMAND | MF_SEPARATOR, 0, 0);
		InsertMenu(hFileSubMenu, ID_FILE_PRINT, MF_BYCOMMAND | MF_STRING, 0, TEXT("New item"));
		InsertMenu(hFileSubMenu, ID_FILE_PRINT, MF_BYCOMMAND | MF_SEPARATOR, 0, 0);

		// удаление подпункта меню
		DeleteMenu(hFileSubMenu, 4, MF_BYPOSITION);

		// Подменю Edit
		HMENU hEditMenu = CreatePopupMenu();

		AppendMenu(hEditMenu, MF_STRING, ID_EDIT_COPY, TEXT("Copy"));
		AppendMenu(hEditMenu, MF_STRING, ID_EDIT_CUT, TEXT("Cut"));
		AppendMenu(hEditMenu, MF_STRING, ID_EDIT_PASTE, TEXT("Paste"));

		TCHAR str[50];
		GetMenuString(hEditMenu, ID_EDIT_PASTE, str, 49, MF_BYCOMMAND);

		ModifyMenu(hEditMenu, ID_EDIT_PASTE, MF_BYCOMMAND | MF_DISABLED, ID_EDIT_PASTE, str);

		// Добавление подменю в главное меню приложения
		AppendMenu(hMenu, MF_POPUP | MF_STRING, (UINT_PTR)hFileSubMenu, TEXT("&File"));
		AppendMenu(hMenu, MF_POPUP | MF_STRING, (UINT_PTR)hEditMenu, TEXT("&Edit"));

		SetMenu(hwnd, hMenu);
	}

	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
	{
		// Create Menu Here
		CreateMainMenu(hwnd);
		
		// Context menu
		HMENU tmp = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
		hContextMenu = GetSubMenu(tmp, 0);

		// Status Bar
		hStatus = CreateStatusWindow(WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, hwnd, IDD_STATUSBAR);
		
		hButton = GetDlgItem(hwnd, IDC_BTNDELETE);

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
		case IDC_BTNDELETE:
			DeleteMenu(hMenu, 1, MF_BYPOSITION);
			DrawMenuBar(hwnd); // перерисовка главного меню					
			break;
		case ID_CONTEXTMENU_EXIT:
		case ID_FILE_EXIT:
			SendMessage(hwnd, WM_CLOSE, NULL, NULL);
			break;
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