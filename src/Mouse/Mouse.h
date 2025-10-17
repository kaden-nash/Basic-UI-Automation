#pragma once

#include <windows.h>

namespace Mouse {
    int moveMouse(int x, int y);
    POINT getCursorPtr();
}