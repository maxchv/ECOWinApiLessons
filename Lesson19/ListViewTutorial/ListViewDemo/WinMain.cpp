#include "ListViewDialog.h"

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmd, int nShowOpt)
{
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	iccx.dwICC = ICC_LISTVIEW_CLASSES;
	if (!InitCommonControlsEx(&iccx)) 
	{
		MessageBox(NULL, TEXT("�� ���� ��������� ����� ListView"), TEXT(""), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	ListViewDialog *dlg = new ListViewDialog();
	INT_PTR ret =  dlg->show();
	delete dlg;
	return ret;
}