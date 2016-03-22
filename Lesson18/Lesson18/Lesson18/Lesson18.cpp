// Lesson18.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Панель инструментов (Toolbar Control)
/*
    Панель инструментов — строка горизонтально (или вертикально) расположенных графических кнопок, иногда 
    объединенных в группы. Разбивка на группы осуществляется программным путем, в соответствии с 
    назначением кнопок Изображения кнопок хранятся в общем растровом изображении, входящем в ресурсы приложения. 
    Если щелкнуть кнопку, она пошлет командное сообщение, подобно меню и быстрым клавишам. 
    Для обновления состояния кнопок служат обработчики обновления командного пользовательского интерфейса, 
    вызываемые каркасом приложений для изменения внешнего вида кнопок

    https://msdn.microsoft.com/en-us/library/windows/desktop/bb760443(v=vs.85).aspx
*/

// Шаг 1. Загрузка и регистрация класса окна Toolbar.
/*
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

INITCOMMONCONTROLSEX iccx;
iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
iccx.dwICC = ICC_BAR_CLASSES;
if (!InitCommonControlsEx(&iccx))
{
    return FALSE;
}
*/

// Шаг 2. Создание панели инструментов (CreateWindow)
/*

Для создания используется класс окна TOOLBARCLASSNAME

Можно задать следующие стили:

TBSTYLE_FLAT		Текст кнопок отображается под картинками.
                    Для предотвращаения проблем с перерисовкой, 
                    стиль должен быть
                    установлен перед отображением панели инструментов.
TBSTYLE_TOOLTIP		Вывод краткого описания кнопки в окне элемента управления
                    Tool Tip
TBSTYLE_LIST		Текст кнопок появляется справа от картинок.
TBSTYLE_TRANSPARENT Создает прозрачную панель инструментов 
                    (но не прозрачные кнопки).
                    Текст кнопок отображается под картинками.
TBSTYLE_ALTDRAG		Если не указан стиль TBSTYLE_ALTDRAG, то пользователь может 
                    передвигать кнопки по поверхности Toolbar левой клавишей мыши 
                    при нажатой клавише <Shift>. Если же этот стиль указан, для 
                    перемещения кнопок используется клавиша <Alt>. В любом случае 
                    кнопки можно передвигать только тогда, когда указан стиль CCS_ADJUSTABLE
TBSTYLE_WRAPABLE	Окно Toolbar может состоять из нескольких строк. Новые строки 
                    создаются в том случае, если все кнопки не помещаются в одной строке

https://msdn.microsoft.com/en-us/library/windows/desktop/bb760439(v=vs.85).aspx#TBSTYLE_LIST

Дополнительные стили:

CCS_ADJUSTABLE		Если указан этот стиль, пользователь может изменять 
                    конфигурацию элемента управления
CCS_BOTTOM			Элемент управления должен быть расположен в нижней части внутренней 
                    области окна
CCS_TOP				Элемент управления должен быть расположен в верхней части внутренней 
                    области окна

https://msdn.microsoft.com/en-us/library/windows/desktop/bb775498(v=vs.85).aspx#CCS_ADJUSTABLE

Пример:
    HWND hToolbar = CreateWindow(TOOLBARCLASSNAME, 0,
        TBSTYLE_FLAT | CCS_ADJUSTABLE | CCS_NODIVIDER | WS_CHILD | WS_VISIBLE,
        0, 0, 0, 0,
        hWnd, (HMENU)IDC_TOOLBAR, GetModuleHandle(0), 0);
*/

