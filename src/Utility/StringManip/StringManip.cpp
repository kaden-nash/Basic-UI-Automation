#include "StringManip.h"
#include <string>
#include <vector>
#include <algorithm>

namespace Utility::StringManip {
    using std::string;
    using std::vector;

    string toLower(const string& s) {
        string copy = s;
        std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
        return copy;
    }

    string stripWhitespace(const string& str) {
        string result;
        for (char c : str) {
            if (!std::isspace(c)) {
                result += c;
            }
        }
        return result;
    }

    vector<string> split(const string& s, const string& delim) {
        vector<string> result;
        size_t start = 0;
        size_t end = s.find(delim);

        while (end != string::npos)
        {
            result.push_back(s.substr(start, end - start));
            start = end + delim.length();
            end = s.find(delim, start);
        }
        
        result.push_back(s.substr(start));
        return result;
    }
    }