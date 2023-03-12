add_library(
        "memory"
        include/helpers.h
        $<$<PLATFORM_ID:Windows>:
        windows/native_process.cpp
        windows/native_process.hpp
        >
        $<$<PLATFORM_ID:Linux>:
        unix/dolphin_process.cpp
        unix/dolphin_process.hpp
        unix/native_process.cpp
        unix/native_process.hpp
        >
)

target_link_libraries("memory" "ox")

target_include_directories(
        "memory"
        PUBLIC
        "include"
)
