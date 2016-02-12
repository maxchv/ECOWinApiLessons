// Lesson09.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <bitset>
#include <iostream>
#include <vector>
#include <string>

// Повторение пройденного материала
/*

1)	Для чего обычно используют текстовые поля ввода?
2)	Какими способами можно создать текстовое поле на диалоге?
3)	Какое сообщение придёт в диалоговую процедуру при вводе текста в Edit Control?
4)	Какое уведомление от текстового поля приходит родительскому окну (диалогу) 
    при вводе текста?
5)	Какие сообщения отправляются текстовому полю ввода при копиро-вании, вырезании и 
    удалении фрагмента текста?
6)	Какое сообщение необходимо отправить текстовому полю, чтобы получить границы выделения текста?
7)	Какое сообщение необходимо отправить текстовому полю, чтобы выделить фрагмент текста? 
    Каким образом можно выделить весь текст?
8)	Как определить длину текста, введённого в текстовое поле?
9)	Какая функция позволяет установить, имеется ли текст в буфере об-мена?
10)	Какая функция позволяет изменить стиль элемента управления?
11)	Какая функция позволяет переопределить стандартную оконную процедуру элемента 
    управления?
*/


// Элемент управления «список» (List Box)

/*
    Элемент управления List Box представляет собой список элементов,
    из которых пользователь может выбрать один или более. Элементы 
    списка могут быть представлены строками, растровыми образами 
    или комбинацией текста и изображения.

    Обзор списков:
        https://msdn.microsoft.com/en-us/library/windows/desktop/bb775144(v=vs.85).aspx

    Создание списков: списки являются классами LISTBOX

    CreateWindowEx(WS_EX_CLIENTEDGE, 
                   TEXT("LISTBOX"), 0,
                   WS_CHILD | WS_VISIBLE | LBS_SORT | LBS_NOTIFY, 			
                   LEFT, TOP, WIDTH, HEIGHT, 
                   hDlg,
                   (HMENU)IDC_LIST			// идентификатор списка , 
                   hInstance, 
                   0);

    Стили списков:
        https://msdn.microsoft.com/en-us/library/windows/desktop/bb775149(v=vs.85).aspx

    Примечание: в CommCtrl.h определены удобные макросы для задания
                классов элементов управления
                см. https://msdn.microsoft.com/en-us/library/windows/desktop/bb775491(v=vs.85).aspx#WC_LISTBOX
*/

// Сообщения списков
/*
    Перечень всех сообщений:
        https://msdn.microsoft.com/en-us/library/windows/desktop/bb775146(v=vs.85).aspx#Messages
                    

    Код сообщения:	LB_ADDSTRING	
           wParam:	0			
           lParam:  szString		
         Описание:  Добавить в список строку szString. Если свойство Sort у 
                    списка выключено, то строка будет добавлена в конец списка. 
                    Если это свойство включено, то после добавления строки 
                    производится сортировка списка

    Код сообщения:	LB_FINDSTRING	
           wParam:	iStart		
           lParam:	szString		
         Описание:  Найти строку, начинающуюся префиксом szString. Поиск 
                    начинается с элемента с индексом iStart + 1. 
                    Если wParam равен -1, то поиск начинается с начала списка. 
                    SendMessage возвращает индекс найденной строки или LB_ERR, 
                    если поиск завершился неуспешно

    Код сообщения:	LB_GETCURSEL
           wParam:	0		
           lParam:	0		
         Описание:  Получить индекс текущего выбранного элемента или LB_ERR, 
                    если такого элемента нет (только для списков с единичным выбором)
                

    Код сообщения:	LB_GETSELCOUNT
           wParam:	0		
           lParam:	0		
         Описание:	Получить количество выбранных элементов (для списка с 
                    множественным выбором)

    Код сообщения:	LB_GETSELITEMS
           wParam:	nMax		
           lParam:	pBuf		
         Описание:	Заполнить буфер pBuf массивом индексов выделенных элементов 
                    для списка с множественным выбором. Параметр nМах задает 
                    максимальное количество таких элементов

    Код сообщения:	LB_INSERTSTRING
           wParam:	iIndex		
           lParam:	szString		
         Описание:	Вставить строку szString после строки с индексом iIndex. 
                    Применяется для списка с выключенным свойством Sort

    Код сообщения:	LB_SELECTSTRING
           wParam:	iStart		
           lParam:	szString		
         Описание:	Аналогично сообщению LB_FINDSTRING, но дополнительно 
                    выделяется найденная строка

    Код сообщения:	LB_SETSEL
           wParam:	wParam		
           lParam:	iIndex		
         Описание:	Выбрать элемент с индексом iIndex (в списке с множественным 
                    выбором). Если wParam равен TRUE, элемент выбирается и 
                    выделяется,если FALSE — выбор отменяется. Если lParam 
                    равен -1, то операция применяется ко всем элементам списка
        
    Код сообщения:	LB_GETTEXT
           wParam:	iIndex		
           lParam:	szString		
         Описание:	Скопировать строку с индексом iIndex в буфер szString
       
    Код сообщения:	LB_DELETESTRING
           wParam:	iIndex		
           lParam:	0		
         Описание:	Удалить строку с индексом iIndex.
        
    Код сообщения:	LB_GETCOUNT
           wParam:	0		
           lParam:	0		
         Описание:	Получить количество элементов в списке
        
    Код сообщения:	LB_GETTEXTLEN
           wParam:	iIndex		
           lParam:	0		
         Описание:	Получить длину строки с индексом iIndex

    Код сообщения:	LB_RESETCONTENT
           wParam:	0		
           lParam:	0		
         Описание:	Удалить все элементы из списка
                
    Код сообщения:	LB_SETCURSEL
           wParam:	iIndex		
           lParam:	0		
         Описание:	Выбрать элемент с индексом iIndex (в списке с единичным 
                    выбором)
        
    Макросы для работы со списками:
        https://msdn.microsoft.com/en-us/library/windows/desktop/ff485966(v=vs.85).aspx
*/

