#include"Runing Window.h"

HWND hDeskWnd; //���������� ���� �������� �����
RECT rect_Desktop;  // ��������� ��� �������� ��������� ������ ���� �������� �����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
VOID CALLBACK timerProc(HWND hWnd, UINT msg, UINT timerId, DWORD iterval);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 1. ���������� ���������
	HWND hWnd;     //���������� ����
	MSG msg;
	LPCTSTR winClassName = TEXT("Runing Window");

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
		TEXT("Runing Window"),        // ��������� ����
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

// ������� ��������� �������
VOID CALLBACK timerProc(HWND hWnd, UINT msg, UINT timerId, DWORD iterval)
{
	RECT rect;                  // ��������� ��� �������� ��������� ������ ����
	GetWindowRect(hWnd, &rect); // ����� ������� ���������� ����

	switch (timerId)
	{
	case ID_MYTIMER:
		// -->
		if ((rect.right < rect_Desktop.right - X_INDENT) && rect.top == rect_Desktop.top + Y_INDENT)
		{
			MoveWindow(hWnd, rect.left + STEP_RUN, rect.top, rect.right - rect.left, rect.bottom - rect.top, true);
		}

		// ����
		else if ((rect.right == rect_Desktop.right - X_INDENT) && rect.bottom < rect_Desktop.bottom - Y_INDENT)
		{
			MoveWindow(hWnd, rect.left, rect.top + STEP_RUN, rect.right - rect.left, rect.bottom - rect.top, true);
		}

		// <--
		else if ((rect.bottom == rect_Desktop.bottom - Y_INDENT) && rect.left != rect_Desktop.left + X_INDENT)
		{
			MoveWindow(hWnd, rect.left - STEP_RUN, rect.top, rect.right - rect.left, rect.bottom - rect.top, true);
		}

		// �����
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
		hDeskWnd = GetDesktopWindow();          //��������� ����������� �������� �����
		GetWindowRect(hDeskWnd, &rect_Desktop); //��������� ��������� ���� ��� �����
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