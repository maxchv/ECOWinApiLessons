#include "Generate_Text.h"

Generate_Text* Generate_Text::ptr = NULL;

CRITICAL_SECTION cs;

Generate_Text::Generate_Text(void)
{
	ptr = this;
}

Generate_Text::~Generate_Text(void)
{
	DeleteCriticalSection(&cs);
}

void Generate_Text::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL Generate_Text::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hEdit_1 = GetDlgItem(hwnd, IDC_EDIT2);
	hEdit_2 = GetDlgItem(hwnd, IDC_EDIT3);
	hEdit_3 = GetDlgItem(hwnd, IDC_EDIT5);
	hBTNGenerate = GetDlgItem(hwnd, IDC_BTN_GEN);
	hBTNStart = GetDlgItem(hwnd, IDC_BTN_OPEN);
	hEdit_Path = GetDlgItem(hwnd, IDC_EDIT_PATH);
	/*hEdit_Get_text = GetDlgItem(hwnd, IDC_EDIT_GET_TEXT);*/
	hStatic = GetDlgItem(hwnd, IDC_STATIC_TEXT);
	SetWindowText(hEdit_Path, TEXT("Вопросы на экзамен.txt"));
	
	InitializeCriticalSection(&cs);
	return TRUE;
}

void Generate_Text::Read(HWND hwnd)
{
	
	FILE* f;
	TCHAR buffFile[256] = { '\0' };
	TCHAR buffCopy[100];
	INT num;
	int i;
	BOOL isText;
	int idx = 0;
	
	TCHAR filename[256] = TEXT("Вопросы на экзамен.txt");
	//EnterCriticalSection(&cs);
	if (!_wfopen_s(&f, filename, TEXT("r, ccs=UTF-8")))
	{
 		while (!feof(f))
		{
			i = 0;
			isText = FALSE;
			std::wstringstream sstr;
			sstr.str(TEXT(""));
			fgetws(buffFile, 256, f);

			while (buffFile[i] != TEXT('.'))
			{
				sstr << buffFile[i];
				i++;
			}
			num = _wtoi(sstr.str().c_str());
			if (num == num_rand[0] || num == num_rand[1] || num == num_rand[2])
			{
				wstringstream ss;
				ss << buffFile << endl;
				SetWindowText(hStatic, ss.str().c_str());
			}
			sstr.clear();
		}
	}
	fclose(f);
	//LeaveCriticalSection(&cs);
}
DWORD WINAPI Thread(LPVOID lP)
{
	char buff[8];
	TCHAR buffFile[100], buffCopy[100];
	std::ifstream in(buffFile, std::ios::binary);
	if (in.is_open())
	{
		in.read(reinterpret_cast<char *>(&buff), 8);
	}

	std::ofstream out(buffCopy, std::ios::binary); //ios::out | ios::trunc 
	if (out.is_open())
	{

		out.write(reinterpret_cast<char *>(&buff), 8);
		out.close();
	}

	return 0;
}
void Generate_Text::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_BTN_GEN)
	{

		
		Edit_GetText(hStatic, buffFile, 256);
		
		for (int i = 0; i < 3; i++)
		{
			num_rand[i] = rand() % 87 + 1;
		}
		Read(hwnd);
		
		_sstr.str(TEXT(""));
		_sstr.clear();
	}
}

BOOL CALLBACK Generate_Text::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}


