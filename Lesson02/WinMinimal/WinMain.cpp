#include <Windows.h>
#include <iostream>
using namespace std;

class WindowClass
{
	WNDCLASS wnd;
public:
	WindowClass()
	{
		// инициализировать структуру WNDCLASS
	}
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCommandOpt,
	int nShowOpt)
{
	LPCWSTR lpszWinName = TEXT("My Window");
	
	// Класс будующего окна
	WNDCLASS wnd;
	// стиль окна
	wnd.style = CS_VREDRAW | CS_HREDRAW;
	wnd.cbClsExtra = 0;				// расширенные данные остутсвуют
	wnd.cbWndExtra = 0;
	wnd.hInstance = hInstance;      // экземпляр приложения
	wnd.lpszClassName = lpszWinName;// имя окна
	wnd.lpszMenuName = NULL;        // меню отсутсвует
	// IDI_* - идентификаторы стандартных иконок
	wnd.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	// IDС_* - идентификаторы стандартных курсоров
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	// задание фона
	wnd.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	// обработчик событий окна
	wnd.lpfnWndProc = WndProc;
	
	// регистрация окна
	if (!RegisterClass(&wnd))
	{
		return 1;
	}

	// создание окна на базе WNDCLASS
	HWND hWnd = CreateWindow(
		lpszWinName,			// имя класса
		TEXT("Привет Окошки"),  // заголовок
		WS_OVERLAPPEDWINDOW,    // стиль отображения
		100, 100,               // координаты x, y
		800, 600,			    // размеры окна (ширина, высота)
		NULL,					// родительское окно
		NULL,                   // меню
		hInstance,              // экземпляр приложения
		0);						// дополнительные параметры
	// отобразить окно
	ShowWindow(hWnd, nShowOpt);
	// перерисовать окно
	UpdateWindow(hWnd);

	MSG msg;
	// цикл обработки сообщений
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		// Преобразование скан-кода клавиши в символы
		TranslateMessage(&msg);
		// Диспетчеризация т.е. передача сообщения функции WndProc
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY: // наступило событие закрытие приложения
		PostQuitMessage(0);
		break;
	default:
		// передача необработанных сообщений системному диспетчеру сообщений 
		return DefWindowProc(hWnd, Msg, wParam, lParam);
		break;
	}

	return 0;
}