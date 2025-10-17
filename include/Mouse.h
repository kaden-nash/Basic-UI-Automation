#pragma once

#include <windows.h>

namespace KeystrokeAutomation::Mouse {
    /*
    Moves mouse to specified (x,y) location.
    --param: relative x position, relative y position
    --return: none
    */ 
    int moveMouse(int x, int y);

    /*
    Retrieves a structure containing the exact relative position of the cursor.
    --param: none
    --return: a POINT structure containing the relative position of the mouse.
    */
    POINT getCursorPos();
}