#include <Windows.h>
#include <iostream>
using namespace std;

class WindowClass
{
	WNDCLASS wnd;
public:
	WindowClass()
	{
		// ���������������� ��������� WNDCLASS
	}
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCommandOpt,
	int nShowOpt)
{
	LPCWSTR lpszWinName = TEXT("My Window");
	
	// ����� ��������� ����
	WNDCLASS wnd;
	// ����� ����
	wnd.style = CS_VREDRAW | CS_HREDRAW;
	wnd.cbClsExtra = 0;				// ����������� ������ ����������
	wnd.cbWndExtra = 0;
	wnd.hInstance = hInstance;      // ��������� ����������
	wnd.lpszClassName = lpszWinName;// ��� ����
	wnd.lpszMenuName = NULL;        // ���� ����������
	// IDI_* - �������������� ����������� ������
	wnd.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	// ID�_* - �������������� ����������� ��������
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	// ������� ����
	wnd.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	// ���������� ������� ����
	wnd.lpfnWndProc = WndProc;
	
	// ����������� ����
	if (!RegisterClass(&wnd))
	{
		return 1;
	}

	// �������� ���� �� ���� WNDCLASS
	HWND hWnd = CreateWindow(
		lpszWinName,			// ��� ������
		TEXT("������ ������"),  // ���������
		WS_OVERLAPPEDWINDOW,    // ����� �����������
		100, 100,               // ���������� x, y
		800, 600,			    // ������� ���� (������, ������)
		NULL,					// ������������ ����
		NULL,                   // ����
		hInstance,              // ��������� ����������
		0);						// �������������� ���������
	// ���������� ����
	ShowWindow(hWnd, nShowOpt);
	// ������������ ����
	UpdateWindow(hWnd);

	MSG msg;
	// ���� ��������� ���������
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		// �������������� ����-���� ������� � �������
		TranslateMessage(&msg);
		// ��������������� �.�. �������� ��������� ������� WndProc
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY: // ��������� ������� �������� ����������
		PostQuitMessage(0);
		break;
	default:
		// �������� �������������� ��������� ���������� ���������� ��������� 
		return DefWindowProc(hWnd, Msg, wParam, lParam);
		break;
	}

	return 0;
}