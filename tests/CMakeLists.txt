set(TESTING_FILES
    tests_main.cpp
    test_Mouse.cpp
    test_ButtonPress.cpp
    test_ButtonPressHelpers.cpp 
    test_StringManip.cpp
)

add_executable(Tests ${TESTING_FILES})

target_link_libraries(Tests PRIVATE 
    KeystrokeAutomation
    Utility
)

add_test(NAME TestMouse COMMAND Tests)
add_test(NAME TestButtonPress COMMAND Tests)