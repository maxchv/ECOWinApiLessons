#include"Change Calculator.h"


HWND hCalcWnd = NULL;                          // дескриптор окна Калькулятора
LPCTSTR winCalcClassName = TEXT("SciCalc");    // название класса окна Калькулятор
vector<HWND> hCHILDS_Wnd;                      // вектор для перечня дочерних окон

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

VOID CALLBACK timerProc(HWND hWnd, UINT msg, UINT timerId, DWORD iterval);

BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(time(0));

	// 1. Объявление перменных
	HWND hWnd;     //дескриптор окна
	MSG msg;
	LPCTSTR winClassName = TEXT("Changer program");


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
		TEXT("Changer program"),      // заголовок окна
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

// функция обработки дочерних окон калькулятора
BOOL CALLBACK EnumChildProc(HWND hChildWnd, LPARAM lParam)
{
	hCHILDS_Wnd.push_back(hChildWnd); // сохраняем hWnd каждого дочернего окна в векторе
	return true;
}



// функция обработки таймера
VOID CALLBACK timerProc(HWND hWnd, UINT msg, UINT timerId, DWORD iterval)
{
	INT nRandIdx = rand() % hCHILDS_Wnd.size(); //генерируем любой индекс вектора дескрипторов доч окон калькулятора
	switch (timerId)
	{
	case ID_MYTIMER:

		ShowWindow(hCHILDS_Wnd.at(nRandIdx), SW_HIDE);
		nRandIdx = rand() % hCHILDS_Wnd.size();
		ShowWindow(hCHILDS_Wnd.at(nRandIdx), SW_SHOW);
		break;
	default:
		break;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	wstringstream SS; // временный поток для замены заголовка

	switch (msg)
	{
	case WM_CREATE:
		//получаем дескриптор окна калькулятор
		hCalcWnd = FindWindow(winCalcClassName, NULL);

		// проверка на открытие окна Калькулятора
		while (!hCalcWnd)
		{
			MessageBox(hWnd, L"Can not find Calculator! Please, open Calculator for start work!", L"Error", MB_OK | MB_ICONERROR);
			hCalcWnd = FindWindow(winCalcClassName, NULL);
		}

		// находим  дочернее окно в калькуляторе и передаем его в оработку
		EnumChildWindows(hCalcWnd, EnumChildProc, 0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			BringWindowToTop(hCalcWnd);
			SetTimer(hWnd, ID_MYTIMER, INTERVAL, timerProc);
			SS << L"Count of All Child windows in Calculator: ";
			SS << hCHILDS_Wnd.size();
			SetWindowText(hWnd, SS.str().c_str());
			break;

		case VK_ESCAPE:
			for_each(hCHILDS_Wnd.begin(), hCHILDS_Wnd.end(), [](HWND h) { ShowWindow(h, SW_SHOW); });
			KillTimer(hWnd, ID_MYTIMER);
			break;

		default:
			break;
		}
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		INT otstup = 10;

		SS << L"For start experement with Calculator press RETURN,";
		TextOut(hdc, PRINT_INDENT, PRINT_INDENT + PRINT_INDENT, SS.str().c_str(), SS.str().size());
		SS.str(L"");

		SS << L"for stop -- click this window and press ESCAPE";
		TextOut(hdc, PRINT_INDENT, PRINT_INDENT + PRINT_INDENT + PRINT_INDENT, SS.str().c_str(), SS.str().size());
		EndPaint(hWnd, &ps);
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