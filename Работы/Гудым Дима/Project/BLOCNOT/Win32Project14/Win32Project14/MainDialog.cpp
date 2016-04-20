#include "Header.h"
#pragma comment(lib, "comctl32")

CMainDialog* CMainDialog::ptr = NULL;
UINT WM_FINDREPLACE = RegisterWindowMessage(FINDMSGSTRING);

CMainDialog::CMainDialog()
{
	ptr = this;
	hFindReplace = NULL;
	ZeroMemory(&fr, sizeof(fr));
	lFont = { 0 };
}

HWND hStatus;
HWND hPictureBox;
HBITMAP hImage;

BOOL CMainDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	HMENU hMenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));
	SetMenu(hwnd, hMenu);

	hStatus = CreateStatusWindow(WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP | SBARS_TOOLTIPS, TEXT("Ready"), hwnd, IDC_STATUSBAR);

	//HMENU hEdit = GetSubMenu(hMenu, 1);
	//EnableMenuItem(hEdit, 0, MF_BYPOSITION | MF_GRAYED);

	DrawMenuBar(hwnd);

	// создаем окно панели инструментов
	/*hToolbar = CreateWindow(TOOLBARCLASSNAME,
		NULL,
		TBSTYLE_FLAT | CCS_TOP | CCS_NODIVIDER | WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0,
		hwnd,
		(HMENU)IDC_TOOLBAR,
		GetModuleHandle(0),
		NULL);
	// использовать структуру TBBUTTON для хранения данных кнопок панели инструментов
	SendMessage(hToolbar, TB_BUTTONSTRUCTSIZE, WPARAM(sizeof(TBBUTTON)), 0);

	// Создание и настройка структуры для панели управления
	// Указать исочник изображений для панели управления
	TBADDBITMAP tbAddBmp = { 0 };
	tbAddBmp.hInst = HINST_COMMCTRL;// HINST_COMMCTRL - стандартные изображения;
									// GetModuleHandle(0) - Не стандартные
	tbAddBmp.nID = IDB_STD_SMALL_COLOR;// IDB_STD_SMALL_COLOR - стандартные;
								// IDR_TOOLBAR2 - Не стандартные;
	SendMessage(hToolbar, TB_ADDBITMAP, 0, (LPARAM)&tbAddBmp);
	SendMessage(hToolbar, TB_SETBITMAPSIZE, 0, (LPARAM)MAKELONG(16, 16));

	// Заполнение панели данными
	TBBUTTON buttons[] = {

		{STD_FILEOPEN, ID_FILE_OPEN, TBSTATE_ENABLED, BTNS_AUTOSIZE,{ 0 }, 0, (INT_PTR)TEXT("Open") },

		{STD_FILESAVE, ID_FILE_SAVEAS, TBSTATE_ENABLED, BTNS_AUTOSIZE,{ 0 }, 0, (INT_PTR)TEXT("Save...") },

		Не стандартные
		{ 0, ID_FILE_CREATE, TBSTATE_ENABLED, BTNS_AUTOSIZE,{ 0 }, 0, (INT_PTR)TEXT("New") },
		{ 1, ID_FILE_OPEN, TBSTATE_ENABLED, BTNS_AUTOSIZE,{ 0 }, 0, (INT_PTR)TEXT("Open") },
		{ 2, ID_FILE_SAVE, TBSTATE_ENABLED, BTNS_AUTOSIZE,{ 0 }, 0, (INT_PTR)TEXT("Save") },
		{ 3, ID_FILE_COPY, TBSTATE_ENABLED, BTNS_AUTOSIZE,{ 0 }, 0, (INT_PTR)TEXT("Copy") },
		{ 4, ID_FILE_CUT, TBSTATE_ENABLED, BTNS_AUTOSIZE,{ 0 }, 0, (INT_PTR)TEXT("Cut") },
		{ 5, ID_FILE_PASTE, TBSTATE_ENABLED, BTNS_AUTOSIZE,{ 0 }, 0, (INT_PTR)TEXT("Paste") }

	};*/

	hEdit = GetDlgItem(hwnd, IDC_EDIT1);

	//int nButtons = sizeof(buttons) / sizeof(buttons[0]);
	// Установка панели
	//SendMessage(hToolbar, TB_ADDBUTTONS, nButtons, (LPARAM)buttons);

	// Подбор размера панели под размер окна
	SendMessage(hToolbar, TB_AUTOSIZE, 0, 0);

	for (int i = 0, id = 115, idButton = 1003; i < 4; i++, id++, idButton++)
	{
		hPictureBox = GetDlgItem(hwnd, idButton);
		
		hImage = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(id));

		if (hImage)
		{
			SendMessage(hPictureBox, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
		}
		else
		{
			MessageBox(hwnd, TEXT("Image not found"), TEXT("Error"), MB_OK | MB_ICONERROR);
		}
	}
	return FALSE;

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
	ofn.lpstrFilter = TEXT("All files (*.*)\0*.*\0Text files (*.txt)\0*.txt\0BMP Files (*.bmp)\0*.bmp\0PNG Files (*.png)\0*.png\0");
	ofn.lpstrInitialDir = TEXT("d:\\");
	ofn.lpstrTitle = TEXT("Open my file");
	ofn.lStructSize = sizeof(OPENFILENAME);

	ofn.nFilterIndex = 1;
	ofn.nMaxFile = MAX_PATH;

	if (GetOpenFileName(&ofn))
	{
		//MessageBox(hwnd, buf, TEXT("Îòêûðòü ôàéë"), 0);
		FILE* f;
		TCHAR buff[256] = { '\0' };
		if (!_wfopen_s(&f, buf, TEXT("r, ccs=UTF-8")))
		{
			while (!feof(f))
			{
				fgetws(buff, 256, f);
				//lstrcat(buff, TEXT("\r\n"));
				int pos = SendDlgItemMessage(hwnd, IDC_EDIT1, WM_GETTEXTLENGTH, NULL, NULL);
				SendDlgItemMessage(hwnd, IDC_EDIT1, EM_SETSEL, pos, pos);
				SendDlgItemMessage(hwnd, IDC_EDIT1, EM_REPLACESEL, NULL, LPARAM(buff));
			}
		}
		fclose(f);
	}
	InvalidateRect(hwnd, NULL, TRUE);
}

