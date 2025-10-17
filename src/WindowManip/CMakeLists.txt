# add WindowsManip library with all files in this library
add_library(WindowsManip WindowsManip.cpp)

target_include_directories(WindowsManip PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})