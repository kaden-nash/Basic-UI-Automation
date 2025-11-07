#include "..\..\include\ButtonPress.h"
#include "ButtonPressHelpers.h"
#include <windows.h>
#include <vector>
#include <iostream>

namespace KeystrokeAutomation {
    using std::vector;
    using std::string;
    using KeystrokeAutomation::getINPUTs;
    using KeystrokeAutomation::throwSendInputsError;

    void sendInputs(const string& input) {
        vector<INPUT> inputs = getINPUTs(input);
        UINT sent = SendInput(inputs.size(), inputs.data(), sizeof(INPUT));
        if (sent < inputs.size()) {
            throwSendInputsError(sent, inputs.size());
        }
    }
}