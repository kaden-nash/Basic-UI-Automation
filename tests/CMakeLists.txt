set(TESTING_FILES
    tests_main.cpp
    test_Mouse.cpp
    test_Keyboard.cpp
)

add_executable(Tests ${TESTING_FILES})

target_link_libraries(Tests PRIVATE 
    KeystrokeAutomation-ButtonPress
    KeystrokeAutomation-Mouse 
    WindowsManip
)

add_test(NAME TestMouse COMMAND Tests)
add_test(NAME TestKeyboard COMMAND Tests)