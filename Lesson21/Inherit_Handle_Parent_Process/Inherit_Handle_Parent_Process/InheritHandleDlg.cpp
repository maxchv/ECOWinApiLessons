#include "InheritHandleDlg.h"

CInheritHandleDlg* CInheritHandleDlg::ptr = NULL;

CInheritHandleDlg::CInheritHandleDlg(void)
{
	ptr = this;
}

CInheritHandleDlg::~CInheritHandleDlg(void)
{

}

void CInheritHandleDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

void CInheritHandleDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_BUTTON1)
	{
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES); // размер структуры
		sa.lpSecurityDescriptor = 0; // система защиты по умолчанию
		sa.bInheritHandle = TRUE; // дескриптор объекта ядра "Файл" наследуемый !!!
		HANDLE hHandle = CreateFile(
			TEXT("Test.txt"), // путь к файлу
			GENERIC_READ, // только чтение
			0, // запрет совместного использования файла
			&sa, // система защиты
			OPEN_EXISTING, // открытие существующего файла
			FILE_ATTRIBUTE_NORMAL, // атрибутов нет 
			NULL // обычно используется в клиент-серверном приложении
			);
		if (hHandle == INVALID_HANDLE_VALUE) // ошибка открытия файла
		{
			MessageBox(hwnd, TEXT("Ошибка открытия файла Test.txt"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
			return;
		}
		STARTUPINFO startin = {sizeof(STARTUPINFO)};
		PROCESS_INFORMATION info={0};
		TCHAR cmd[200];
		// дескриптор объекта ядра передается дочернему процессу через командную строку
		wsprintf(cmd, TEXT("%s %d"), TEXT("InheritHandle_ChildProcess.exe"), hHandle);
		CreateProcess(
			NULL, // в качестве имени файла выступает первая выделенная пробелами лексема из 2-го параметра
			cmd, // Указатель командной строки, содержащей, в том числе, имя исполняемого файла
			NULL, // атрибуты защиты процесса по умолчанию
			NULL, // атрибуты защиты потока по умолчанию
			TRUE, // наследование разрешено !!!
			0, // класс приоритета по умолчанию - NORMAL_PRIORITY_CLASS 
			NULL, // среда окружения наследуется у родительского процесса 
			NULL, // текущий каталог наследуется у родительского процесса 
			&startin, // способ отображения главного окна, а также размер и заголовок окна
			&info // информация о порождённом процессе
			);
		CloseHandle(hHandle); // закрывается описатель объекта ядра «файл»
		CloseHandle(info.hThread); // закрывается описатель объекта ядра «поток»
		CloseHandle(info.hProcess); // закрывается описатель объекта ядра «процесс»
	}
	else if(id == IDC_BUTTON2)
	{
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES); // размер структуры
		sa.lpSecurityDescriptor = 0; // система защиты по умолчанию
		sa.bInheritHandle = FALSE; // дескриптор объекта ядра "Файл" ненаследуемый !!!
		HANDLE hHandle = CreateFile(
			TEXT("Test.txt"), // путь к файлу
			GENERIC_READ, //только чтение
			0, // запрет совместного использования файла
			&sa, // система защиты
			OPEN_EXISTING, // открытие существующего файла
			FILE_ATTRIBUTE_NORMAL, // атрибутов нет 
			NULL // обычно используется в клиент-серверном приложении
			);
		if ( hHandle == INVALID_HANDLE_VALUE ) //ошибка открытия файла
			return;
		STARTUPINFO startin = {sizeof(STARTUPINFO)};
		PROCESS_INFORMATION info = {0};
		TCHAR cmd[200];
		// дескриптор объекта ядра передается дочернему процессу через командную строку
		wsprintf(cmd, TEXT("%s %d"), TEXT("InheritHandle_ChildProcess.exe"), hHandle);
		CreateProcess(
			NULL, // в качестве имени файла выступает первая выделенная пробелами лексема из 2-го параметра
			cmd, // Указатель командной строки, содержащей, в том числе, имя исполняемого файла
			NULL, // атрибуты защиты процесса по умолчанию
			NULL, // атрибуты защиты потока по умолчанию
			TRUE, // наследование разрешено !!!
			0, // класс приоритета по умолчанию - NORMAL_PRIORITY_CLASS 
			NULL, // среда окружения наследуется у родительского процесса 
			NULL, // текущий каталог наследуется у родительского процесса 
			&startin, // способ отображения главного окна, а также размер и заголовок окна
			&info // информация о порождённом процессе
			);
		CloseHandle(hHandle); // закрывается описатель объекта ядра «файл»
		CloseHandle(info.hThread); // закрывается описатель объекта ядра «поток»
		CloseHandle(info.hProcess); // закрывается описатель объекта ядра «процесс»
	}
	else if(id == IDC_BUTTON3)
	{
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES); // размер структуры
		sa.lpSecurityDescriptor = 0; // система защиты по умолчанию
		sa.bInheritHandle = TRUE; // дескриптор объекта ядра "Файл" наследуемый !!!
		HANDLE hHandle = CreateFile(
			TEXT("Test.txt"), // путь к файлу
			GENERIC_READ, // только чтение
			0, // запрет совместного использования файла
			&sa, // система защиты
			OPEN_EXISTING, // открытие существующего файла
			FILE_ATTRIBUTE_NORMAL, // атрибутов нет 
			NULL // обычно используется в клиент-серверном приложении
			);
		if ( hHandle == INVALID_HANDLE_VALUE ) // ошибка открытия файла
			return;
		STARTUPINFO startin = {sizeof(STARTUPINFO)};
		PROCESS_INFORMATION info={0};
		TCHAR cmd[200];
		// дескриптор объекта ядра передается дочернему процессу через командную строку
		wsprintf(cmd, TEXT("%s %d"), TEXT("InheritHandle_ChildProcess.exe"), hHandle);
		CreateProcess(
			NULL, // в качестве имени файла выступает первая выделенная пробелами лексема из 2-го параметра
			cmd, // Указатель командной строки, содержащей, в том числе, имя исполняемого файла
			NULL, // атрибуты защиты процесса по умолчанию
			NULL, // атрибуты защиты потока по умолчанию
			FALSE, // наследование запрещено !!!
			0, // класс приоритета по умолчанию - NORMAL_PRIORITY_CLASS 
			NULL, // среда окружения наследуется у родительского процесса 
			NULL, // текущий каталог наследуется у родительского процесса 
			&startin, // способ отображения главного окна, а также размер и заголовок окна
			&info // информация о порождённом процессе
			);
		CloseHandle(hHandle); // закрывается описатель объекта ядра «файл»
		CloseHandle(info.hThread); // закрывается описатель объекта ядра «поток»
		CloseHandle(info.hProcess); // закрывается описатель объекта ядра «процесс»
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