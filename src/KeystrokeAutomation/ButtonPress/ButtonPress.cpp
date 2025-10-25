#include "..\..\..\include\ButtonPress.h"
#include "..\ButtonPressHelpers\ButtonPressHelpers.h"
#include <windows.h>
#include <vector>
#include <iostream>

namespace KeystrokeAutomation::ButtonPress {
    using std::vector;
    using std::string;
    using ButtonPressHelpers::getINPUTs;
    using ButtonPressHelpers::throwSendInputsError;

    /*
    Performs a set of keyboard/mouse events
    --param: takes in a string that adheres to InputSpecifications.txt and simulates the button presses within. 
    --return: N/A
    */
    void sendInputs(const string& input) {
        vector<INPUT> inputs = getINPUTs(input);
        UINT sent = SendInput(inputs.size(), inputs.data(), sizeof(INPUT));
        if (sent < inputs.size()) {
            throwSendInputsError(sent, inputs.size());
        }
    }
}