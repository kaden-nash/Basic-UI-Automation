#include <string>
#include <vector>
#include <windows.h>

namespace KeystrokeAutomation {
    using std::vector;
    using std::string;

    vector<INPUT> getINPUTs(const string& inputStr);
    vector<INPUT> createINPUTs(vector<string>& splitInput);
    vector<INPUT> createINPUTForMouseClick(const string& alias);
    vector<INPUT> createINPUTForMouseMove(const string& coords);
    vector<INPUT> createINPUTForUnicodePrint(const string& letters);
    vector<INPUT> createINPUTForCompoundPress(const string& command);
    vector<INPUT> createINPUTForLiteralPress(const string& alias);
    vector<INPUT> createINPUTForHoldingPresses(vector<string>& aliases);
    WORD attemptToGetVKey(const string& alias);
    string removeLeadingAndTrailingChars(const string& str);
    bool isCompoundPress(const string& command);
    bool isUnicodePrint(const string& str);
    bool isMouseMoveRequest(const string& str);
    void throwSendInputsError(int inputsSent, int desiredInputsSent);
    void throwInvalidArgumentErrorToUser(const string& command);
}