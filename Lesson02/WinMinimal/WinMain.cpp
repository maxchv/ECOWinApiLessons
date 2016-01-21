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
	// ����� ��������� ����
	WNDCLASS wnd;
	HWND hWnd;
	HINSTANCE hInstance;
	LPCWSTR lpszWinName;
	
	void initWindow()
	{
		// ���������������� ��������� WNDCLASS
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
		wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		// ���������� ������� ����
		wnd.lpfnWndProc = wndProc;
	}

	void registerWindow()
	{
		// ����������� ����
		if (!RegisterClass(&wnd))
		{
			throw WindowException("Error register window");
		}
	}

	void createWindow()
	{
		// �������� ���� �� ���� WNDCLASS
		hWnd = CreateWindow(
			lpszWinName,			// ��� ������
			TEXT("������ ������"),  // ���������
			WS_OVERLAPPEDWINDOW,    // ����� �����������
			100, 100,               // ���������� x, y
			800, 600,			    // ������� ���� (������, ������)
			NULL,					// ������������ ����
			NULL,                   // ����
			hInstance,              // ��������� ����������
			0);						// �������������� ���������
		if (!hWnd)
		{
			throw WindowException("Error create window");
		}
	}

	void showWindow()
	{
		// ���������� ����
		ShowWindow(hWnd, SW_NORMAL);
		// ������������ ����
		UpdateWindow(hWnd);
	}

	static LRESULT CALLBACK wndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
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
		// ���� ��������� ���������
		while (GetMessage(&msg, NULL, NULL, NULL))
		{
			// �������������� ����-���� ������� � �������
			TranslateMessage(&msg);
			// ��������������� �.�. �������� ��������� ������� WndProc
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

