#include <Windows.h>

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdOptions, int nShowOpt)
{
	int res = MessageBox(NULL,							   // ������������ ���� ����������
		       TEXT("������ �� �������"),          // ���������
		       TEXT("�� ��, ��� ���������� ����"), // ���������
			   MB_ABORTRETRYIGNORE | MB_ICONERROR
	);

	switch (res)
	{
	case IDABORT:
		MessageBox(NULL, TEXT("������"), TEXT("���������"), MB_OK | MB_ICONEXCLAMATION);
		break;
	case IDRETRY:
		MessageBox(NULL, TEXT("���������"), TEXT("���������"), MB_OK | MB_ICONINFORMATION);
		break;
	case IDIGNORE:
		MessageBox(NULL, TEXT("������������"), TEXT("���������"), MB_OK | MB_ICONQUESTION);
		break;
	default:
		break;
	}

	return 0;
}