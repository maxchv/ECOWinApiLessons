#include "ListViewDialog.h"

ListViewDialog* ListViewDialog::_this = NULL;

ListViewDialog::ListViewDialog()
{
	_this = this;
	g_hInst = GetModuleHandle(0);
}


ListViewDialog::~ListViewDialog()
{

}

void ListViewDialog::Cls_OnClose(HWND hwnd)
{
	// Destroy the image lists
	ImageList_Destroy(lvh->hLargeIcons);
	ImageList_Destroy(lvh->hSmallIcons);
	delete lvh;

	EndDialog(hwnd, 0);
}

void ListViewDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{

}

BOOL ListViewDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	// Create storage for struct to contain information about the listview 
	// (window and image list handles).
	lvh = new LVHandles();

	// Create the Listview control
	/*RECT rc;
	GetClientRect(hWnd, &rc);
	lvh->hListview = CreateWindowEx(0, WC_LISTVIEW, 0,
		LVS_ICON | WS_CHILD | WS_VISIBLE,
		rc.left, rc.top, rc.right, rc.bottom,
		hWnd, (HMENU)IDC_LISTVIEW, g_hInst, 0);*/

	// Create the image lists
	int lx = GetSystemMetrics(SM_CXICON);
	int ly = GetSystemMetrics(SM_CYICON);
	lvh->hLargeIcons = ImageList_Create(lx, ly, ILC_COLOR32 | ILC_MASK, 1, 1);
	
	int sx = GetSystemMetrics(SM_CXSMICON);
	int sy = GetSystemMetrics(SM_CYSMICON);
	lvh->hSmallIcons = ImageList_Create(sx, sy, ILC_COLOR32 | ILC_MASK, 1, 1);

	// Add icons to image lists
	HICON hLargeIcon, hSmallIcon;
	for (int rid = IDI_ICON1; rid <= IDI_ICON10; rid++)
	{
		// Load and add the large icon
		hLargeIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(rid),
			IMAGE_ICON, lx, ly, 0);
		ImageList_AddIcon(lvh->hLargeIcons, hLargeIcon);
		DestroyIcon(hLargeIcon);

		// Load and add the small icon
		hSmallIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(rid),
			IMAGE_ICON, sx, sy, 0);
		ImageList_AddIcon(lvh->hSmallIcons, hSmallIcon);
		DestroyIcon(hSmallIcon);
	}

	// Attach image lists to list view common control
	ListView_SetImageList(lvh->hListview, lvh->hLargeIcons, LVSIL_NORMAL);
	ListView_SetImageList(lvh->hListview, lvh->hSmallIcons, LVSIL_SMALL);


	/////////////////////////////////////////////////////////////////////////
	// Add items to the the list view common control.
	// 

	LVITEM lvi = { 0 };
	lvi.mask = LVIF_TEXT | LVIF_IMAGE;
	TCHAR szText[200];
	for (int i = 0; i < 10; i++)
	{
		lvi.iItem = i;
		swprintf_s(szText, 200, L"Item  %d", i);
		lvi.pszText = szText;
		lvi.iImage = i;

		SendMessage(lvh->hListview, LVM_INSERTITEM, 0, (LPARAM)&lvi);
	}

	return TRUE;
}

INT_PTR CALLBACK ListViewDialog::DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hDlg, WM_CLOSE, ListViewDialog::_this->Cls_OnClose);
	}
	return FALSE;
}


INT_PTR ListViewDialog::show()
{
	return DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_LVDIALOG), NULL, DlgProc);
}
