#include"Change Calculator.h"


HWND hCalcWnd = NULL;                          // ���������� ���� ������������
LPCTSTR winCalcClassName = TEXT("SciCalc");    // �������� ������ ���� �����������
vector<HWND> hCHILDS_Wnd;                      // ������ ��� ������� �������� ����

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

VOID CALLBACK timerProc(HWND hWnd, UINT msg, UINT timerId, DWORD iterval);

BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(time(0));

	// 1. ���������� ���������
	HWND hWnd;     //���������� ����
	MSG msg;
	LPCTSTR winClassName = TEXT("Changer program");


	// 2. ������� ��������� ����
	WNDCLASSEX wcl = { 0 };

	wcl.cbSize = sizeof(wcl);								 // ������ ��������� WNDCLASSEX
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ���� ����
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);               // ����������� ������ 
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);             // ����������� ������
	wcl.hInstance = hInstance;                               // ���������� ����������
	wcl.lpfnWndProc = WndProc;                               // ��������� �� ������� ��������� (������� ��������� ������)
	wcl.lpszClassName = winClassName;                        // ��� ������ ������
	wcl.style = CS_VREDRAW | CS_HREDRAW;                     // ����� ����

															 // 3. �����������
	if (!RegisterClassEx(&wcl))
	{
		// ������ ����������� ����
		MessageBox(NULL, TEXT("Error"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return 0;
	}

	// 4. �������� ����
	hWnd = CreateWindow(winClassName, // ����������������� ��� ������ ����
		TEXT("Changer program"),      // ��������� ����
		WS_OVERLAPPEDWINDOW,          // ����� ����
		X_INDENT,                     // x - ������ �� �����������
		Y_INDENT,                     // y - ������ �� ���������
		WIDTH_WINDOW,                 // ������
		HEIGHT_WINDOW,                // ������
		NULL,                         // ������������ ����
		NULL,                         // ����
		hInstance,
		NULL);

	// 5. ����������� ����
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// 6. ���� ��������� ���������
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

// ������� ��������� �������� ���� ������������
BOOL CALLBACK EnumChildProc(HWND hChildWnd, LPARAM lParam)
{
	hCHILDS_Wnd.push_back(hChildWnd); // ��������� hWnd ������� ��������� ���� � �������
	return true;
}



// ������� ��������� �������
VOID CALLBACK timerProc(HWND hWnd, UINT msg, UINT timerId, DWORD iterval)
{
	INT nRandIdx = rand() % hCHILDS_Wnd.size(); //���������� ����� ������ ������� ������������ ��� ���� ������������
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
	wstringstream SS; // ��������� ����� ��� ������ ���������

	switch (msg)
	{
	case WM_CREATE:
		//�������� ���������� ���� �����������
		hCalcWnd = FindWindow(winCalcClassName, NULL);

		// �������� �� �������� ���� ������������
		while (!hCalcWnd)
		{
			MessageBox(hWnd, L"Can not find Calculator! Please, open Calculator for start work!", L"Error", MB_OK | MB_ICONERROR);
			hCalcWnd = FindWindow(winCalcClassName, NULL);
		}

		// �������  �������� ���� � ������������ � �������� ��� � ��������
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