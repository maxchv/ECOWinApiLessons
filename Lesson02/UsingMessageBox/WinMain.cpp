#include <Windows.h>

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdOptions, int nShowOpt)
{
	int res = MessageBox(NULL,							   // родилетьское окно отсутсвует
		       TEXT("Привет из диалога"),          // сообщение
		       TEXT("Да да, это диалоговое окно"), // заголовок
			   MB_ABORTRETRYIGNORE | MB_ICONERROR
	);

	switch (res)
	{
	case IDABORT:
		MessageBox(NULL, TEXT("Отмена"), TEXT("Результат"), MB_OK | MB_ICONEXCLAMATION);
		break;
	case IDRETRY:
		MessageBox(NULL, TEXT("Повторить"), TEXT("Результат"), MB_OK | MB_ICONINFORMATION);
		break;
	case IDIGNORE:
		MessageBox(NULL, TEXT("Игнорировать"), TEXT("Результат"), MB_OK | MB_ICONQUESTION);
		break;
	default:
		break;
	}

	return 0;
}