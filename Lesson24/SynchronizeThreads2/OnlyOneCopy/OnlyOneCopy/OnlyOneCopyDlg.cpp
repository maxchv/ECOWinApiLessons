#include "OnlyOneCopyDlg.h"

OnlyOneCopyDlg* OnlyOneCopyDlg::ptr = NULL;

OnlyOneCopyDlg::OnlyOneCopyDlg(void)
{
	ptr = this;
}

OnlyOneCopyDlg::~OnlyOneCopyDlg(void)
{
	ReleaseMutex(hMutex);
}

void OnlyOneCopyDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL OnlyOneCopyDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	TCHAR GUID[] = TEXT("{CA168952-383A-4DBA-BBE4-197708D9513F}");
	hMutex = CreateMutex(NULL, FALSE, GUID);
	DWORD dwAnswer = WaitForSingleObject(hMutex, 0);
	if (dwAnswer == WAIT_TIMEOUT)
	{
		MessageBox(hwnd, TEXT("Нельзя запускать более одной копии приложения!!!"), TEXT("Мьютекс"), MB_OK | MB_ICONINFORMATION);
		EndDialog(hwnd, 0);
	}
	return TRUE;
}

void OnlyOneCopyDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDOK || id == IDCANCEL)
		EndDialog(hwnd, 0);
}

BOOL CALLBACK OnlyOneCopyDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}