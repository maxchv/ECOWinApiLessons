#include "DialogUtils.h"

// ����������� ������ �� ������ Edit � ������
bool DialogUtils::Text2Text(HWND hEditFrom, HWND hEditTo)
{	
	int length = Edit_GetTextLength(hEditFrom);
	std::unique_ptr<TCHAR> buffer(new TCHAR[length + 1]);
	ZeroMemory(buffer.get(), length + 1);
	
	// �������� ����� � ���������� ���� �����
	Edit_GetText(hEditFrom, buffer.get(), length + 1);

	// ���������� ����� � ������ ����
	SetWindowText(hEditTo, buffer.get());
	return true; // �����
}
