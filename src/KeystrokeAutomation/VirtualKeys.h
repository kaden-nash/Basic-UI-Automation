#include <windows.h>
#include <string>
#include <map>

namespace KeystrokeAutomation {
    using std::string;

    WORD getVirtualKey(const string& alias);
    bool isMouseClickRequest(const string& alias);
}

