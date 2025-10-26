#include "VirtualKeys.h"

#include <windows.h>
#include <string>
#include <map>
#include <stdexcept>
#include <iostream>

namespace KeystrokeAutomation::Utility::VirtualKeys {
    using std::map;
    using std::string;
    using std::endl;
    using std::cout;

    WORD getVirtualKey(const string& alias) {
        try {
            virtualKeyMap.at(alias);
            return virtualKeyMap[alias];
        } catch (const std::out_of_range& e) {
            throw std::invalid_argument("No entry matching key found in virtualKeyMap.");
        }
    }

    bool isMouseRequest(const string& alias) {
        WORD vKey = getVirtualKey(alias);
        return vKey == VK_LBUTTON || vKey == VK_RBUTTON || vKey == VK_MBUTTON;
    }

}