// Шаг 3. Настроить и добавить кнопки в панель инструментов.
/*
3.1 После создания необходимо отправить сообщение TB_BUTTONSTRUCTSIZE в панель инструментов. 
Если приложение использует функцию CreateWindow для создания панели инструментов, 
необходимо отправить это сообщение перед сообщениями TB_ADDBITMAP или TB_ADDBUTTONS. 

Посылаем сообщение TB_BUTTONSTRUCTSIZE, указывая размер структуры TBBUTTON.

Пример:
    SendMessage(hToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
    
3.2 Добавить изображения (TBADDBITMAP, TB_ADDBITMAP)

Затем заполняем структуру TBADDBITMAP:
    typedef struct
    {
        HINSTANCE hInst;				// идентификатор приложения
        UINT nID;						// nID - идентификатор изображения кнопок
    } TBADDBITMAP, *LPTBADDBITMAP;

Можно использовать предопределенные системные изображения, тогда hInst должен быть
задан HINST_COMMCTRL, а значение nID выбирается из списка

IDB_STD_LARGE_COLOR				Стандартные большие цветные изображения
IDB_STD_SMALL_COLOR				Стандартные маленькие цветные изображения

Другие стандартные значения nID: https://msdn.microsoft.com/en-us/library/windows/desktop/bb760475(v=vs.85).aspx
 
Пример:
    TBADDBITMAP tbAddBmp = {0};
    tbAddBmp.hInst = HINST_COMMCTRL;
    tbAddBmp.nID = IDB_STD_SMALL_COLOR;

Адрес заполненной структуры типа TBADDBITMAP передаем в 
качестве параметров сообщения TB_ADDBITMAP.

Пример:
    SendMessage(hToolbar, TB_ADDBITMAP, 0, (WPARAM)&tbAddBmp);

3.3 Добавление кнопок (TBBUTTON, TB_ADDBUTTONS)

Далее необходимо создать массив структур TBBUTTON , который описывает 
кнопки и разделители между группами кнопок. 
В этом массиве необходимо зарезервировать по одной структуре для каждой 
кнопки и для каждого разделителя групп кнопок.

В файле commctrl.h находится такое определение структуры TBBUTTON:

typedef struct _TBBUTTON
{
    int   iBitmap;			// индекс изображения кнопки
    int   idCommand;		// идентификатор, который будет передаваться родительскому окну с 
                            // сообщением WM_COMMAND
                            // Если элемент массива структур TBBUTTON описывает разделитель 
                            // группы кнопок, в поле idCommand нужно записать нулевое значение.
    BYTE  fsState;			// флаг исходного состояния кнопки
    BYTE  fsStyle;			// стиль кнопки
    DWORD dwData;			// дополнительные данные, которые будут хранится в описании 
                            // кнопки и использоваться при необходимости
    int   iString;			// индекс текстовой метки кнопки
} TBBUTTON, NEAR * PTBBUTTON, FAR * LPTBBUTTON;
typedef const TBBUTTON FAR * LPCTBBUTTON;

Для описания включаемых в приложение кнопок в Windows имеется два набора готовых для 
использования битовых образов. Первый набор содержит изображения 15 кнопок, 
соответствующих командам меню File и Edit, откуда мы и позаимствуем необходимые изображения. 

Идентификаторы кнопок вполне отражают их назначение:
    STD_CUT,		STD_COPY,		STD_PASTE,		STD_UNDO,		STD_REDOW, 
    STD_DELETE,		STD_FILENEW,	STD_PRINTPRE,	STD_PROPERTIES, STD_HELP, STD_FIND, 
    STD_FILEOPEN,	STD_FILESAVE,	STD_REPLACE,	STD_PRINT.	

Другие идентификаторы
    https://msdn.microsoft.com/en-us/library/windows/desktop/bb760433(v=vs.85).aspx

Флаг исходного состояния кнопки fsState:
TBSTATE_ENABLED			Кнопка находится в разблокированном состоянии. 
                        Если этот флаг не установлен, кнопка заблокирована и отображается 
                        серым цветом
TBSTATE_CHECKED			Кнопка изображается в нажатом состоянии. Этот флаг используется 
                        для кнопок с фиксацией
TBSTATE_HIDDEN			Скрытая кнопка, не отображается
TBSTATE_INDETERMINATE	Кнопка отображается серым цветом
TBSTATE_PRESSED			Кнопка изображается в нажатом состоянии
TBSTATE_WRAP			Кнопки, расположенные после той, что имеет флаг TBSTATE_WRAP, 
                        отображаются на новой строке. Таким образом, вы можете создать 
                        многострочный Toolbar . Этот флаг можно указывать только тогда, 
                        когда установлен флаг TBSTATE_ENABLED

Другие состояния: https://msdn.microsoft.com/en-us/library/windows/desktop/bb760437(v=vs.85).aspx

Стиль кнопки fsStyle:

TBSTYLE_BUTTON		Стандартная кнопка
TBSTYLE_CHECK		Кнопка с фиксацией. Эта кнопка "залипает", когда пользователь нажимает на нее. Для того чтобы вернуть кнопку в исходное состояние, необходимо нажать на нее еще раз
TBSTYLE_CHECKGROUP	Кнопка с фиксацией, которая остается нажатой до тех пор, пока нажата другая кнопка из этой же группы
TBSTYLE_GROUP		Стандартная кнопка, которая остается нажатой до тех пор, пока нажата другая кнопка из этой же группы
TBSTYLE_SEP			Разделитель между группами кнопок

Другие стили: https://msdn.microsoft.com/en-us/library/windows/desktop/bb760439(v=vs.85).aspx

Пример сосздания набора из 7 кнопок:

    const int numButtons = 7;
    TBBUTTON tbButtons[numButtons] =
    {
        { STD_FILENEW, NULL, TBSTATE_ENABLED,
            BTNS_AUTOSIZE, 0, 0, (INT_PTR)TEXT("New") },
        { STD_FILEOPEN, NULL, TBSTATE_ENABLED,
            BTNS_AUTOSIZE, 0, 0, (INT_PTR)TEXT("Open") },
        { STD_FILESAVE, NULL, 0,
            BTNS_AUTOSIZE, 0, 0, (INT_PTR)TEXT("Save") },
        { 0, NULL, 0, TBSTYLE_SEP, 0, 0, (INT_PTR)TEXT("") }, // разделитель
        { STD_COPY, NULL, TBSTATE_ENABLED,
            BTNS_AUTOSIZE, 0, 0, (INT_PTR)TEXT("Copy") },
        { STD_CUT, NULL, TBSTATE_ENABLED,
            BTNS_AUTOSIZE, 0, 0, (INT_PTR)TEXT("Cut") },
        { STD_PASTE, NULL, TBSTATE_ENABLED,
            BTNS_AUTOSIZE, 0, 0, (INT_PTR)TEXT("Paste") }
    };

Добавляем кнопки к панели инструментов:
    
    SendMessage(hToolbar, TB_ADDBUTTONS, numButtons, (LPARAM)tbButtons);
*/

// Шаг 4. Передать сообщение автоматически разместить и отобразить 
//        панель инструментов. (TB_AUTOSIZE)
/*

Пример:
    SendMessage(hToolbar, TB_AUTOSIZE, 0, 0);
*/

// Шаг 5. Обработать сообщения от панели инструментов
/*
Toolbar посылает в родительское окно сообщения WM_COMMAND и WM_NOTIFY.

Параметр lParam сообщения WM_NOTIFY содержит указатель на структуру 
TBNOTIFY (содержащую в самом начале структуру NMHDR ):
    typedef struct
    {
        NMHDR    hdr;
        int      iItem;
        TBBUTTON tbButton;
        int      cchText;
        LPTSTR   pszText;
    } TBNOTIFY, FAR * LPTBNOTIFY;

В этой структуре поле iItem содержит номер кнопки, от которой пришло извещение 
(нумерация кнопок начинается с нуля).
Структура tbButton типа TBBUTTON содержит описание кнопки.

В поле cchText находится длина текстовой строки, соответствующей кнопке. 
Адрес этой строки передается через параметр pszText.

*/
int _tmain(int argc, _TCHAR* argv[])
{
    return 0;
}