// Уведомления списка
/*
    При воздействии на List Box (например, при выборе элемента списка), 
    в диалоговую процедуру DlgProc поступает сообщение WM_COMMAND, в 
    котором  LOWORD (wParam) содержит идентификатор списка, HIWORD (wParam) 
    содержит код уведомления (например, LBN_SELCHANGE), а lParam – 
    дескриптор списка.

    Список всех уведомлений:
    https://msdn.microsoft.com/en-us/library/windows/desktop/bb775146(v=vs.85).aspx#Notifications
    
    Некоторые из кодов уведомления от списка:
    
    LBN_SETFOCUS	Окно получило фокус ввода
    LBN_KILLFOCUS	Окно потеряло фокус ввода
    LBN_SELCHANGE	Текущий выбор был изменен (свойство Notify должно 
                    иметь значение True)
    LBN_DBLCLK		На данном пункте списка был двойной щелчок мыши 
                    (свойство Notify должно иметь значение True)
    LBN_ERRSPACE	Превышен размер памяти, отведенный для списка
*/

// Элемент управления «комбинированный список» (Combo Box)
/*
    Комбинированный список (Combo Box) является комбинацией списка 
    и текстового поля ввода.

    Обзор:
        https://msdn.microsoft.com/en-us/library/windows/desktop/bb775791(v=vs.85).aspx

    Многие свойства Combo Box аналогичны свойствам элемента управления 
    List Box. Но есть и некоторые различия. В частности, стиль 
    комбинированного списка задаётся свойством Туре, которое принимает 
    одно из следующих значений:	
        Simple (CBS_SIMPLE), 
        Dropdown (CBS_DROPDOWN), 
        Drop List (CBS_DROPDOWNLIST)

    Создание комбинированного списка: класс COMBOBOX

    CreateWindowEx(WS_EX_DLGMODALFRAME, 
                   TEXT("COMBOBOX"), 0,
                   WS_CHILD | WS_VISIBLE | CBS_SORT | CBS_DROPDOWNLIST,
                   LEFT, TOP, WIDTH, HEIGHT, 
                   hWnd, 
                   0, 
                   hInstance, 
                   0);
    Все стили:
        https://msdn.microsoft.com/en-us/library/windows/desktop/bb775796(v=vs.85).aspx


*/