void CMainDialog::CWriteFile(HWND hwnd)
{
	OPENFILENAME ofn = { 0 };

	TCHAR filename[MAX_PATH] = TEXT("filename");

	ofn.hInstance = GetModuleHandle(0);
	ofn.hwndOwner = hwnd;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = TEXT("txt","bmp","png");
	ofn.lpstrFile = filename;
	ofn.lpstrFilter = TEXT("All files (*.*)\0*.*\0Text files (*.txt)\0*.txt\0BMP Files (*.bmp)\0*.bmp\0PNG Files (*.png)\0*.png\0");
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
	InvalidateRect(hwnd, NULL, TRUE);
}

void CMainDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	//case ID_FILE_FONT:
	{
		CHOOSEFONT chooseFont = { 0 };
		//lFont = { 0 };
		chooseFont.hwndOwner = hwnd;
		chooseFont.lStructSize = sizeof(CHOOSEFONT);
		chooseFont.lpLogFont = &lFont;
																// Выбор шрифта !
		chooseFont.Flags = CF_SCREENFONTS | CF_EFFECTS;

		if (ChooseFont(&chooseFont) == TRUE)
		{
			HFONT hFont = CreateFontIndirect(chooseFont.lpLogFont);
			SendDlgItemMessage(hwnd, IDC_EDIT1, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
		}
	}
	break;

		
	case IDC_BTNSTAR:
		/*hImage = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP2));
		if (hImage)
		{
			SendMessage(hPictureBox, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
		}
		else
		{
			MessageBox(hwnd, TEXT("Îøèáêà çàãðóçêè ôàéëà"), TEXT("Error"), MB_OK | MB_ICONERROR);
		}*/
		break;

	case ID_FILE_OPEN:
	{
		COpenFile(hwnd);
	}
	break;
	case ID_FILE_SAVE:
		break;
	case ID_FILE_SAVEAS:
		CWriteFile(hwnd);
		break;
	/*case ID_FILE_SEARCHIN:
	{
		endSel = startSel = 0;
		OnFind();
	}
		break;
	case ID_FILE_ZAMENIT:
	{
		endSel = startSel = 0;
		OnReplace();
	}
		break;*/
	case ID_FILE_EXIT:
		EndDialog(hwnd, IDOK);
		break;
	}
}

