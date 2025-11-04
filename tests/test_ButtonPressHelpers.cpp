#include "catch.hpp"
#include "..\src\KeystrokeAutomation\ButtonPressHelpers\ButtonPressHelpers.h"
#include "..\src\KeystrokeAutomation\Utility\VirtualKeys\VirtualKeys.h"
#include "..\src\Utility\StringManip\StringManip.h"
#include "winuser.h"

TEST_CASE("Error Handling", "[errors]") {
    
    SECTION("throwSendInputsError formats the message correctly") {
        REQUIRE_THROWS_WITH(
            KeystrokeAutomation::ButtonPressHelpers::throwSendInputsError(5, 10), 
            "Not all inputs were sent (5/10)"
        );
    }
    
    SECTION("attemptToGetVKey finds valid keys") {
        REQUIRE(KeystrokeAutomation::ButtonPressHelpers::attemptToGetVKey("lshift") == VK_LSHIFT);
        REQUIRE(KeystrokeAutomation::ButtonPressHelpers::attemptToGetVKey("lSHIFT") == VK_LSHIFT); 
        REQUIRE(KeystrokeAutomation::ButtonPressHelpers::attemptToGetVKey("lmouse") == VK_LBUTTON);
    }
}

TEST_CASE("Parsing Helper Functions", "[parser_helpers]") {

    SECTION("isCompoundCommand identifies commands with a pipe") {
        REQUIRE(KeystrokeAutomation::ButtonPressHelpers::isCompoundCommand("ctrl|shift") == true);
        REQUIRE(KeystrokeAutomation::ButtonPressHelpers::isCompoundCommand("ctrl | shift") == true);
        REQUIRE(KeystrokeAutomation::ButtonPressHelpers::isCompoundCommand("ctrl") == false);
        REQUIRE(KeystrokeAutomation::ButtonPressHelpers::isCompoundCommand("") == false);
    }

    SECTION("isPrintableVKey identifies quoted strings") {
        REQUIRE(KeystrokeAutomation::ButtonPressHelpers::isPrintableVKey("\"hello\"") == true);
        REQUIRE(KeystrokeAutomation::ButtonPressHelpers::isPrintableVKey("\"\"") == true);
        REQUIRE(KeystrokeAutomation::ButtonPressHelpers::isPrintableVKey("hello") == false);
        REQUIRE(KeystrokeAutomation::ButtonPressHelpers::isPrintableVKey("\"hello") == false);
        REQUIRE(KeystrokeAutomation::ButtonPressHelpers::isPrintableVKey("hello\"") == false);
        REQUIRE(KeystrokeAutomation::ButtonPressHelpers::isPrintableVKey("") == false);
    }

    SECTION("removeLeadingAndTrailingChars strips outer quotes") {
        REQUIRE(KeystrokeAutomation::ButtonPressHelpers::removeLeadingAndTrailingChars("\"hello\"") == "hello");
        REQUIRE(KeystrokeAutomation::ButtonPressHelpers::removeLeadingAndTrailingChars("\"a\"") == "a");
        REQUIRE(KeystrokeAutomation::ButtonPressHelpers::removeLeadingAndTrailingChars("\"\"") == "");
    }
}

TEST_CASE("Input Creation Logic", "[input_creation]") {

    SECTION("createINPUTForUnprintableVKey creates a press and release pair") {
        auto inputs = KeystrokeAutomation::ButtonPressHelpers::createINPUTForUnprintableVKey("shift");
        REQUIRE(inputs.size() == 2);
        REQUIRE(inputs[0].type == INPUT_KEYBOARD); 
        REQUIRE(inputs[0].ki.wVk == VK_SHIFT);
        REQUIRE(inputs[1].type == INPUT_KEYBOARD); 
        REQUIRE(inputs[1].ki.wVk == VK_SHIFT);
    }

    SECTION("createINPUTForPrintableVKeys creates pairs for each character") {
        auto inputs = KeystrokeAutomation::ButtonPressHelpers::createINPUTForPrintableVKeys("\"hi\"");
        REQUIRE(inputs.size() == 4);
        REQUIRE(inputs[0].ki.wScan == 'h');
        REQUIRE(inputs[1].ki.wScan == 'h');
        REQUIRE(inputs[2].ki.wScan == 'i');
        REQUIRE(inputs[3].ki.wScan == 'i');
        REQUIRE(inputs[0].type == INPUT_KEYBOARD);
        REQUIRE(inputs[1].type == INPUT_KEYBOARD); 
    }

    SECTION("createINPUTForMouseClick creates mouse and release pair") {
        auto inputs = KeystrokeAutomation::ButtonPressHelpers::createINPUTForMouseClick("lmouse");
        REQUIRE(inputs.size() == 2);
        REQUIRE(inputs[0].type == INPUT_MOUSE); 
        REQUIRE(inputs[1].type == INPUT_MOUSE); 

        auto rInputs = KeystrokeAutomation::ButtonPressHelpers::createINPUTForMouseClick("rmouse");
        REQUIRE(rInputs.size() == 2);
        REQUIRE(rInputs[0].type == INPUT_MOUSE); 
    }

    SECTION("createINPUTForMouseMove creates mouse movement INPUT") {
        auto inputs = KeystrokeAutomation::ButtonPressHelpers::createINPUTForMouseMove("(100|100)");
        REQUIRE(inputs.size() == 1);
        REQUIRE(inputs[0].type == INPUT_MOUSE); 
        REQUIRE(inputs[0].mi.dx == 100); 
        REQUIRE(inputs[0].mi.dy == 100); 
        REQUIRE(inputs[0].mi.dwFlags == MOUSEEVENTF_ABSOLUTE); 

        REQUIRE_THROWS_WITH(KeystrokeAutomation::ButtonPressHelpers::createINPUTForMouseMove("(0|-1)"), 
        "Mouse movement range must be between 0 and 65335 for both axes, was (0, -1)"
        );
    }

    SECTION("createINPUTForHoldingPresses") {
        std::vector<std::string> aliases = {"ctrl", "shift"};
        auto inputs = KeystrokeAutomation::ButtonPressHelpers::createINPUTForHoldingPresses(aliases);
        
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
        auto inputs = KeystrokeAutomation::ButtonPressHelpers::createINPUTs(splitInput);

        REQUIRE(inputs.size() == 8);
        
        REQUIRE(inputs[0].type == INPUT_MOUSE); 

        REQUIRE(inputs[2].type == INPUT_KEYBOARD);
        REQUIRE(inputs[2].ki.wScan == 'h');

        REQUIRE(inputs[7].type == INPUT_KEYBOARD);
        REQUIRE(inputs[7].ki.wVk == VK_SHIFT);
    }

    SECTION("getINPUTs runs the full pipeline") {
        auto inputs = KeystrokeAutomation::ButtonPressHelpers::getINPUTs(" lmouse, \"hi\" ");
        REQUIRE(inputs.size() == 6);
        REQUIRE(inputs[0].type == INPUT_MOUSE); 
        REQUIRE(inputs[1].type == INPUT_MOUSE); 
        REQUIRE(inputs[2].ki.wScan == 'h'); 
        REQUIRE(inputs[3].ki.wScan == 'h'); 
        REQUIRE(inputs[4].ki.wScan == 'i'); 
        REQUIRE(inputs[5].ki.wScan == 'i'); 
    }
}
