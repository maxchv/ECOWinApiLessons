#include "DecodingThreadDlg.h"

DecodingThreadDlg* DecodingThreadDlg::ptr = NULL;

DecodingThreadDlg::DecodingThreadDlg(void)
{
	ptr = this;
}

DecodingThreadDlg::~DecodingThreadDlg(void)
{
	
}

void DecodingThreadDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

DWORD WINAPI Decoding_Thread(LPVOID lp)
{
	DecodingThreadDlg *ptr = (DecodingThreadDlg *)lp;
	char buf[4096];
	TCHAR str[MAX_PATH];
	_tcscpy(str, GetCommandLine());
	TCHAR seps[] = TEXT(" ");
	TCHAR *token, *last;
	token = _tcstok(str, seps); 
	while(token != NULL)
	{
		token = _tcstok(NULL, seps);
		if(token)
			last = token;
	}
	wsprintf(str, TEXT("copymusic_%s.txt"), last);
	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, false, TEXT("{2525FD5F-12E6-47c0-838A-7C5CA1EBD169}"));
	DWORD dwAnswer = WaitForSingleObject(hSemaphore, INFINITE);
	if(dwAnswer == WAIT_OBJECT_0)
	{
		ifstream in(TEXT("coding.txt"), ios::binary | ios::in);
		if(!in)
		{
			MessageBox(ptr->hDialog, TEXT("Ошибка открытия файла!"), TEXT("Семафор"), MB_OK | MB_ICONINFORMATION);
			return 1;
		}
		ofstream out(str, ios::binary | ios::out | ios::trunc);
		const int KEY = 100;
		while(!in.eof())
		{
			in.read(buf, 4096);
			int n = in.gcount();
			for(int i = 0; i < n; i++)
			{
				buf[i] ^= KEY;
			}
			out.write(buf, n);
		}
		out.close();
		in.close();
		ReleaseSemaphore(hSemaphore, 1, NULL);
		MessageBox(ptr->hDialog, TEXT("Чтение данных из файла coding.txt завершено!"), TEXT("Семафор"), MB_OK | MB_ICONINFORMATION);
	}
	return 0;
}

BOOL DecodingThreadDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hDialog = hwnd;
	CreateThread(NULL, 0, Decoding_Thread, this, 0, NULL); 
	return TRUE;
}

BOOL CALLBACK DecodingThreadDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
	}
	return FALSE;
}