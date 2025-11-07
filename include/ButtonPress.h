#pragma once

#include <string>

namespace KeystrokeAutomation {\
    /*
    Performs a set of keyboard/mouse events
    --param: takes in a string that adheres to InputSpecifications.txt and simulates the button presses within. 
    --return: N/A
    */
    void sendInputs(const std::string& input);
}