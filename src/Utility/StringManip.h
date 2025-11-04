#include <string>
#include <vector>

namespace Utility {
    using std::string;
    using std::vector;

    string toLower(const string& s);
    string stripWhitespace(const string& str);
    vector<string> split(const string& s, const string& delim);
}