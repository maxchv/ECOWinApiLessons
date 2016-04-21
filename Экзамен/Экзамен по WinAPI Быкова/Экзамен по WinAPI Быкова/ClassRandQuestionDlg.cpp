#include "ClassRandQuestionDlg.h"

RandQuestionDlg* RandQuestionDlg::_this = NULL;
DWORD dwFlag = WS_CHILD | WS_VISIBLE | WS_BORDER;
RandQuestionDlg::RandQuestionDlg()
{
	_this = this;
}

RandQuestionDlg::~RandQuestionDlg()
{
	
}


void RandQuestionDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL RandQuestionDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hInst = GetModuleHandle(0);
	hParent = hwnd;

	hStaticResult = GetDlgItem(hParent, IDC_STATIC_RESULT);
	hEditWay = GetDlgItem(hParent, IDC_EDIT_WAY_FILE);
	SetWindowText(hEditWay, TEXT("Вопросы на экзамен.txt"));

	return TRUE;
}

DWORD RandQuestionDlg::Thread(LPVOID lp)
{
	return 0;
}

void RandQuestionDlg::OpenFileQuestions()
{
	FILE* f;
	TCHAR buff[256] = { '\0' };
	
	BOOL isNum;
	int num;
	int idx = 0;
	int i = 0;
	if (!_wfopen_s(&f, filename, TEXT("r, ccs=UTF-8")))
	{
		while (!feof(f))
		{
			i = 0;
			std::wstringstream sstr;
			sstr.str(TEXT(""));
			fgetws(buff, 256, f);
			i = 0;

			while (buff[i] != TEXT('.'))
			{
				sstr << buff[i];
				i++;
			}
			num = _wtoi(sstr.str().c_str());
			if (num == rand_num[0] || num == rand_num[1] || num == rand_num[2])
			{
				_sstr << buff;
				idx++;
			}
			sstr.clear();
		}
	}
	fclose(f);
}

void RandQuestionDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_BTN_START:
	{
		_sstr.str(TEXT(""));
		Edit_GetText(hEditWay, filename, 256);
		
		for (int i = 0; i < 3; i++)
		{
			rand_num[i] = rand() % 87 + 1;
		}
		for (int i = 0; i < 2; i++)
		{
			if (rand_num[i] == rand_num[i + 1])
			{
				rand_num[i] = rand() % 87 + 1;
			}
		}
		OpenFileQuestions();

		SetWindowText(hStaticResult, _sstr.str().c_str());

		_sstr.clear();
	}
		break;
	case IDC_BTN_EXIT:
	{
		Cls_OnClose(hwnd);
	}
	break;
	}
}



BOOL CALLBACK RandQuestionDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, _this->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, _this->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, _this->Cls_OnCommand);
	}
	return FALSE;
}