// Сообщения комбинированных списков
/*
    Обмен сообщениями с комбинированным списком во многом похож на обмен  
    сообщениями с элементами управления Edit Box и List Box. 
    При этом идентификаторы сообщений, отправляемых элементу управления 
    Combo Box, начинаются с префикса СВ_, а идентификаторы уведомительных 
    сообщений, посылаемых от Combo Box своему родительскому окну, имеют 
    префикс CBN_.

    Сравнение сообщений Edit Control, List Box и Combo Box
    ========================== ===============================
        Код сообщения для
    Edit Control или List Box	Код сообщения для Combo Box
    ========================== ===============================
        EM_GETSEL						CB_GETEDITSEL
    -------------------------- -------------------------------
        EM_SETSEL						CB_SETEDITSEL
    -------------------------- -------------------------------
        LB_ADDSTRING					CB_ADDSTRING
    -------------------------- -------------------------------
        LB_DELETESTRING					CB_DELETESTRING
    -------------------------- -------------------------------
        LB_GETCOUNT						CB_GETCOUNT
    -------------------------- -------------------------------
        LB_GETCURSEL					CB_GETCURSEL
    -------------------------- -------------------------------
        LB_GETTEXT						CB_GETLBTEXT
    -------------------------- -------------------------------
        LB_SETCURSEL					CB_SETCURSEL
    -------------------------- -------------------------------


    Сравнительный анализ кодов уведомлений.
    ========================== ===============================
        Код уведомления для
    Edit Control или List Box		Код уведомления для Combo Box
    ========================== ===============================
    EN_SETFOCUS, LBN_SETFOCUS			CBN_SETFOCUS
    -------------------------- -------------------------------
    EN_KILLFOCUS, LBN_KILLFOCUS			CBN_KILLFOCUS
    -------------------------- -------------------------------
    EN_UPDATE							CBN_EDITUPDATE
    -------------------------- -------------------------------
    EN_CHANGE							CBN_EDITCHANGE
    -------------------------- -------------------------------
    EN_ERRSPACE, LBN_ERRSPACE			CBN_ERRSPACE
    -------------------------- -------------------------------
    LBN_SELCHANGE						CBN_SELCHANGE
    -------------------------- -------------------------------

    Макросы:
    https://msdn.microsoft.com/en-us/library/windows/desktop/bb775792(v=vs.85).aspx#Macros
*/


std::string drive_type(LPCTSTR type)
{
    std::string str_type;
    switch (GetDriveType(type))
    {
    case DRIVE_NO_ROOT_DIR:
        str_type = "NO ROOT DIR";
        break;
    case DRIVE_REMOVABLE:
        str_type = "REMOVABLE";
        break;
    case DRIVE_FIXED:
        str_type = "FIXEDR";
        break;
    case DRIVE_REMOTE:
        str_type = "REMOTE";
        break;
    case DRIVE_CDROM:
        str_type = "CDROM";
        break;
    case DRIVE_RAMDISK:
        str_type = "RAMDISK";
        break;
    case DRIVE_UNKNOWN:
    default:
        str_type = "UNKNOWN";
    }
    return str_type;
}

void ex()
{
    /*
    Примеры http://www.softzenware.com/visual/visual24.html
            https://shinigamiblog.wordpress.com/2011/02/27/getlogicaldrivestrings-%D1%87%D1%82%D0%BE-%D1%8D%D1%82%D0%BE-%D0%B8-%D1%81%D0%BE%D0%B1%D1%81%D0%BD%D0%B0-%D0%B7%D0%B0%D1%87%D0%B5%D0%BC/
    */
    /*
        Функция GetLogicalDrives возвращает битовую маску логических дисков,
        которые доступны в данный момент. При этом каждый бит маски 
        представляет собой конкретный диск. Если бит установлен, то 
        логический диск доступен, в противном случае бит будет сброшен. 
        Бит 0 соответствует диску A, бит 1 – диску B, бит 2 – диску С и т.д

        https://msdn.microsoft.com/en-us/library/windows/desktop/aa364972(v=vs.85).aspx
    */
    DWORD drivers = GetLogicalDrives();
    std::vector<std::string> strdrivers;
    std::bitset<26> drivers_map = drivers;
    std::cout << drivers_map << std::endl;
    for (int i = 0; i < 26; i++) {
        if ((drivers >> i) & 0x00000001)
        {
            char ch[2] = { 'A' + i, '\0' };
            strdrivers.push_back(std::string(ch) + std::string(":\\"));			
        }
    }

    for (auto drive : strdrivers)
    {

        /*
        Функция GetDriveType возвращает тип накопителя по заданному имени
        корневого пути (например, “C:\\”).

        https://msdn.microsoft.com/en-us/library/windows/desktop/aa364939(v=vs.85).aspx
        */
        std::cout << drive << " " << drive_type(LPCTSTR(drive.c_str())) << std::endl;
    }

    /*
        Функция GetLogicalDriveStrings заполняет буфер строками, которые 
        определяют действительные логические диски в системе.

        https://msdn.microsoft.com/en-us/library/windows/desktop/aa364975(v=vs.85).aspx
    */
    DWORD dwSize = GetLogicalDriveStrings(0, NULL);	//возвращает длину строки c дисками, поэтому вызовем ее с нулем	
    TCHAR* szDrives = new TCHAR[dwSize];
    GetLogicalDriveStrings(dwSize, szDrives);
    std::wcout << szDrives << std::endl;
}

int main()
{
    ///ex();
    return 0;
}

