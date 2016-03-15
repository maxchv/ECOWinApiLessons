#include "MainDialog.h"

CMainDialog* CMainDialog::ptr = NULL;

CMainDialog::CMainDialog()
{
	ptr = this;
}

CMainDialog::~CMainDialog()
{

}

void CMainDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

void CMainDialog::COpenFile(HWND hwnd)
{
	OPENFILENAME ofn = { 0 };

	TCHAR buf[MAX_PATH];// = TEXT("filename");
	buf[0] = '\0';

	ofn.hInstance = GetModuleHandle(0);
	ofn.hwndOwner = hwnd;
	ofn.Flags = OFN_FILEMUSTEXIST;
	ofn.lpstrDefExt = TEXT("txt");
	ofn.lpstrFile = buf;
	ofn.lpstrFilter = TEXT("All files (*.*)\0*.*\0Text files (*.txt)\0*.txt\0");
	ofn.lpstrInitialDir = TEXT("d:\\");
	ofn.lpstrTitle = TEXT("Open my file");
	ofn.lStructSize = sizeof(OPENFILENAME);

	ofn.nFilterIndex = 1;
	ofn.nMaxFile = MAX_PATH;

	if (GetOpenFileName(&ofn))
	{
		//MessageBox(hwnd, buf, TEXT("־עךûנעü פאיכ"), 0);
		FILE* f;
		TCHAR buff[256] = { '\0' };
		if (!_wfopen_s(&f, buf, TEXT("r, ccs=UTF-8")))
		{				
			while (!feof(f))
			{
				fgetws(buff, 256, f);	
				lstrcat(buff, TEXT("\r\n"));
				int pos = SendDlgItemMessage(hwnd, IDC_EDIT1, WM_GETTEXTLENGTH, NULL, NULL);
				SendDlgItemMessage(hwnd, IDC_EDIT1, EM_SETSEL, pos, pos);
				SendDlgItemMessage(hwnd, IDC_EDIT1, EM_REPLACESEL, NULL, LPARAM(buff));
			}			
		}
		fclose(f);
	}
}

void CMainDialog::CWriteFile(HWND hwnd)
{
	OPENFILENAME ofn = { 0 };

	TCHAR filename[MAX_PATH] = TEXT("filename");	

	ofn.hInstance = GetModuleHandle(0);
	ofn.hwndOwner = hwnd;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = TEXT("txt");
	ofn.lpstrFile = filename;
	ofn.lpstrFilter = TEXT("All files (*.*)\0*.*\0Text files (*.txt)\0*.txt\0");
	ofn.lpstrInitialDir = TEXT("d:\\");
	ofn.lpstrTitle = TEXT("Save my file");
	ofn.lStructSize = sizeof(OPENFILENAME);

	ofn.nFilterIndex = 1;
	ofn.nMaxFile = MAX_PATH;

	if (GetSaveFileName(&ofn))
	{		
		FILE* f;
		TCHAR text[256];
		SendDlgItemMessage(hwnd, IDC_EDIT1, WM_GETTEXT, 256, LPARAM(text));
		if (!_wfopen_s(&f, filename, TEXT("w, ccs=UTF-8")))
		{
			_fwprintf_p(f, text);
		}
		fclose(f);
	}
}

void CMainDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{		
		case ID_FILE_OPEN40001:		
		{
			COpenFile(hwnd);
		}
			break;
		case ID_FILE_SAVE40002:	
			break;
		case ID_FILE_SAVE40003:
			CWriteFile(hwnd);
			break;
		case ID_FILE_EXIT:
			EndDialog(hwnd, IDOK);
			break;
	}
}

BOOL CALLBACK CMainDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
