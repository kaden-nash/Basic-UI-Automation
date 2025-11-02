#include <string>
#include <vector>
#include <winuser.h>

namespace KeystrokeAutomation::ButtonPressHelpers {
    using std::vector;
    using std::string;

    vector<INPUT> getINPUTs(const string& inputStr);
    void throwSendInputsError(int inputsSent, int desiredInputsSent);
    vector<INPUT> createINPUTs(vector<string>& splitInput);
    bool isCompoundCommand(const string& command);
    bool isPrintableVKey(const string& str);
    vector<INPUT> createINPUTForMouse(const string& alias);
    vector<INPUT> createINPUTForCompoundCommand(const string& command);
    vector<INPUT> createINPUTForHoldingPresses(vector<string>& aliases);
    WORD attemptToGetVKey(const string& alias);
    string removeLeadingAndTrailingChars(const string& str);
    vector<INPUT> createINPUTForPrintableVKeys(const string& letters);
    vector<INPUT> createINPUTForUnprintableVKey(const string& alias);
}