#pragma once

#include <windows.h>
#include <vector>

namespace KeystrokeAutomation::Keyboard {
    using std::vector;
    
    void kEvent(vector<WORD> input);
    INPUT kEventPressHelper(INPUT inputStruct, WORD input);
    INPUT kEventUnpressHelper(INPUT inputStruct, WORD input);
    int getInputError(UINT sent, int sizeInput); 
}