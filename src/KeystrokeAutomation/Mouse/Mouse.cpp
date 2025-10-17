#include "..\..\..\include\Mouse.h"
#include <iostream>

#include <windows.h>
#include <winuser.h>

namespace KeystrokeAutomation::Mouse {
    using std::cout;
    using std::endl;

    int moveMouse(int x, int y)
    {
        UINT successfulInputs = SetCursorPos(x, y); // remember coords are relative to top left corner

        if (successfulInputs == 0)
        {
            cout << "Mouse movement was not successful: " << GetLastError() << endl;
            return 0;
        }

        return 1;
    }

    POINT getCursorPos()
    {
        POINT p;
        GetCursorPos(&p);
        return p;
    }
}