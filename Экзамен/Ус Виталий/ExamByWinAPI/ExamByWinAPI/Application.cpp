#include "Application.h"
#include "include.h"

Application* Application::_this = NULL;
INT Application::startProgramm(int dlg)
{
	return DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(dlg), 0, DlgProc);
}
INT_PTR Application::DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		HANDLE_MSG(hWnd, WM_INITDIALOG, _this->Cls_OnInitDialog);
		HANDLE_MSG(hWnd, WM_COMMAND, _this->Cls_OnCommand);
		HANDLE_MSG(hWnd, WM_CLOSE, _this->Cls_OnClose);
		return FALSE;
	}
	return FALSE;
}
VOID Application::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	static TCHAR getTextToEditPath[MAX_PATH];
	switch (id)
	{
		case IDC_EDITPATH:
		{
			if (codeNotify == EN_CHANGE)
			{
				Edit_GetText(hEditPath, getTextToEditPath, MAX_PATH);

				if (lstrlen(getTextToEditPath) > 0)
					Button_Enable(hBtnRead, TRUE);
				else
					Button_Enable(hBtnRead, FALSE);
			}
			break;
		}
		case IDC_BUTTONREAD:
		{	
			int numbers[3];
			for (int i = 0; i < 3;i++)
			{
				numbers[i] = rand() % 87 + 1;
			}
			FILE *f;
			TCHAR buff[256] = { '\0' };

			{
				if (!_wfopen_s(&f, getTextToEditPath, TEXT("r, ccs=UTF-8")))
				{
					while (!feof(f))
					{
						fgetws(buff, 256, f);
						int num;
						TCHAR tmp[3];
						for (int i = 0; i < 2;i++)
						{
							tmp[i] = buff[i];
						}
						num = _wtoi(tmp);
						for (int i = 0; i < 3;i++)
						{
							if (numbers[i] == num)
							{
								Static_SetText(hStaticOutputs[i], buff);
							}
						}
					}
				}
				fclose(f);
			}
			{
				//MessageBox(hwnd, TEXT("Такого файла не существует"), TEXT("Warning"), MB_ICONWARNING);
			}
			break;
		}
		default:
			break;
	}
}
BOOL Application::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hEditPath = GetDlgItem(hwnd, IDC_EDITPATH);
	hBtnRead = GetDlgItem(hwnd, IDC_BUTTONREAD);
	Button_Enable(hBtnRead, FALSE);
	hStaticOutputs[0] = GetDlgItem(hwnd, IDC_STATICOUTTEXT1);
	hStaticOutputs[1] = GetDlgItem(hwnd, IDC_STATICOUTTEXT2);
	hStaticOutputs[2] = GetDlgItem(hwnd, IDC_STATICOUTTEXT3);
	Edit_SetText(hEditPath, TEXT("exameexam.txt"));
	return TRUE;
}
VOID Application::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}
Application::Application()
{
	_this = this;
}


Application::~Application()
{
	
}
