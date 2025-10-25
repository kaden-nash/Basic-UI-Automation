#include "..\Utility\VirtualKeys\VirtualKeys.h"
#include "..\..\Utility\StringManip\StringManip.h"
#include <windows.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>

namespace KeystrokeAutomation::ButtonPressHelpers {
    using std::cout;
    using std::endl;
    using std::vector;
    using std::string;
    using Utility::VirtualKeys::getVirtualKey;
    using Utility::VirtualKeys::isMouseRequest;
    using ::Utility::StringManip::stripWhitespace;
    using ::Utility::StringManip::toLower;
    using ::Utility::StringManip::split;

    vector<INPUT> getINPUTs(const string& inputStr) {
        string strippedInput = stripWhitespace(inputStr);
        vector<string> splitInput = split(strippedInput, ",");
        return createINPUTs(splitInput);
    }

    void throwSendInputsError(int inputsSent, int desiredInputsSent) {
        string errorMsg = "";
        errorMsg += "Not all inputs were sent (";
        errorMsg += desiredInputsSent;
        errorMsg += "/";
        errorMsg += inputsSent;
        errorMsg += ")";
        throw std::runtime_error(errorMsg);
    }

    vector<INPUT> createINPUTs(vector<string>& splitInput) {
        vector<INPUT> inputs = {};
        vector<INPUT> newInputs = {};
        for (int i = 0; i < splitInput.size(); ++i) {
            if (isMouseRequest(splitInput[i])) {
                newInputs = createINPUTForMouse(splitInput[i]);
            } else if (isPrintableVKey(splitInput[i])) {
                newInputs = createINPUTForPrintableVKeys(splitInput[i]);
            } else if (isCompoundCommand(splitInput[i])) {
                newInputs = createINPUTForCompoundCommand(splitInput[i]);
            } else {
                newInputs = createINPUTForUnprintableVKey(splitInput[i]);
            }

            inputs.insert(inputs.end(), newInputs.begin(), newInputs.end());
        }
        return inputs;
    }

    bool isCompoundCommand(const string& command) {
        return command.find("|") != string::npos;
    }

    bool isPrintableVKey(const string& str) {
        if (str[0] == '\"' && str[str.size() - 1] == '\"') {
            return true;
        }

        return false;
    }

    vector<INPUT> createINPUTForMouse(const string& alias) {
        WORD vKey = attemptToGetVKey(alias);
        vector<INPUT> inputs = {};
        switch(vKey) {
            case VK_LBUTTON:
                inputs.push_back(createINPUTForLeftClick());
                inputs.push_back(createINPUTForLeftRelease());
                break;
            case VK_RBUTTON:
                inputs.push_back(createINPUTForRightClick());
                inputs.push_back(createINPUTForRightRelease());
                break;
            case VK_MBUTTON:
                inputs.push_back(createINPUTForMiddleClick());
                inputs.push_back(createINPUTForMiddleRelease());
                break;
        }
        return inputs;
    }

    vector<INPUT> createINPUTForCompoundCommand(const string& command) {
        vector<INPUT> inputs = {};
        vector<string> splitCommand = split(command, "|");
        vector<INPUT> newInputs = createINPUTForHoldingPresses(splitCommand);
        return inputs;
    }

    vector<INPUT> createINPUTForHoldingPresses(vector<string>& aliases) {
        vector<INPUT> input = {};
        WORD vKey;
        for(int i = 0; i < aliases.size(); ++i) {
            vKey = attemptToGetVKey(aliases[i]);
            input.push_back(createINPUTForPress(vKey));
        }

        for(int i = 0; i < aliases.size(); ++i) {
            input.push_back(createINPUTForRelease(vKey));
        }

        return input;
    }

    WORD attemptToGetVKey(const string& alias) {
        string lower = toLower(alias);

        WORD vKey;
        try {
            vKey = getVirtualKey(lower);
        } catch (const std::invalid_argument) {
            cout << "Invalid input: " << alias << " - terminating.\n";
            exit(0);
        }

        return vKey;
    }

    string removeLeadingAndTrailingQuotations(const string& str) {
        string copy = str;
        copy.erase(0, 1);
        copy.erase(copy.size()-1, 1);
        return copy;
    }

    vector<INPUT> createINPUTForPrintableVKeys(const string& letters) {
        string strippedLetters = removeLeadingAndTrailingQuotations(letters);
        vector<INPUT> inputs = {};
        vector<INPUT> inputs = {};
        for (int i = 0; i < strippedLetters.size(); ++i) {
            inputs.push_back(createINPUTForPress(strippedLetters[i]));
            inputs.push_back(createINPUTForRelease(strippedLetters[i]));
        }
        return inputs;
    }

    vector<INPUT> createINPUTForUnprintableVKey(const string& alias) {
        vector<INPUT> inputs = {};
        WORD vKey = attemptToGetVKey(alias);
        inputs.push_back(createINPUTForPress(vKey));
        inputs.push_back(createINPUTForRelease(vKey));
        return inputs;
    }

    namespace {
        INPUT createINPUTForLeftClick() {
            INPUT input = {};
            input.type = INPUT_MOUSE;
            input.ki.dwFlags = MOUSEEVENTF_LEFTDOWN;
            return input;
        }

        INPUT createINPUTForLeftRelease() {
            INPUT input = {};
            input.type = INPUT_MOUSE;
            input.ki.dwFlags = MOUSEEVENTF_LEFTUP;
            return input;
        }

        INPUT createINPUTForRightClick() {
            INPUT input = {};
            input.type = INPUT_MOUSE;
            input.ki.dwFlags = MOUSEEVENTF_RIGHTDOWN;
            return input;
        }

        INPUT createINPUTForRightRelease() {
            INPUT input = {};
            input.type = INPUT_MOUSE;
            input.ki.dwFlags = MOUSEEVENTF_RIGHTUP;
            return input;
        }

        INPUT createINPUTForMiddleClick() {
            INPUT input = {};
            input.type = INPUT_MOUSE;
            input.ki.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
            return input;
        }

        INPUT createINPUTForMiddleRelease() {
            INPUT input = {};
            input.type = INPUT_MOUSE;
            input.ki.dwFlags = MOUSEEVENTF_MIDDLEUP;
            return input;
        }

        INPUT createINPUTForPress(char ltr) {
            INPUT input = {};
            input.type = INPUT_KEYBOARD;
            input.ki.wScan = ltr;
            input.ki.dwFlags = KEYEVENTF_UNICODE;
            return input;
        }

        INPUT createINPUTForPress(WORD vKey) {
            INPUT input = {};
            input.type = INPUT_KEYBOARD;
            input.ki.wScan = vKey;
            input.ki.dwFlags = 0;
            return input;
        }

        INPUT createINPUTForRelease(char ltr) {
            INPUT input = {};
            input.type = INPUT_KEYBOARD;
            input.ki.wScan = ltr;
            input.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
            return input;
        }

        INPUT createINPUTForRelease(WORD vKey) {
            INPUT input = {};
            input.type = INPUT_KEYBOARD;
            input.ki.wScan = vKey;
            input.ki.dwFlags = KEYEVENTF_KEYUP;
            return input;
        }
    }
}