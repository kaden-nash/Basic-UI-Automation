#include <windows.h>
#include <string>
#include <map>

namespace KeystrokeAutomation::Utility::VirtualKeys {
    using std::string;

    WORD getVirtualKey(const string& alias);
    bool isMouseRequest(const string& alias);
}

