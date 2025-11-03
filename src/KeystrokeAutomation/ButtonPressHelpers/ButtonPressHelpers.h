#include <string>
#include <vector>
#include <winuser.h>

namespace KeystrokeAutomation::ButtonPressHelpers {
    using std::vector;
    using std::string;

    void throwSendInputsError(int inputsSent, int desiredInputsSent);
    vector<INPUT> getINPUTs(const string& inputStr);
    vector<INPUT> createINPUTs(vector<string>& splitInput);
    vector<INPUT> createINPUTForMouseClick(const string& alias);
    vector<INPUT> createINPUTForMouseMove(const string& coords);
    vector<INPUT> createINPUTForPrintableVKeys(const string& letters);
    vector<INPUT> createINPUTForCompoundCommand(const string& command);
    vector<INPUT> createINPUTForUnprintableVKey(const string& alias);
    vector<INPUT> createINPUTForHoldingPresses(vector<string>& aliases);
    WORD attemptToGetVKey(const string& alias);
    string removeLeadingAndTrailingChars(const string& str);
    bool isCompoundCommand(const string& command);
    bool isPrintableVKey(const string& str);
    bool isMouseMoveRequest(const string& str);
}