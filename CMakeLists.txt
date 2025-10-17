cmake_minimum_required(4.2.0)

project(BasicUIAutomation)

# including Catch2 "catch.hpp" fetch
include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.10
)

FetchContent_MakeAvailable(Catch2)

# subfolders
add_subdirectory(src)
add_subdirectory(tests)