#include "catch.hpp"
#include "..\src\KeystrokeAutomation\ButtonPressHelpers.h"
#include "..\src\KeystrokeAutomation\VirtualKeys.h"
#include "..\src\Utility\StringManip.h"
#include "windows.h"

TEST_CASE("Error Handling", "[errors]") {
    
    SECTION("throwSendInputsError formats the message correctly") {
        REQUIRE_THROWS_WITH(
            KeystrokeAutomation::throwSendInputsError(5, 10), 
            "Not all inputs were sent (5/10)"
        );
    }
    
    SECTION("attemptToGetVKey finds valid keys") {
        REQUIRE(KeystrokeAutomation::attemptToGetVKey("lshift") == VK_LSHIFT);
        REQUIRE(KeystrokeAutomation::attemptToGetVKey("lSHIFT") == VK_LSHIFT); 
        REQUIRE(KeystrokeAutomation::attemptToGetVKey("lmouse") == VK_LBUTTON);
    }
}

TEST_CASE("Parsing Helper Functions", "[parser_helpers]") {

    SECTION("isCompoundPress identifies commands with a pipe") {
        REQUIRE(KeystrokeAutomation::isCompoundPress("ctrl|shift") == true);
        REQUIRE(KeystrokeAutomation::isCompoundPress("ctrl | shift") == true);
        REQUIRE(KeystrokeAutomation::isCompoundPress("ctrl") == false);
        REQUIRE(KeystrokeAutomation::isCompoundPress("ctrl|") == true);
        REQUIRE(KeystrokeAutomation::isCompoundPress("|ctrl") == true);
        REQUIRE(KeystrokeAutomation::isCompoundPress("") == false);
    }

    SECTION("isUnicodePrintRequest identifies quoted strings") {
        REQUIRE(KeystrokeAutomation::isUnicodePrintRequest("\"hello\"") == true);
        REQUIRE(KeystrokeAutomation::isUnicodePrintRequest("\"\"") == true);
        REQUIRE(KeystrokeAutomation::isUnicodePrintRequest("hello") == false);
        REQUIRE(KeystrokeAutomation::isUnicodePrintRequest("\"hello") == false);
        REQUIRE(KeystrokeAutomation::isUnicodePrintRequest("hello\"") == false);
        REQUIRE(KeystrokeAutomation::isUnicodePrintRequest("") == false);
    }

    SECTION("isMouseMoveRequest identifies strings matching (x|y) format") {
        REQUIRE(KeystrokeAutomation::isMouseMoveRequest("(3.445|3)") == true);
        REQUIRE(KeystrokeAutomation::isMouseMoveRequest("(3.445|3.455)") == true);
        REQUIRE(KeystrokeAutomation::isMouseMoveRequest("(|3)") == false);
        REQUIRE(KeystrokeAutomation::isMouseMoveRequest("(heafd|3)") == false);
        REQUIRE(KeystrokeAutomation::isMouseMoveRequest("") == false);
        REQUIRE(KeystrokeAutomation::isMouseMoveRequest("(3|)") == false);
        REQUIRE(KeystrokeAutomation::isMouseMoveRequest("|)") == false);
        REQUIRE(KeystrokeAutomation::isMouseMoveRequest("(|") == false);
    }

    SECTION("isMouseClickRequest identifies strings with key values matching mouse click options") {
        REQUIRE(KeystrokeAutomation::isMouseClickRequest("lmouse") == true);
        REQUIRE(KeystrokeAutomation::isMouseClickRequest("rmouse") == true);
        REQUIRE(KeystrokeAutomation::isMouseClickRequest("mmouse") == true);
        REQUIRE(KeystrokeAutomation::isMouseClickRequest("mouse") == false);
        REQUIRE(KeystrokeAutomation::isMouseClickRequest("") == false);
    }

    SECTION("removeLeadingAndTrailingChars strips outer quotes") {
        REQUIRE(KeystrokeAutomation::removeLeadingAndTrailingChars("\"hello\"") == "hello");
        REQUIRE(KeystrokeAutomation::removeLeadingAndTrailingChars("\"a\"") == "a");
        REQUIRE(KeystrokeAutomation::removeLeadingAndTrailingChars("\"\"") == "");
    }
}

