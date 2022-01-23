add_library(
        "memory"
        include/helpers.h
        unix/dolphin_process.cpp
        unix/dolphin_process.hpp
        unix/native_process.cpp
        unix/native_process.hpp
)

target_link_libraries("memory" "ox")

target_include_directories(
        "memory"
        PUBLIC
        "include"
)
