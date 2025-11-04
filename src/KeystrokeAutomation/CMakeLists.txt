set(KeystrokeAutomationFiles
    ButtonPress.cpp
    ButtonPressHelpers.cpp 
    VirtualKeys.cpp 
)
add_library(KeystrokeAutomation ${KeystrokeAutomationFiles})
target_link_libraries(KeystrokeAutomation PRIVATE Utility)
target_include_directories(KeystrokeAutomation PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(KeystrokeAutomation PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})