void CMainDialog::Cls_OnMenuSelect(HWND hwnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags)
{
	switch (item)
	{
		// Для отображения в строке состояния для верхнего меню!!!
		// Файл
	case ID_FILE_CREATE:
		SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)TEXT("Создать файл"));
		break;
	case ID_FILE_OPEN:
		SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)TEXT("Открыть файл"));
		break;
	case ID_FILE_SAVE:
		SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)TEXT("Сохранить "));
		break;
	case ID_FILE_SAVEAS:
		SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)TEXT("Сохранить файл в ..."));
		break;
	case ID_FILE_EXIT:
		SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)TEXT("Закрыть программу"));
		break;
	default:
		SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)TEXT("Ready"));
		break;
	}
	// Для отображения в строке состояния !!!
}

void CMainDialog::Cls_OnClose(HWND hDlg)
{
	EndDialog(hDlg, 0);
}

CMainDialog::~CMainDialog(void)
{
}
void CMainDialog::OnFind()
{
	// Проверим, открыто ли окно поиска
	if (hFindReplace)
	{
		//Активизируем окно поиска
		SetForegroundWindow(hFindReplace);
		return;
	}
	// обнуляем структуру FINDREPLACE
	ZeroMemory(&fr, sizeof(fr));
	DWORD start, end;
	// получим весь текст, находяшийся в текстовом поле ввода	
	GetWindowText(hEdit, alltext, 65536);

	// получим границы выделения фрагмента текста
	//SendMessage(hEdit, EM_GETSEL, WPARAM(&start), LPARAM(&end));
	DWORD selected = Edit_GetSel(hEdit);
	start = LOWORD(selected);
	end = HIWORD(selected);

	// скопируем в буфер выделенный фрагмент текста
	_tcsncpy(bufFind, alltext + start, end - start);
	bufFind[end - start] = TEXT('\0');

	fr.lStructSize = sizeof(fr);

	// главный диалог является окном-владелецем
	fr.hwndOwner = hDialog;

	// указатель на буфер, содержащий строку для поиска
	fr.lpstrFindWhat = bufFind;
	fr.wFindWhatLen = 100;

	// поиск от текущего положения каретки в тексте до конца документа
	fr.Flags = FR_DOWN;

	// отображаем диалог Найти
	hFindReplace = FindText(&fr);
}

