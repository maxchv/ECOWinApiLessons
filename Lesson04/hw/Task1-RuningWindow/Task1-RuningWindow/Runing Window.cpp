#include"Runing Window.h"

HWND hDeskWnd; //дескриптор окна рабочего стола
RECT rect_Desktop;  // структура для хранения координат сторон окна рабочего стола
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
VOID CALLBACK timerProc(HWND hWnd, UINT msg, UINT timerId, DWORD iterval);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 1. Объявление перменных
	HWND hWnd;     //дескриптор окна
	MSG msg;
	LPCTSTR winClassName = TEXT("Runing Window");

	// 2. Создать структуру окна
	WNDCLASSEX wcl = { 0 };

	wcl.cbSize = sizeof(wcl);								 // размер стркутуры WNDCLASSEX
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // цвет фона
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);               // стандартный курсор 
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);             // стандартная иконка
	wcl.hInstance = hInstance;                               // дескриптор приложения
	wcl.lpfnWndProc = WndProc;                               // указатель на оконную процедуру (функция обратного вызова)
	wcl.lpszClassName = winClassName;                        // имя нашего класса
	wcl.style = CS_VREDRAW | CS_HREDRAW;                     // стиль окна

															 // 3. Регистрация
	if (!RegisterClassEx(&wcl))
	{
		// ошибка регистрации окна
		MessageBox(NULL, TEXT("Error"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return 0;
	}

	// 4. Создание окна
	hWnd = CreateWindow(winClassName, // зарегестированное имя класса окна
		TEXT("Runing Window"),        // заголовок окна
		WS_OVERLAPPEDWINDOW,          // стиль окна
		X_INDENT,                     // x - отступ по горизонтали
		Y_INDENT,                     // y - отступ по вертикали
		WIDTH_WINDOW,                 // ширина
		HEIGHT_WINDOW,                // высота
		NULL,                         // родительское окно
		NULL,                         // меню
		hInstance,
		NULL);

	// 5. Отображение окна
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// 6. Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

// функция обработки таймера
VOID CALLBACK timerProc(HWND hWnd, UINT msg, UINT timerId, DWORD iterval)
{
	RECT rect;                  // структура для хранения координат сторон окна
	GetWindowRect(hWnd, &rect); // взять текущие координаты окна

	switch (timerId)
	{
	case ID_MYTIMER:
		// -->
		if ((rect.right < rect_Desktop.right - X_INDENT) && rect.top == rect_Desktop.top + Y_INDENT)
		{
			MoveWindow(hWnd, rect.left + STEP_RUN, rect.top, rect.right - rect.left, rect.bottom - rect.top, true);
		}

		// вниз
		else if ((rect.right == rect_Desktop.right - X_INDENT) && rect.bottom < rect_Desktop.bottom - Y_INDENT)
		{
			MoveWindow(hWnd, rect.left, rect.top + STEP_RUN, rect.right - rect.left, rect.bottom - rect.top, true);
		}

		// <--
		else if ((rect.bottom == rect_Desktop.bottom - Y_INDENT) && rect.left != rect_Desktop.left + X_INDENT)
		{
			MoveWindow(hWnd, rect.left - STEP_RUN, rect.top, rect.right - rect.left, rect.bottom - rect.top, true);
		}

		// вверх
		else if ((rect.left == rect_Desktop.left + X_INDENT) && rect.top != rect_Desktop.top + Y_INDENT)
		{
			MoveWindow(hWnd, rect.left, rect.top - STEP_RUN, rect.right - rect.left, rect.bottom - rect.top, true);
		}
		break;
	default:
		break;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_CREATE:
		hDeskWnd = GetDesktopWindow();          //получение дескриптора рабочего стола
		GetWindowRect(hDeskWnd, &rect_Desktop); //получение координат окна раб стола
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			SetTimer(hWnd, ID_MYTIMER, INTERVAL, timerProc);
			break;

		case VK_ESCAPE:
			KillTimer(hWnd, ID_MYTIMER);
			break;

		default:
			break;
		}

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}
	return 0;
}