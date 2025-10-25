add_subdirectory(StringManip)

add_library(Utility INTERFACE)

target_link_libraries(Utility INTERFACE 
    Utility-StringManip
)

