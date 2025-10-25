add_subdirectory(VirtualKeys)

add_library(KeystrokeAutomation-Utility INTERFACE)

target_link_libraries(KeystrokeAutomation-Utility INTERFACE 
    KeystrokeAutomation-Utility-VirtualKeys
)