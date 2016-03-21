#include "MainDialog.h"

// ����������� ��������� ��� ����������� ���� FindText and ReplaceText
UINT WM_FINDREPLACE = RegisterWindowMessage(FINDMSGSTRING);

MainDialog* MainDialog::_this = NULL;

// ������������� ��������� ����� �������/�������
void MainDialog::InitFindReplace()
{
	// ��������� ���������
	ZeroMemory(&fr, sizeof(fr));

	fr.hInstance = GetModuleHandle(0);
	fr.hwndOwner = hDialog;

	// ���� ��������� ����� � EDIT
	GetWindowText(hEdit, alltext, TEXTLENGTH);
	DWORD start, end;
	// �������� ������� ����������� ������ � EDITe
	SendMessage(hEdit, EM_GETSEL, WPARAM(&start), LPARAM(&end));
	// �������� ����� � �����
	_tcsncpy(bufFind, alltext + start, end - start);
	bufFind[end - start] = TEXT('\0');
	// ������ ��� ������
	fr.lpstrFindWhat = bufFind;

	fr.wFindWhatLen = FINDTEXTLENTH;
	fr.lStructSize = sizeof(FINDREPLACE);

	fr.Flags = FR_DOWN;
}

MainDialog::MainDialog(void)
{
	_this = this;
	hFindReplace = NULL;	
	ZeroMemory(&fr, sizeof(fr));
}

MainDialog::~MainDialog(void){}

void MainDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL MainDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hDialog = hwnd;
	hEdit = GetDlgItem(hwnd, IDC_EDIT1);
	SetWindowText(hEdit, TEXT("� ��� �� ��������� ������?\r\n� Job\r\n � � ��������?\r\n� �job�����"));

	hStatus = CreateStatusWindow(WS_VISIBLE | WS_CHILD | CCS_BOTTOM, TEXT(""), hwnd, WM_USER);
	RECT r = { 0 };
	GetClientRect(hwnd, &r);
	int half = r.right / 2;
	int parts[4] = { half / 2, half, half * 2 / 3, -1 };
	SendMessage(hStatus, SB_SETPARTS, 4, LPARAM(parts));
	SendMessage(hStatus, SB_SETTEXT, 0, LPARAM(TEXT("Down")));
	SendMessage(hStatus, SB_SETTEXT, 1, LPARAM(TEXT(" ")));
	SendMessage(hStatus, SB_SETTEXT, 2, LPARAM(TEXT(" ")));

	return TRUE;
}

void MainDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_FIND:
		OnFind(); // ������ ������ �����
		break;
	case IDC_REPLACE:
		OnReplace(); // ������ ������ ��������
		break;	
	case IDC_BUTTON3:
		Edit_SetSel(hEdit, 0, 10);
		Edit_ReplaceSel(hEdit, TEXT("test"));
		break;
	}
}

void MainDialog::OnFind()
{
	if (hFindReplace) // ���� ���� ������������
	{
		SetForegroundWindow(hFindReplace);
	}
	else // ������� ����
	{
		InitFindReplace();
		hFindReplace = FindText(&fr);
	}
}

void MainDialog::OnReplace()
{
	if (hFindReplace) // ���� ���� ������������
	{
		SetForegroundWindow(hFindReplace);
	}
	else // ������� ����
	{
		InitFindReplace();
		ZeroMemory(bufReplace, FINDTEXTLENTH);
		fr.lpstrReplaceWith = bufReplace;
		fr.wReplaceWithLen = FINDTEXTLENTH;
		hFindReplace = ReplaceText(&fr);
	}
}

void MainDialog::MessageFromFindReplace()
{
	if (fr.Flags & FR_DOWN) {
		SendMessage(hStatus, SB_SETTEXT, 0, LPARAM(TEXT("Down")));
	}
	else 
	{
		SendMessage(hStatus, SB_SETTEXT, 0, LPARAM(TEXT("Up")));
	}

	if (fr.Flags & FR_FINDNEXT) {
		SendMessage(hStatus, SB_SETTEXT, 1, LPARAM(TEXT("FindNext")));
		GetWindowText(hEdit, alltext, TEXTLENGTH);

		DWORD selStart, selEnd;
		SendMessage(hEdit, EM_GETSEL, WPARAM(&selStart), LPARAM(&selEnd));

		TCHAR * searchStart = alltext;// +selEnd;

		TCHAR *start_word = _tcsstr(searchStart, bufFind); // ����� ������
		int len = lstrlen(bufFind);  // ����� �������� �����
		DWORD start_idx, end_idx;   
		start_idx = start_word - alltext; // ������ ����� � ������ alltext
		end_idx = start_idx + len;
		SendMessage(hEdit, EM_SETSEL, start_idx, end_idx);
		//Edit_ReplaceSel(hEdit, TEXT("test"));
	}

	if (fr.Flags & FR_REPLACE) 
	{
		SendMessage(hStatus, SB_SETTEXT, 1, LPARAM(bufReplace));
		
		SendMessage(hEdit, EM_REPLACESEL, TRUE, LPARAM(bufReplace));
	}

	if (fr.Flags & FR_MATCHCASE) {
		SendMessage(hStatus, SB_SETTEXT, 2, LPARAM(TEXT("MatchCase")));
	}

	if (fr.Flags & FR_WHOLEWORD) {
		SendMessage(hStatus, SB_SETTEXT, 3, LPARAM(TEXT("WholeWord")));
	}

	if (fr.Flags & FR_DIALOGTERM)
	{
		hFindReplace = NULL;
	}
}


BOOL CALLBACK MainDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, _this->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, _this->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, _this->Cls_OnCommand);
	}
	
	if (WM_FINDREPLACE) 
	{
		// ���� ���-�� ��������� � �������������� ����, �� 
		// � �������� ���� �������� ������������������ 
		// ��������� WM_FINDREPLACE
		_this->MessageFromFindReplace();
	}

	return FALSE;
}
