#include "ParentProcessDlg.h"

ParentProcessDlg* ParentProcessDlg::ptr = NULL;

ParentProcessDlg::ParentProcessDlg(void)
{
	ptr = this;
}

ParentProcessDlg::~ParentProcessDlg(void)
{
	
}

void ParentProcessDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

void MessageAboutError(DWORD dwError)
{
	LPVOID lpMsgBuf = NULL;
	TCHAR szBuf[300]; 

	BOOL fOK = FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	if(lpMsgBuf != NULL)
	{
		wsprintf(szBuf, TEXT("Ошибка %d: %s"), dwError, lpMsgBuf); 
		MessageBox(0, szBuf, TEXT("Сообщение об ошибке"), MB_OK | MB_ICONSTOP); 
		LocalFree(lpMsgBuf);
	}
}

void ParentProcessDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(IDC_BUTTON1 == id)
	{
		CreateMutex(0, FALSE, TEXT("[Guid('9188D5A7-3C47- 48E1-A7B0-9866BB418678')]"));
		STARTUPINFO st = {sizeof(st)};
		PROCESS_INFORMATION pr;
		static TCHAR filename[20];
		wsprintf(filename, TEXT("%s"), TEXT("04.CodingThread.exe"));
		if (!CreateProcess(NULL, filename, NULL, NULL, 0, 0, NULL, NULL, &st, &pr))
		{
			MessageAboutError(GetLastError());
			return;
		}
		CloseHandle(pr.hThread);
		CloseHandle(pr.hProcess);
		ZeroMemory(&st,sizeof(st));
		st.cb = sizeof(st);
		wsprintf(filename, TEXT("%s"), TEXT("05.DecodingThread.exe"));
		if (!CreateProcess(NULL, filename, NULL, NULL, 0, 0, NULL, NULL, &st, &pr))
		{
			MessageAboutError(GetLastError());
			return;
		}
		CloseHandle(pr.hThread);
		CloseHandle(pr.hProcess);	
	}
}

BOOL CALLBACK ParentProcessDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}