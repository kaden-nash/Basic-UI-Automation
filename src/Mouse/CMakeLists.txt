# add Mouse library with all files in this library
add_library(Mouse Mouse.cpp)

target_include_directories(Mouse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})