void CMainDialog::OnReplace()
{
	// Проверим, открыто ли окно замены
	if (hFindReplace)
	{
		// Активизируем окно замены
		SetForegroundWindow(hFindReplace);
		return;
	}
	// обнуляем структуру FINDREPLACE
	ZeroMemory(&fr, sizeof(fr));
	DWORD start, end;

	// обнуляем буфер, предназначенный для хранения замещающей строки 
	ZeroMemory(&bufReplace, sizeof(bufReplace));

	// получим весь текст, находяшийся в текстовом поле ввода
	GetWindowText(hEdit, alltext, 65536);

	// получим границы выделения фрагмента текста
	SendMessage(hEdit, EM_GETSEL, WPARAM(&start), LPARAM(&end));

	// скопируем в буфер выделенный фрагмент текста
	_tcsncpy(bufFind, alltext + start, end - start);
	bufFind[end - start] = TEXT('\0');
	fr.lStructSize = sizeof(fr);

	// главный диалог является окном-владелецем
	fr.hwndOwner = hDialog;

	// указатель на буфер, содержащий строку для поиска
	fr.lpstrFindWhat = bufFind;
	fr.wFindWhatLen = 100;

	// указатель на буфер, содержащий строку для замены
	fr.lpstrReplaceWith = bufReplace;
	fr.wReplaceWithLen = 100;

	// поиск от текущего положения каретки в тексте до конца документа
	fr.Flags = FR_DOWN;

	// отображаем диалог Заменить
	hFindReplace = ReplaceText(&fr);
}

void CMainDialog::MessageFromFindReplace()
{
	if (fr.Flags & FR_REPLACEALL)
	{
		//MessageBox(hDialog, TEXT("Нажата кнопка \"Заменить всё\""), TEXT("Поиск и замена"), MB_OK | MB_ICONINFORMATION);
	}

	if (fr.Flags & FR_REPLACE)
	{
		//MessageBox(hDialog, TEXT("Нажата кнопка \"Заменить\""), TEXT("Поиск и замена"), MB_OK | MB_ICONINFORMATION);
		// заменяем выделенный фрагмент текста на строку, находящуюся в буфере bufReplace
		SendMessage(hEdit, EM_REPLACESEL, WPARAM(TRUE), (LPARAM)bufReplace);
	}

	if (fr.Flags & FR_FINDNEXT)
	{
		//MessageBox(hDialog, TEXT("Нажата кнопка \"Найти далее\""), TEXT("Поиск и замена"), MB_OK | MB_ICONINFORMATION);

		DWORD Start, End;

		// выполняем поиск искомой строки
		TCHAR * p = _tcsstr(alltext + num, bufFind);
		if (p)
		{
			Start = p - alltext;
			End = Start + _tcslen(bufFind);
			SendMessage(hEdit, EM_SETSEL, Start, End);
			SendMessage(hEdit, EM_GETSEL, (WPARAM)&startSel, (LPARAM)&endSel);
			// выделяем найденную строку
			if (fr.Flags & FR_DOWN)
			{
				num = endSel;
			}
			else
			{
				num = 65536 - endSel;
			}
		}
	}

	if (fr.Flags & FR_DIALOGTERM)
	{
		hFindReplace = NULL;
		//MessageBox(hDialog, TEXT("Закрывается диалог поиска и замены!"), TEXT("Поиск и замена"), MB_OK | MB_ICONINFORMATION);
		return;
	}

	/*if (fr.Flags & FR_MATCHCASE)
	MessageBox(hDialog, TEXT("Установлен флажок регистрозависимости"), TEXT("Поиск и замена"), MB_OK | MB_ICONINFORMATION);

	if (fr.Flags & FR_WHOLEWORD)
	MessageBox(hDialog, TEXT("Установлен флажок поиска слова целиком"), TEXT("Поиск и замена"), MB_OK | MB_ICONINFORMATION);
	*/
	if (fr.Flags & FR_DOWN)
	{

	}
	else
	{

	}
}

void CMainDialog::Cls_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	mouse.x = cx;
	mouse.y = cy;
	SendMessage(hStatus, WM_SIZE, 0, 0);
	RECT r = { 0 };
	GetWindowRect(hStatus, &r);
	MoveWindow(hEdit, 74, 26, cx-84, cy - 53, TRUE);
}

BOOL CALLBACK CMainDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_SIZE, ptr->Cls_OnSize);
		HANDLE_MSG(hwnd, WM_MENUSELECT, ptr->Cls_OnMenuSelect);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	if (message == WM_FINDREPLACE)
		ptr->MessageFromFindReplace();
	return FALSE;
}