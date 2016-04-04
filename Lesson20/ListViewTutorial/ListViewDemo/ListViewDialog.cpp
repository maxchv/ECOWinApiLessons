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
	// Очищаем ресурсы
	if (hLargeIcons)
	{
		ImageList_Destroy(hLargeIcons);
	}
	if (hSmallIcons)
	{
		ImageList_Destroy(hSmallIcons);
	}

	EndDialog(hwnd, 0);
}

int ListViewDialog::Cls_OnNotify(HWND hwnd, int id, LPNMHDR lParam)
{
	switch (id)
	{
	case IDC_LIST1:
		if (lParam->code == NM_DBLCLK) // Двойной клик
		{
			// Индекс выделенного элемента
			int iSelect = ListView_GetNextItem(hListview, -1, LVNI_SELECTED);

			if (iSelect == -1)
			{
				break;
			}

			TCHAR a[5];
			_itow_s(iSelect, a, 10);
			MessageBox(hwnd, TEXT("Clicked"), a, MB_OK);
		}
		break;
	}
	return id;
}

// Изменяем стиль окна
void ListViewDialog::SetView(DWORD dwView)
{
	DWORD dwStyle = GetWindowLong(hListview, GWL_STYLE);

	if ((dwStyle & LVS_TYPEMASK) != dwView)
		SetWindowLong(hListview, GWL_STYLE, (dwStyle & ~LVS_TYPEMASK) | dwView);
}

void ListViewDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case ID_VIEW_DETAILS:
		SetView(LV_VIEW_DETAILS);
		break;
	case ID_VIEW_ICON:
		SetView(LV_VIEW_ICON);
		break;
	case ID_VIEW_LIST:
		SetView(LV_VIEW_LIST);
		break;
	case ID_VIEW_SMALLICON:
		SetView(LV_VIEW_SMALLICON);
		break;
	case ID_VIEW_TILE:
		SetView(LV_VIEW_TILE);
		break;
	case ID_FILE_QUIT:
		Cls_OnClose(hwnd);
		break;
	}
}

BOOL ListViewDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	// Получаем дискриптор Listview
	hListview = GetDlgItem(hwnd, IDC_LIST1);

	

	// Выделение всей строки
	SendMessage(hListview, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

	// Задаем колонки - только для детального вида
	LV_COLUMN lvCol = { 0 };
	lvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lvCol.cx = 80; // ширина колонки
	lvCol.pszText = TEXT("Item");
	ListView_InsertColumn(hListview, 0, &lvCol);

	// Дополнительные колонки
	lvCol.pszText = TEXT("SubItem1");
	ListView_InsertColumn(hListview, 1, &lvCol);
	lvCol.pszText = TEXT("SubItem2");
	ListView_InsertColumn(hListview, 2, &lvCol);
	lvCol.pszText = TEXT("SubItem3");
	ListView_InsertColumn(hListview, 3, &lvCol);
	lvCol.pszText = TEXT("SubItem4");
	//ListView_InsertColumn(hListview, 4, &lvCol);
	lvCol.pszText = TEXT("SubItem5");
	//ListView_InsertColumn(hListview, 5, &lvCol);

	// Создаем список изображений
	int lx = 48;//GetSystemMetrics(SM_CXICON);
	int ly = 48;//GetSystemMetrics(SM_CYICON);
	hLargeIcons = ImageList_Create(lx, ly, ILC_COLOR32 | ILC_MASK, 1, 1);

	int sx = 32;//GetSystemMetrics(SM_CXSMICON);
	int sy = 32;//GetSystemMetrics(SM_CYSMICON);
	hSmallIcons = ImageList_Create(sx, sy, ILC_COLOR32 | ILC_MASK, 1, 1);

	// список изображений
	TCHAR* icons[10] = {
		TEXT("Gear.ico"),
		TEXT("error.ico"),
		TEXT("info.ico"),
		TEXT("Likely_unavail.ico"),
		TEXT("New.ico"),
		TEXT("preferences.ico"),
		TEXT("share_overlay.ico"),
		TEXT("Shortcut.ico"),
		TEXT("UAC_shield.ico"),
		TEXT("warning.ico")
	};

	// Добавляем иконки в список
	HICON hLargeIcon, hSmallIcon;
	TCHAR path[256];
	for (int rid = 0; rid < 10; rid++)
	{
		// Загружаем и добавляем большие иконки
		lstrcpy(path, TEXT("res\\"));
		lstrcat(path, icons[rid]);

		hLargeIcon = (HICON)LoadImage(g_hInst, path,
			IMAGE_ICON, lx, ly, LR_LOADFROMFILE);
		ImageList_AddIcon(hLargeIcons, hLargeIcon);
		DestroyIcon(hLargeIcon);

		// То же для малых
		hSmallIcon = (HICON)LoadImage(g_hInst, path,
			IMAGE_ICON, sx, sy, LR_LOADFROMFILE);
		ImageList_AddIcon(hSmallIcons, hSmallIcon);
		DestroyIcon(hSmallIcon);
	}

	// Присоединяем список изображений к list view 
	ListView_SetImageList(hListview, hLargeIcons, LVSIL_NORMAL);
	ListView_SetImageList(hListview, hSmallIcons, LVSIL_SMALL);
		
	// Добавляем текст
	LVITEM lvi = { 0 };
	lvi.mask = LVIF_TEXT | LVIF_IMAGE;
	TCHAR szText[200];
	for (int i = 0; i < 10; i++)
	{
		// Основной
		lvi.iItem = i;
		lvi.iSubItem = 0;
		swprintf_s(szText, 200, TEXT("Item  %d"), i);
		lvi.pszText = szText;
		lvi.iImage = i;

		ListView_InsertItem(hListview, &lvi);

		// Вспомагательный
		for (int j = 1; j <= 3; j++)
		{
			swprintf_s(szText, 200, TEXT("SubItem %d"), j);
			lvi.pszText = szText;
			lvi.iSubItem = j;
			ListView_SetItem(hListview, &lvi);
		}
	}

	return TRUE;
}

INT_PTR CALLBACK ListViewDialog::DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hDlg, WM_CLOSE, _this->Cls_OnClose);
		HANDLE_MSG(hDlg, WM_INITDIALOG, _this->Cls_OnInitDialog);
		HANDLE_MSG(hDlg, WM_COMMAND, _this->Cls_OnCommand);
		HANDLE_MSG(hDlg, WM_NOTIFY, _this->Cls_OnNotify);
	}
	return FALSE;
}

INT_PTR ListViewDialog::show()
{
	return DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_LVDIALOG), NULL, DlgProc);
}
