// ListViewTutorial.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// List View Control
/*
	http://msdn.microsoft.com/en-us/library/bb774737.aspx
*/

// Шаг 1.  Загрузка и регистрация класса окна Listview.
/*
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	iccx.dwICC = ICC_LISTVIEW_CLASSES;
	if (!InitCommonControlsEx(&iccx))
	return FALSE;
*/

// Шаг 2. Создания окна на базе класса Listview. (Функция CreateWindow)
/*



*/

// Шаг 3. Настройка и добавление списка изображений в listview.
//(Макросы ImageList_Create, ImageList_AddIcon, ListView_SetImageList)
/*
	Creates a new image list.
	https://msdn.microsoft.com/en-us/library/windows/desktop/bb761522(v=vs.85).aspx

	HIMAGELIST ImageList_Create(
		int  cx,			// The width, in pixels, of each image.
		int  cy,			// The height, in pixels, of each image.
		UINT flags,			// A set of bit flags that specify the type of image list to create. 
							// This parameter can be a combination of the
							// https://msdn.microsoft.com/en-us/library/windows/desktop/bb775232(v=vs.85).aspx
		int  cInitial,		// The number of images that the image list initially contains.
		int  cGrow			// The number of images by which the image list can grow when the system needs to make room for new images. This parameter represents the number of new images that the resized image list can contain.
	);
	Returns the handle to the image list if successful, or NULL otherwise.
	Remarks: When you finish using the image list, destroy it by calling the ImageList_Destroy function.

	--

	Adds an icon or cursor to an image list.
	https://msdn.microsoft.com/en-us/library/windows/desktop/bb761399(v=vs.85).aspx

	int ImageList_AddIcon(
		HIMAGELIST himl,	// A handle to the image list. If this parameter identifies a masked image list, the macro copies both the image and mask bitmaps of the icon or cursor. If this parameter identifies a nonmasked image list, the macro copies only the image bitmap.
		HICON      hicon	// A handle to the icon or cursor that contains the bitmap and mask for the new image.
	);
		
	Returns the index of the new image if successful, or -1 otherwise.
	
	--

	Assigns an image list to a list-view control. You can use this macro or send the LVM_SETIMAGELIST message explicitly.
	https://msdn.microsoft.com/en-us/library/windows/desktop/bb775086(v=vs.85).aspx

	HIMAGELIST ListView_SetImageList(
		HWND       hwnd,			// A handle to the list-view control.
		HIMAGELIST himl,			// A handle to the image list to assign.
		int        iImageList		// The type of image list. This parameter can be one of the following values
	);

	The type of image list. This parameter can be one of the following values:
	LVSIL_NORMAL		Image list with large icons.
	LVSIL_SMALL			Image list with small icons.
	LVSIL_STATE			Image list with state images.
	LVSIL_GROUPHEADER	Image list for group header.

	Returns the handle to the image list previously associated with the control if successful, or NULL otherwise.


*/

//Шаг 4. Add items to the the list view common control.
//(LVITEM, LVM_INSERTITEM)


//Шаг 5. In OnListviewSize of the window, resize and re-arrange the Listview
//control to fit the client rectangle. (MoveWindow, LVM_ARRANGE)


//Шаг 6. In OnListviewClose, free up the image list resources.
//(ImageList_Destroy)


int main()
{
    return 0;
}

