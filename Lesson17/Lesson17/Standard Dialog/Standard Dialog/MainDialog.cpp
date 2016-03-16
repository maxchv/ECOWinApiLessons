#include "MainDialog.h"

// ������������� ������������������� ��������� FINDMSGSTRING
UINT WM_FR = RegisterWindowMessage(FINDMSGSTRING);

CMainDialog* CMainDialog::ptr = NULL;

CMainDialog::CMainDialog(void)
{
	ptr = this;
	hFR = NULL;
	ZeroMemory(&fr, sizeof(fr));
}

CMainDialog::~CMainDialog(void){}

void CMainDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL CMainDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hDialog = hwnd;
	hEdit = GetDlgItem(hwnd, IDC_EDIT1);
	return TRUE;
}

void CMainDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_FIND)
		OnFind();
	else if(id == IDC_REPLACE)
		OnReplace();
}

void CMainDialog::OnFind()
{
	// ��������, ������� �� ���� ������
	if(hFR)
	{
		//������������ ���� ������
		SetForegroundWindow(hFR);
		return;
	}
	// �������� ��������� FINDREPLACE
	ZeroMemory(&fr, sizeof(fr));
	DWORD start, end;
	// ������� ���� �����, ����������� � ��������� ���� �����
	
	GetWindowText(hEdit, alltext, 65536);
	// ������� ������� ��������� ��������� ������
	SendMessage(hEdit, EM_GETSEL, WPARAM(&start), LPARAM(&end));
	// ��������� � ����� ���������� �������� ������
	_tcsncpy(bufFind, alltext+start, end-start);
	bufFind[end - start] = TEXT('\0');
	fr.lStructSize = sizeof(fr);
	// ������� ������ �������� �����-����������
	fr.hwndOwner = hDialog;
	// ��������� �� �����, ���������� ������ ��� ������
	fr.lpstrFindWhat = bufFind; 
	fr.wFindWhatLen = 100; 
	// ����� �� �������� ��������� ������� � ������ �� ����� ���������
	fr.Flags = FR_DOWN;
	// ���������� ������ �����
	hFR = FindText(&fr);
}

void CMainDialog::OnReplace()
{
	// ��������, ������� �� ���� ������
	if(hFR)
	{
		// ������������ ���� ������
		SetForegroundWindow(hFR);
		return;
	}
	// �������� ��������� FINDREPLACE
	ZeroMemory(&fr, sizeof(fr));
	DWORD start, end;
	// �������� �����, ��������������� ��� �������� ���������� ������ 
	ZeroMemory(&bufReplace, sizeof(bufReplace));
	// ������� ���� �����, ����������� � ��������� ���� �����
	GetWindowText(hEdit, alltext, 65536);
	// ������� ������� ��������� ��������� ������
	SendMessage(hEdit, EM_GETSEL, WPARAM(&start), LPARAM(&end));
	// ��������� � ����� ���������� �������� ������
	_tcsncpy(bufFind, alltext + start, end - start);
	bufFind[end - start] = TEXT('\0');
	fr.lStructSize = sizeof(fr);
	// ������� ������ �������� �����-����������
	fr.hwndOwner = hDialog;
	// ��������� �� �����, ���������� ������ ��� ������
	fr.lpstrFindWhat = bufFind;
	fr.wFindWhatLen = 100; 
	// ��������� �� �����, ���������� ������ ��� ������
	fr.lpstrReplaceWith = bufReplace;
	fr.wReplaceWithLen = 100;
	// ����� �� �������� ��������� ������� � ������ �� ����� ���������
	fr.Flags = FR_DOWN;
	// ���������� ������ ��������
	hFR = ReplaceText(&fr);
}

void CMainDialog::MessageFromFindReplace()
{
	if(fr.Flags & FR_REPLACEALL) 
		MessageBox(hDialog, TEXT("������ ������ \"�������� ��\""), TEXT("����� � ������"), MB_OK | MB_ICONINFORMATION);

	if(fr.Flags & FR_REPLACE)
	{
		MessageBox(hDialog, TEXT("������ ������ \"��������\""), TEXT("����� � ������"), MB_OK | MB_ICONINFORMATION);
		// �������� ���������� �������� ������ �� ������, ����������� � ������ bufReplace
		SendMessage(hEdit, EM_REPLACESEL, WPARAM(TRUE),(LPARAM)bufReplace);
	}

	if(fr.Flags & FR_FINDNEXT)
	{
		MessageBox(hDialog, TEXT("������ ������ \"����� �����\""), TEXT("����� � ������"), MB_OK | MB_ICONINFORMATION);
		DWORD Start, End;
		// ��������� ����� ������� ������
		TCHAR * p = _tcsstr(alltext, bufFind);
		if(p)
		{
			Start = p - alltext;
			End = Start + _tcslen(bufFind);
			// �������� ��������� ������
			SendMessage(hEdit, EM_SETSEL, Start, End); 
		}
	}

	if(fr.Flags&FR_DIALOGTERM)
	{
		hFR = NULL;
		MessageBox(hDialog, TEXT("����������� ������ ������ � ������!"), TEXT("����� � ������"), MB_OK | MB_ICONINFORMATION);
		return;
	}

	if(fr.Flags & FR_MATCHCASE)
		MessageBox(hDialog, TEXT("���������� ������ �������������������"), TEXT("����� � ������"), MB_OK | MB_ICONINFORMATION);

	if(fr.Flags & FR_WHOLEWORD)
		MessageBox(hDialog, TEXT("���������� ������ ������ ����� �������"), TEXT("����� � ������"), MB_OK | MB_ICONINFORMATION);

	if(fr.Flags & FR_DOWN)
		MessageBox(hDialog, TEXT("������ ����� ������ � ����������� ����"), TEXT("����� � ������"), MB_OK | MB_ICONINFORMATION);
	else
		MessageBox(hDialog, TEXT("������ ����� ������ � ����������� �����"), TEXT("����� � ������"), MB_OK | MB_ICONINFORMATION);
	
}


BOOL CALLBACK CMainDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	// ��������� ���������, ���������� �� ������������ ����������� ����
	if(message == WM_FR)
		ptr->MessageFromFindReplace();
	return FALSE;
}
