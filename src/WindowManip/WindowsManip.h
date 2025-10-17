#pragma once

#include <windows.h>
#include <winuser.h>

#include "..\..\include\windowInfo_s.h"

namespace WindowsManip {
    /*
    Enumerates top level windows open on computer, not including any with empty titles or "MSCTFIME UI" or "Default IME".
    --param: takes a windowInfo_s struct object reference where info will be stored. 
    --return: none
    */
    void getWindows(windowInfo_s *info);

    /*
    Gets child windows of a specific parent
    */
    void getChildWindows(windowInfo_s *childInfo, HWND hwnd);

}
