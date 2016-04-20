#include "MainDlg.h"

MainDlg* MainDlg::this_ = NULL;

MainDlg::MainDlg()
{
	this_ = this;	
}

BOOL MainDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hEditPath		= GetDlgItem(hwnd, IDC_EDIT_PATH);
	hStaticString1	= GetDlgItem(hwnd, IDC_STATIC_STRING1);
	hStaticString2	= GetDlgItem(hwnd, IDC_STATIC_STRING2);
	hStaticString3	= GetDlgItem(hwnd, IDC_STATIC_STRING3);	

	return BOOL(TRUE);
}

INT_PTR MainDlg::DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hwnd, WM_INITDIALOG, this_->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, this_->Cls_OnCommand);		
		HANDLE_MSG(hwnd, WM_CLOSE, this_->Cls_OnClose);
	}

	return INT_PTR(FALSE);
}

void MainDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_BTN_RAND:
	{
		TCHAR pathToFile[MAX_PATH * 2] = { 0 };
		Edit_GetText(hEditPath, pathToFile, MAX_PATH * 2);

		if (pathToFile[0] == '\0')
		{
			MessageBox(hwnd, TEXT("Вы не указали путь к файлу"), TEXT("Не все поля заполнены"), MB_OK | MB_ICONWARNING);
		}
		else 
		{		
			srand(static_cast<unsigned int>(time(0)));
			int randNum[3] = { 0 };
			
			do 
			{
				randNum[0] = rand() % GetNumberLinesInFile(pathToFile);
				randNum[1] = rand() % GetNumberLinesInFile(pathToFile);
				randNum[2] = rand() % GetNumberLinesInFile(pathToFile);
			} while (randNum[0] == 0 && randNum[1] == 0 && randNum[2] == 0 && randNum[0] == randNum[1] && randNum[0] == randNum[2] && randNum[1] == randNum[2]);
			
			TCHAR str[MAX_PATH * 2] = { '\0' };
			int i = 0;
			int nStr = 1;			
			FILE *in;
			
			if (_wfopen_s(&in, pathToFile, TEXT("r, ccs=UTF-8")))
			{
				MessageBox(hwnd, TEXT("Вы указали неверный путь или имя файла"), TEXT("Ошибка"), MB_OK | MB_ICONWARNING);
			}
			else		
			{
				while (!feof(in))
				{
					i++;
					fgetws(str, MAX_PATH * 2, in);

					if (i == randNum[0] || i == randNum[1] || i == randNum[2])
					{						
						if (nStr == 1)
						{
							SetWindowText(hStaticString1, str);
							nStr++;
						}
						else if (nStr == 2)
						{
							SetWindowText(hStaticString2, str);
							nStr++;
						}
						else if (nStr == 3)
						{
							SetWindowText(hStaticString3, str);							
						}
					}
				}
			}			
		}
	}
	break;	
	default:
		break;
	}
}

void MainDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

int MainDlg::GetNumberLinesInFile(TCHAR path[MAX_PATH * 2])
{
	std::ifstream base(path);

	if (base)
	{
		char *str = new char[1024];
		int i = 0;

		while (!base.eof())
		{
			base.getline(str, 1024, '\n');
			i++;
		}
		
		base.close();
		delete str;
		
		return i;
	}

	return 10;
}

MainDlg::~MainDlg()
{
	
}