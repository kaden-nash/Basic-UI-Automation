# add Keyboard library with all files in this library
add_library(Keyboard Keyboard.cpp)

target_include_directories(Keyboard PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})