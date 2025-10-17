#pragma once

#include <windows.h>

namespace KeystrokeAutomation::Mouse {
    int moveMouse(int x, int y);
    POINT getCursorPos();
}