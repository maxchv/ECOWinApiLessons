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
    hListview = CreateWindow(WC_LISTVIEW, 0,
                        LVS_ICON | WS_CHILD | WS_VISIBLE,
                        rc.left, rc.top, rc.right, rc.bottom,
                        hWnd, (HMENU)IDC_LISTVIEW, g_hInst, 0);
    Стили окон:
    https://msdn.microsoft.com/en-us/library/windows/desktop/bb774739%28v=vs.85%29.aspx#LVS_REPORT
*/

// Шаг 3. Настройка и добавление списка изображений в listview.
//(Макросы ImageList_Create, ImageList_AddIcon, ListView_SetImageList)
/*
    Создание нового списка изображений
    https://msdn.microsoft.com/en-us/library/windows/desktop/bb761522(v=vs.85).aspx

    HIMAGELIST ImageList_Create(
        int  cx,			// Ширина в пикселях для каждого изображения
        int  cy,			// Высота в пикселях для каждого изображения
        UINT flags,			// Набор битовых флагов определяющих тип создаваемых изображений
                            // Перечень всех флагов:
                            // https://msdn.microsoft.com/en-us/library/windows/desktop/bb775232(v=vs.85).aspx
        int  cInitial,		// Количество изображений в списке
        int  cGrow			// Количество изображений которое может быть добавлено (при необходимости)
    );

    Возвращает дескриптор списка изображений в случае успежного создания или NULL при неудаче
    
    Примечание: Если список не нужен, то его необходимо уничтожить вызвав функцию 
    ImageList_Destroy.

    --

    Добавляем иконки в список изображений.
    https://msdn.microsoft.com/en-us/library/windows/desktop/bb761399(v=vs.85).aspx

    int ImageList_AddIcon(
        HIMAGELIST himl,	// Дескриптор списка изображения. 		
        HICON      hicon	// Дескриптор иконки
    );
        
    Возвращает индекс нового изображения при успехе и -1 в случае неудачи.
    
    --

    Ассоциировать список изображений с list-view control. 	
    https://msdn.microsoft.com/en-us/library/windows/desktop/bb775086(v=vs.85).aspx

    HIMAGELIST ListView_SetImageList(
        HWND       hwnd,			// Дескрипрот list-view control.
        HIMAGELIST himl,			// Дескриптор списка изображений.
        int        iImageList		// Тип изображений
                                    
    );

    Тип изображений в списке может быть:

    LVSIL_NORMAL		Список изображений с большими иконками
    LVSIL_SMALL			Список изображений с маленькими иконками
    LVSIL_STATE			Image list with state images.
    LVSIL_GROUPHEADER	Image list for group header.

    Возвращает дескриптор списка изображений ранее ассоциированного с элементом 
    управление в случае успешного выполнения команыди или NULL в случае ошибки.
*/

//Шаг 4. Добавить изображения в list view common control.
//(LVITEM, ListView_InsertItem, ListView_SetItem)
/*
    Структура задает или получает атрибуты элемента list-view.
    https://msdn.microsoft.com/en-us/library/windows/desktop/bb774760%28v=vs.85%29.aspx

    typedef struct {
        UINT   mask;					// Set of flags that specify which members of this structure contain data to be set or which members are being requested. This member can have one or more of the following flags set: 
        int    iItem;					// Zero-based index of the item to which this structure refers.
        int    iSubItem;				// One-based index of the subitem to which this structure refers, or zero if this structure refers to an item rather than a subitem. 
        UINT   state;
        UINT   stateMask;
        LPTSTR pszText;					// If the structure specifies item attributes, pszText is a pointer to a null-terminated string containing the item text. 
        int    cchTextMax;				// Number of TCHARs in the buffer pointed to by pszText, including the terminating NULL.
        int    iImage;					// Index of the item's icon in the control's image list
        LPARAM lParam;
        #if (_WIN32_IE >= 0x0300)
        int    iIndent;
        #endif
        #if (_WIN32_WINNT >= 0x0501)
        int    iGroupId;
        UINT   cColumns;				// Number of data columns (subitems) to display for this item in tile view
        PUINT  puColumns;
        #endif
        #if (_WIN32_WINNT >= 0x0600)
        int    *piColFmt;
        int    iGroup;
        #endif
    } LVITEM, *LPLVITEM;

    Для добавления нового элемента в список необходимо отправить сообщение LVM_INSERTITEM
    https://msdn.microsoft.com/en-us/library/windows/desktop/bb761107%28v=vs.85%29.aspx
    или воспользоваться макросом ListView_InsertItem
    https://msdn.microsoft.com/en-us/library/windows/desktop/bb775038%28v=vs.85%29.aspx

    int ListView_InsertItem(
        HWND     hwnd,			// A handle to the list-view control.
        const LPLVITEM pitem	// A pointer to an LVITEM structure that specifies the attributes of the list-view item. 
    );
    Returns the index of the new item if successful, or -1 otherwise.
*/

// Шаг 5. Освободить ресурсы при закрытии диалога.
//(ImageList_Destroy)

// Шаг 6. Дополнительные настройки
/*
    LVS_EX_FULLROWSELECT	
    When an item is selected, the item and all its subitems are highlighted. 
    This style is available only in conjunction with the LVS_REPORT style.
    https://msdn.microsoft.com/en-us/library/windows/desktop/bb774732%28v=vs.85%29.aspx
*/

// Шаг 7. Настроить стиль отображения списка
/*
    Changing List View Styles
    You can change the window style of a list view control after it is created. First, use the GetWindowLong function to get the current style. Then use the SetWindowLong function to specify the new style. For a complete list of the list view window styles, see List View Window Styles.

    The following example changes the style bits that govern the view mode.

    // SetView - sets a list view's window style to change the view.

    // hwndLV - handle of the list view control

    // dwView - value specifying a view style

    VOID WINAPI SetView(HWND hwndLV, DWORD dwView)
    {
        // Get the current window style.
        DWORD dwStyle = GetWindowLong(hwndLV, GWL_STYLE);
        
        // Only set the window style if the view bits have changed.
        if ((dwStyle & LVS_TYPEMASK) != dwView)
            SetWindowLong(hwndLV, GWL_STYLE, (dwStyle & ~LVS_TYPEMASK) | dwView);
    }

    --

    Searches for a list-view item that has the specified properties and bears the 
    specified relationship to a specified item. You can use this macro or 
    send the LVM_GETNEXTITEM message explicitly.

    int ListView_GetNextItem(
        HWND hwnd,
        int  iStart,
        UINT flags
    );
*/

/*
Практическое задания
https://msdn.microsoft.com/ru-ru/library/windows/desktop/aa365200%28v=vs.85%29.aspx
*/

int main()
{
    return 0;
}

