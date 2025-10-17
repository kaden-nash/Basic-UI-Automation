#pragma once

#include <windows.h>
#include <winuser.h>
#include <vector>
#include <string>

namespace WindowsManip {
    using std::vector;
    using std::string;

    /*
    A stupid replacement for a dataclass before I knew what a dataclass was
    */
    struct windowInfo_s {
        vector<HWND> windowHandles;
        vector<string> windowTitles;
        vector<WINDOWINFO> windowInfo;
        int sizeOfVectors = 0;
    };

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
