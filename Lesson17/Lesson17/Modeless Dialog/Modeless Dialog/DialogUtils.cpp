#include "DialogUtils.h"

// Копирование текста их одного Edit в другой
bool DialogUtils::Text2Text(HWND hEditFrom, HWND hEditTo)
{	
	int length = Edit_GetTextLength(hEditFrom);
	std::unique_ptr<TCHAR> buffer(new TCHAR[length + 1]);
	ZeroMemory(buffer.get(), length + 1);
	
	// Получаем текст с текстового поля ввода
	Edit_GetText(hEditFrom, buffer.get(), length + 1);

	// Отображаем текст в другом окне
	SetWindowText(hEditTo, buffer.get());
	return true; // успех
}
