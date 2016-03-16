#include "MainDialog.h"

// идентификатор зарегистрированного сообщения FINDMSGSTRING
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
	// Проверим, открыто ли окно поиска
	if(hFR)
	{
		//Активизируем окно поиска
		SetForegroundWindow(hFR);
		return;
	}
	// обнуляем структуру FINDREPLACE
	ZeroMemory(&fr, sizeof(fr));
	DWORD start, end;
	// получим весь текст, находяшийся в текстовом поле ввода
	
	GetWindowText(hEdit, alltext, 65536);
	// получим границы выделения фрагмента текста
	SendMessage(hEdit, EM_GETSEL, WPARAM(&start), LPARAM(&end));
	// скопируем в буфер выделенный фрагмент текста
	_tcsncpy(bufFind, alltext+start, end-start);
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
	hFR = FindText(&fr);
}

void CMainDialog::OnReplace()
{
	// Проверим, открыто ли окно замены
	if(hFR)
	{
		// Активизируем окно замены
		SetForegroundWindow(hFR);
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
	hFR = ReplaceText(&fr);
}

void CMainDialog::MessageFromFindReplace()
{
	if(fr.Flags & FR_REPLACEALL) 
		MessageBox(hDialog, TEXT("Нажата кнопка \"Заменить всё\""), TEXT("Поиск и замена"), MB_OK | MB_ICONINFORMATION);

	if(fr.Flags & FR_REPLACE)
	{
		MessageBox(hDialog, TEXT("Нажата кнопка \"Заменить\""), TEXT("Поиск и замена"), MB_OK | MB_ICONINFORMATION);
		// заменяем выделенный фрагмент текста на строку, находящуюся в буфере bufReplace
		SendMessage(hEdit, EM_REPLACESEL, WPARAM(TRUE),(LPARAM)bufReplace);
	}

	if(fr.Flags & FR_FINDNEXT)
	{
		MessageBox(hDialog, TEXT("Нажата кнопка \"Найти далее\""), TEXT("Поиск и замена"), MB_OK | MB_ICONINFORMATION);
		DWORD Start, End;
		// выполняем поиск искомой строки
		TCHAR * p = _tcsstr(alltext, bufFind);
		if(p)
		{
			Start = p - alltext;
			End = Start + _tcslen(bufFind);
			// выделяем найденную строку
			SendMessage(hEdit, EM_SETSEL, Start, End); 
		}
	}

	if(fr.Flags&FR_DIALOGTERM)
	{
		hFR = NULL;
		MessageBox(hDialog, TEXT("Закрывается диалог поиска и замены!"), TEXT("Поиск и замена"), MB_OK | MB_ICONINFORMATION);
		return;
	}

	if(fr.Flags & FR_MATCHCASE)
		MessageBox(hDialog, TEXT("Установлен флажок регистрозависимости"), TEXT("Поиск и замена"), MB_OK | MB_ICONINFORMATION);

	if(fr.Flags & FR_WHOLEWORD)
		MessageBox(hDialog, TEXT("Установлен флажок поиска слова целиком"), TEXT("Поиск и замена"), MB_OK | MB_ICONINFORMATION);

	if(fr.Flags & FR_DOWN)
		MessageBox(hDialog, TEXT("Выбран режим поиска в направлении вниз"), TEXT("Поиск и замена"), MB_OK | MB_ICONINFORMATION);
	else
		MessageBox(hDialog, TEXT("Выбран режим поиска в направлении вверх"), TEXT("Поиск и замена"), MB_OK | MB_ICONINFORMATION);
	
}


BOOL CALLBACK CMainDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	// обработка сообщений, посылаемых из немодального диалогового окна
	if(message == WM_FR)
		ptr->MessageFromFindReplace();
	return FALSE;
}
