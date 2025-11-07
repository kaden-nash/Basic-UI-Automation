#include "VirtualKeys.h"
#include "..\Utility\StringManip.h"
#include "ButtonPressHelpers.h"
#include <windows.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <regex>

namespace KeystrokeAutomation {
    using std::cout;
    using std::endl;
    using std::vector;
    using std::string;
    using KeystrokeAutomation::getVirtualKey;
    using KeystrokeAutomation::isMouseClickRequest;
    using ::Utility::stripWhitespace;
    using ::Utility::toLower;
    using ::Utility::split;

    namespace {
        void isValidMouseMoveRange(int x, int y) {
            std::stringstream errorMsg;
            if (x > 65335 || x < 0 || y > 65535 || y < 0) {
                errorMsg << "Mouse movement range must be between 0 and 65335 for both axes, was (" << x << ", " << y << ")"; 
                throw std::invalid_argument(errorMsg.str());
            }
        }

        INPUT populateINPUTForMouseMove(int x, int y) {
            isValidMouseMoveRange(x, y);
            INPUT input = {};
            input.type = INPUT_MOUSE;
            input.mi.dx = x;
            input.mi.dy = y;
            input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
            return input;
        }

        INPUT populateINPUTForLeftClick() {
            INPUT input = {};
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            return input;
        }

        INPUT populateINPUTForLeftRelease() {
            INPUT input = {};
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
            return input;
        }

        INPUT populateINPUTForRightClick() {
            INPUT input = {};
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
            return input;
        }

        INPUT populateINPUTForRightRelease() {
            INPUT input = {};
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
            return input;
        }

        INPUT populateINPUTForMiddleClick() {
            INPUT input = {};
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
            return input;
        }

        INPUT populateINPUTForMiddleRelease() {
            INPUT input = {};
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
            return input;
        }

        INPUT populateINPUTForPress(char ltr) {
            INPUT input = {};
            input.type = INPUT_KEYBOARD;
            input.ki.wScan = ltr;
            input.ki.dwFlags = KEYEVENTF_UNICODE;
            return input;
        }

        INPUT populateINPUTForPress(WORD vKey) {
            INPUT input = {};
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = vKey;
            input.ki.dwFlags = 0;
            return input;
        }

        INPUT populateINPUTForRelease(char ltr) {
            INPUT input = {};
            input.type = INPUT_KEYBOARD;
            input.ki.wScan = ltr;
            input.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
            return input;
        }

        INPUT populateINPUTForRelease(WORD vKey) {
            INPUT input = {};
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = vKey;
            input.ki.dwFlags = KEYEVENTF_KEYUP;
            return input;
        }
    }

    vector<INPUT> getINPUTs(const string& inputStr) {
        string strippedInput = stripWhitespace(inputStr);
        vector<string> splitInput = split(strippedInput, ",");
        return createINPUTs(splitInput);
    }

    vector<INPUT> createINPUTs(vector<string>& splitInput) {
        vector<INPUT> inputs = {};
        vector<INPUT> newInputs = {};
        for (int i = 0; i < splitInput.size(); ++i) {
            if (isMouseClickRequest(splitInput[i])) {
                newInputs = createINPUTForMouseClick(splitInput[i]);
            } else if (isMouseMoveRequest(splitInput[i])) {
                newInputs = createINPUTForMouseMove(splitInput[i]);
            } else if (isUnicodePrintRequest(splitInput[i])) {
                newInputs = createINPUTForUnicodePrint(splitInput[i]);
            } else if (isCompoundPress(splitInput[i])) {
                newInputs = createINPUTForCompoundPress(splitInput[i]);
            } else {
                newInputs = createINPUTForLiteralPress(splitInput[i]);
            }

            inputs.insert(inputs.end(), newInputs.begin(), newInputs.end());
        }
        return inputs;
    }

