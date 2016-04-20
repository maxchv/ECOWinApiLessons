#include "include.h"
#include "Application.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmd, int cmdShow)
{
	srand(time(0));
	Application app;
	return app.startProgramm(IDD_DIALOG1);
}