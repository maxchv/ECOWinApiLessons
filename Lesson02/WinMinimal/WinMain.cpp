#include <Windows.h>
#include <iostream>
#include <exception>
using namespace std;

class WindowException : exception
{
public:
	WindowException(const char const *message) : exception(message)
	{

	}
};

class Window
{
	// Класс будующего окна
	WNDCLASS wnd;
	HWND hWnd;
	HINSTANCE hInstance;
	LPCWSTR lpszWinName;
	
	void initWindow()
	{
		// инициализировать структуру WNDCLASS
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
		wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		// обработчик событий окна
		wnd.lpfnWndProc = wndProc;
	}

	void registerWindow()
	{
		// регистрация окна
		if (!RegisterClass(&wnd))
		{
			throw WindowException("Error register window");
		}
	}

	void createWindow()
	{
		// создание окна на базе WNDCLASS
		hWnd = CreateWindow(
			lpszWinName,			// имя класса
			TEXT("Привет Окошки"),  // заголовок
			WS_OVERLAPPEDWINDOW,    // стиль отображения
			100, 100,               // координаты x, y
			800, 600,			    // размеры окна (ширина, высота)
			NULL,					// родительское окно
			NULL,                   // меню
			hInstance,              // экземпляр приложения
			0);						// дополнительные параметры
		if (!hWnd)
		{
			throw WindowException("Error create window");
		}
	}

	void showWindow()
	{
		// отобразить окно
		ShowWindow(hWnd, SW_NORMAL);
		// перерисовать окно
		UpdateWindow(hWnd);
	}

	static LRESULT CALLBACK wndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
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
	

public:
	Window(): lpszWinName(TEXT("My Window"))
	{
		hInstance = GetModuleHandle(NULL);		
		try 
		{
			initWindow();
			registerWindow();
			createWindow();
			showWindow();
		}
		catch (...)
		{
			throw;
		}
	}

	int start()
	{
		MSG msg;
		// цикл обработки сообщений
		while (GetMessage(&msg, NULL, NULL, NULL))
		{
			// Преобразование скан-кода клавиши в символы
			TranslateMessage(&msg);
			// Диспетчеризация т.е. передача сообщения функции WndProc
			DispatchMessage(&msg);
		}
		return (int)msg.wParam;
	}

};

INT APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCommandOpt,
	int nShowOpt)
{
	Window win;
	win.start();
	return 0;
}