TEST_CASE("Input Creation Logic", "[input_creation]") {

    SECTION("createINPUTForLiteralPress creates a press and release pair") {
        auto inputs = KeystrokeAutomation::createINPUTForLiteralPress("shift");
        REQUIRE(inputs.size() == 2);
        REQUIRE(inputs[0].type == INPUT_KEYBOARD); 
        REQUIRE(inputs[0].ki.wVk == VK_SHIFT);
        REQUIRE(inputs[1].type == INPUT_KEYBOARD); 
        REQUIRE(inputs[1].ki.wVk == VK_SHIFT);
    }

    SECTION("createINPUTForLiteralPress receives an invalid alias") {
        REQUIRE_THROWS_WITH(KeystrokeAutomation::createINPUTForLiteralPress("fead"), "Invalid keypress requested: fead");
    }

    SECTION("createINPUTForUnicodePrint creates pairs for each character") {
        auto inputs = KeystrokeAutomation::createINPUTForUnicodePrint("\"hi\"");
        REQUIRE(inputs.size() == 4);
        REQUIRE(inputs[0].ki.wScan == 'h');
        REQUIRE(inputs[1].ki.wScan == 'h');
        REQUIRE(inputs[2].ki.wScan == 'i');
        REQUIRE(inputs[3].ki.wScan == 'i');
        REQUIRE(inputs[0].type == INPUT_KEYBOARD);
        REQUIRE(inputs[1].type == INPUT_KEYBOARD); 
    }

    SECTION("createINPUTForMouseClick creates mouse and release pair") {
        auto inputs = KeystrokeAutomation::createINPUTForMouseClick("lmouse");
        REQUIRE(inputs.size() == 2);
        REQUIRE(inputs[0].type == INPUT_MOUSE); 
        REQUIRE(inputs[1].type == INPUT_MOUSE); 

        auto rInputs = KeystrokeAutomation::createINPUTForMouseClick("rmouse");
        REQUIRE(rInputs.size() == 2);
        REQUIRE(rInputs[0].type == INPUT_MOUSE); 
    }

    SECTION("createINPUTForMouseMove creates mouse movement INPUT") {
        auto inputs = KeystrokeAutomation::createINPUTForMouseMove("(100|100)");
        REQUIRE(inputs.size() == 1);
        REQUIRE(inputs[0].type == INPUT_MOUSE); 
        REQUIRE(inputs[0].mi.dx == 100); 
        REQUIRE(inputs[0].mi.dy == 100); 
        REQUIRE(inputs[0].mi.dwFlags == MOUSEEVENTF_ABSOLUTE); 

        REQUIRE_THROWS_WITH(KeystrokeAutomation::createINPUTForMouseMove("(0|-1)"), 
        "Mouse movement range must be between 0 and 65335 for both axes, was (0, -1)"
        );
    }

    SECTION("createINPUTForCompoundPressHelper") {
        std::vector<std::string> aliases = {"ctrl", "shift"};
        auto inputs = KeystrokeAutomation::createINPUTForCompoundPressHelper(aliases);
        
        REQUIRE(inputs.size() == 4);
        REQUIRE(inputs[0].type == INPUT_KEYBOARD);
        REQUIRE(inputs[0].ki.wVk == VK_CONTROL);
        REQUIRE(inputs[0].ki.dwFlags == 0);
        REQUIRE(inputs[1].type == INPUT_KEYBOARD);
        REQUIRE(inputs[1].ki.wVk == VK_SHIFT);
        REQUIRE(inputs[1].ki.dwFlags == 0);
        REQUIRE(inputs[2].type == INPUT_KEYBOARD);
        REQUIRE(inputs[2].ki.wVk == VK_CONTROL);
        REQUIRE(inputs[2].ki.dwFlags == KEYEVENTF_KEYUP);
        REQUIRE(inputs[3].type == INPUT_KEYBOARD);
        REQUIRE(inputs[3].ki.wVk == VK_SHIFT);
        REQUIRE(inputs[3].ki.dwFlags == KEYEVENTF_KEYUP);
    }
}

TEST_CASE("High-Level Parsing Pipeline", "[pipeline]") {
    
    SECTION("createINPUTs dispatches to correct creation functions") {
        std::vector<std::string> splitInput = {"lmouse", "\"hi\"", "shift"};
        auto inputs = KeystrokeAutomation::createINPUTs(splitInput);

        REQUIRE(inputs.size() == 8);
        
        REQUIRE(inputs[0].type == INPUT_MOUSE); 

        REQUIRE(inputs[2].type == INPUT_KEYBOARD);
        REQUIRE(inputs[2].ki.wScan == 'h');

        REQUIRE(inputs[7].type == INPUT_KEYBOARD);
        REQUIRE(inputs[7].ki.wVk == VK_SHIFT);
    }

    SECTION("getINPUTs runs the full pipeline") {
        auto inputs = KeystrokeAutomation::getINPUTs(" lmouse, \"hi\" ");
        REQUIRE(inputs.size() == 6);
        REQUIRE(inputs[0].type == INPUT_MOUSE); 
        REQUIRE(inputs[1].type == INPUT_MOUSE); 
        REQUIRE(inputs[2].ki.wScan == 'h'); 
        REQUIRE(inputs[3].ki.wScan == 'h'); 
        REQUIRE(inputs[4].ki.wScan == 'i'); 
        REQUIRE(inputs[5].ki.wScan == 'i'); 
    }
}
