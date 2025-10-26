#include "catch.hpp"
#include "..\src\Utility\StringManip\StringManip.h"
#include <string>

TEST_CASE("toLower") {
    std::string testStr = "THE QUICK BROWN FOX jumped over the lazy dog.";
    std::string resStr = "the quick brown fox jumped over the lazy dog.";

    SECTION("empty string") {
        REQUIRE(Utility::StringManip::toLower("") == "");
    }

    SECTION("filled string") {
        REQUIRE(Utility::StringManip::toLower(testStr) == resStr);
    }
}