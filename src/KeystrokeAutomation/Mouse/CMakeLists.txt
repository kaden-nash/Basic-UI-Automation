# add Mouse library with all files in this library
add_library(KeystrokeAutomation-Mouse Mouse.cpp)

target_include_directories(KeystrokeAutomation-Mouse PUBLIC ${CMAKE_SOURCE_DIR}/include)