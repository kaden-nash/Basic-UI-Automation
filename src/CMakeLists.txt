add_subdirectory(KeystrokeAutomation)
add_subdirectory(Utility)

add_library(CoreLib INTERFACE)

target_link_libraries(CoreLib INTERFACE 
    KeystrokeAutomation
)