    vector<INPUT> createINPUTForMouseClick(const string& alias) {
        WORD vKey = attemptToGetVKey(alias);
        vector<INPUT> inputs = {};
        switch(vKey) {
            case VK_LBUTTON:
                inputs.push_back(populateINPUTForLeftClick());
                inputs.push_back(populateINPUTForLeftRelease());
                break;
            case VK_RBUTTON:
                inputs.push_back(populateINPUTForRightClick());
                inputs.push_back(populateINPUTForRightRelease());
                break;
            case VK_MBUTTON:
                inputs.push_back(populateINPUTForMiddleClick());
                inputs.push_back(populateINPUTForMiddleRelease());
                break;
        }
        return inputs;
    }

    vector<INPUT> createINPUTForMouseMove(const string& coords) {
        string noBrackets = removeLeadingAndTrailingChars(coords);
        vector<string> coords_vec = split(noBrackets, "|");
        int x = std::stoi(coords_vec[0]);
        int y = std::stoi(coords_vec[1]);
        vector<INPUT> input = {};
        input.push_back(populateINPUTForMouseMove(x, y));
        return input;
    }

    vector<INPUT> createINPUTForUnicodePrint(const string& letters) {
        string strippedLetters = removeLeadingAndTrailingChars(letters);
        vector<INPUT> inputs = {};
        for (int i = 0; i < strippedLetters.size(); ++i) {
            inputs.push_back(populateINPUTForPress(strippedLetters[i]));
            inputs.push_back(populateINPUTForRelease(strippedLetters[i]));
        }
        return inputs;
    }

    vector<INPUT> createINPUTForCompoundPress(const string& command) {
        vector<string> splitCommand = split(command, "|");
        vector<INPUT> inputs;
        try {
            inputs = createINPUTForCompoundPressHelper(splitCommand);
        } catch (std::invalid_argument& e) {
            throwInvalidArgumentErrorToUser(command);
        }
        return inputs;
    }

    vector<INPUT> createINPUTForCompoundPressHelper(vector<string>& aliases) {
        vector<INPUT> input = {};
        WORD vKey;
        for(int i = 0; i < aliases.size(); ++i) {
            vKey = attemptToGetVKey(aliases[i]);
            input.push_back(populateINPUTForPress(vKey));
        }

        for(int i = 0; i < aliases.size(); ++i) {
            vKey = attemptToGetVKey(aliases[i]);
            input.push_back(populateINPUTForRelease(vKey));
        }

        return input;
    }

    vector<INPUT> createINPUTForLiteralPress(const string& alias) {
        vector<INPUT> inputs = {};
        WORD vKey;
        try {
            vKey = attemptToGetVKey(alias);
        } catch (std::invalid_argument& e) {
            throwInvalidArgumentErrorToUser(alias);
        }
        inputs.push_back(populateINPUTForPress(vKey));
        inputs.push_back(populateINPUTForRelease(vKey));
        return inputs;
    }

    WORD attemptToGetVKey(const string& alias) {
        string lower = toLower(alias);
        WORD vKey = getVirtualKey(lower);
        return vKey;
    }

    string removeLeadingAndTrailingChars(const string& str) {
        string copy = str;
        copy.erase(0, 1);
        copy.erase(copy.size()-1, 1);
        return copy;
    }
    
    bool isCompoundPress(const string& command) {
        return command.find("|") != string::npos && !isMouseMoveRequest(command); 
    }

    bool isUnicodePrintRequest(const string& str) {
        return str[0] == '\"' && str[str.size() - 1] == '\"';
    }

    bool isMouseMoveRequest(const string& str) {
        std::regex movePattern(R"(^\((\d+(\.\d+)?)\|(\d+(\.\d+)?)\)$)");
        std::smatch matches;
        std::regex_match(str, matches, movePattern);
        int numMatchesExpected = 5;
        if(matches.size() != numMatchesExpected) {
            return false;
        } else {
            return true;
        }
    }

    void throwSendInputsError(int inputsSent, int desiredInputsSent) {
        std::stringstream errorMsg;
        errorMsg << "Not all inputs were sent (" << std::to_string(inputsSent) << "/" << std::to_string(desiredInputsSent) << ")";
        throw std::runtime_error(errorMsg.str());
    }

    void throwInvalidArgumentErrorToUser(const string& problematicStr) {
        string errorMsg = "Invalid keypress requested: ";
        errorMsg += problematicStr;
        std::throw_with_nested(std::invalid_argument(errorMsg));
    }
}