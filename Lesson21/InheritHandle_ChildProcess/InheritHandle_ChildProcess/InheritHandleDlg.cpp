#include "InheritHandleDlg.h"

CInheritHandleDlg* CInheritHandleDlg::ptr = NULL;

CInheritHandleDlg::CInheritHandleDlg(void)
{
	ptr = this;
	// InheritHandle_ChildProcess.exe 101
	lstrcpy(CommandLine, GetCommandLine()); // получим командную строку
	MessageBox(NULL, CommandLine, TEXT("Command line"), MB_OK);
	TCHAR seps[]   = TEXT(" ");
	TCHAR *token, *last;
	token = _tcstok(CommandLine, seps); // разбиваем командную строку на лексемы (разделитель "пробел")
	while( token != NULL )
	{
		token = _tcstok(NULL, seps); // разбиваем командную строку на лексемы (разделитель "пробел")
		if(token)
			last = token; // указатель на последнюю лексему, т.е. на дескриптор объекта ядра
	}
	hHandle = HANDLE(_tstoi(last));
}

CInheritHandleDlg::~CInheritHandleDlg(void)
{

}

void CInheritHandleDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

void MessageAboutError(DWORD dwError)
{
	LPVOID lpMsgBuf = NULL;
	TCHAR szBuf[300]; 
	//Функция FormatMessage форматирует строку сообщения
	BOOL fOK = FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM /* флаг сообщает функции, что нужна строка, соответствующая коду ошибки, определённому в системе */
		| FORMAT_MESSAGE_ALLOCATE_BUFFER, // нужно выделить соответствующий блок памяти для хранения текста
		NULL, // указатель на строку, содержащую текст сообщения
		dwError, // код ошибки
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // язык, на котором выводится описание ошибки (язык пользователя по умолчанию)
		(LPTSTR)&lpMsgBuf, // указатель на буфер, в который будет записан текст сообщения
		0, // минимальный размер буфера для выделения памяти - память выделяет система
		NULL // список аргументов форматирования
		);
	if(lpMsgBuf != NULL)
	{
		wsprintf(szBuf, TEXT("Ошибка %d: %s"), dwError, lpMsgBuf); 
		MessageBox(NULL,  szBuf, TEXT("Сообщение об ошибке"), MB_OK | MB_ICONSTOP); 
		LocalFree(lpMsgBuf); // освобождаем память, выделенную системой
	}
}

void CInheritHandleDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_BUTTON1)
	{
		TCHAR buf[100] = {0};
		DWORD dwRead = 0;
		/*
			Чтение из файла

			BOOL WINAPI ReadFile(
				HANDLE hFile,				// дескриптор файла
				LPVOID lpBuffer,			// указатель на буфер, в который будут записаны данные, 	
											// прочтённые из файла
				DWORD nNumberOfBytesToRead, // максимальное количество байт для чтения
				LPDWORD lpNumberOfBytesRead, // указатель на переменную, в которую будет   	
				                             // записано фактическое количество прочтённых байт
				LPOVERLAPPED lpOverlapped	// указатель на структуру OVERLAPPED
			);

		*/
		ReadFile(hHandle, buf, sizeof(buf), &dwRead, NULL); // читаем строку из файла, дескриптор которого был унаследован от "родителя"
		DWORD dwError = GetLastError();
		if ( dwError != 0 ) // Ошибка чтения из файла
			MessageAboutError(dwError);
		else
		{
			MessageBox(hwnd, buf, TEXT("Наследование описателя"), MB_OK | MB_ICONINFORMATION);
			CloseHandle(hHandle); // закрываем описатель объекта ядра «файл»
		}
	}
}

BOOL CALLBACK CInheritHandleDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}