#include "..\..\include\Mouse.h"
#include <iostream>

#include <windows.h>
#include <winuser.h>

namespace KeystrokeAutomation::Mouse {
    using std::cout;
    using std::endl;

    /*
    Moves mouse to specified (x,y) location.
    --param: relative x position, relative y position
    --return: none
    */ 
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

    /*
    Retrieves a structure containing the exact relative position of the cursor.
    --param: none
    --return: a POINT structure containing the relative position of the mouse.
    */
    POINT getCursorPos()
    {
        POINT p;
        GetCursorPos(&p);
        return p;
    }
}