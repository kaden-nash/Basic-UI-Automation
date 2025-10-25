add_subdirectory(ButtonPress)
add_subdirectory(ButtonPressHelpers)
add_subdirectory(Mouse)
add_subdirectory(Utility)

add_library(KeystrokeAutomation INTERFACE)

target_link_libraries(KeystrokeAutomation INTERFACE 
    KeystrokeAutomation-ButtonPress
    KeystrokeAutomation-Mouse 
)