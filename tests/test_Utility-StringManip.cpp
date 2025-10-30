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

TEST_CASE("stripWhitespace") {
    std::string testStr = "THE QUICK BROWN FOX jumped over the lazy dog.";
    std::string resStr = "THEQUICKBROWNFOXjumpedoverthelazydog.";

    SECTION("empty string") {
        REQUIRE(Utility::StringManip::stripWhitespace("") == "");
    }

    SECTION("filled string") {
        REQUIRE(Utility::StringManip::stripWhitespace(testStr) == resStr);
    }
}

TEST_CASE("split") {
    std::string testStr = "THE QUICK BROWN FOX jumped over the lazy dog.";
    std::vector<std::string> vec1 = {""};
    std::vector<std::string> vec2 = {"THE", "QUICK", "BROWN", "FOX", "jumped", "over", "the", "lazy", "dog."};

    SECTION("empty string") {
        REQUIRE(Utility::StringManip::split("", "") == vec1);
    }

    SECTION("filled string") {
        REQUIRE(Utility::StringManip::split(testStr, " ") == vec2);
    }
}