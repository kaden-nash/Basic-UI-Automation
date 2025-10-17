#pragma once

#include <vector>
#include <string>
#include <windows.h>
#include <winuser.h>

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
}