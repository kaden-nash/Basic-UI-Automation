#include <windows.h>
#include <string>
#include <map>

namespace KeystrokeAutomation::Utility {
    std::map<std::string, WORD> virtualKeyMap;

    WORD getVirtualKey(string& alias);
}

