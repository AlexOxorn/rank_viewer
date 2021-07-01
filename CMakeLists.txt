cmake_minimum_required(VERSION "3.16.3")

# set the project name and version
project(RANK_VIEWER VERSION 0.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(DCMAKE_CXX_FLAGS "-Werror -Wall -Wextra")

find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
)
if(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found.")
else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(
        CMAKE_CXX_CLANG_TIDY
        "${CLANG_TIDY_EXE}"
        -checks=cppcoreguidelines-*,readability-*,performance-*,clang-analyzer-*,bugprone-*,modernize-*,-modernize-use-trailing-return-type,-cppcoreguidelines-avoid-c-arrays,-cppcoreguidelines-pro-type-reinterpret-cast,-readability-braces-around-statements;
        -header-filter=src/.*.hpp
        --warnings-as-errors=performance-*,bugprone-*,-bugprone-exception-escape;
        -p .;
    )
endif()

add_subdirectory("fmt")
add_subdirectory("ox_lib")
add_subdirectory("memory")
add_subdirectory("sonic_heroes_gc")

add_executable(
    "${PROJECT_NAME}"
    "main.cpp"
    "rank.hpp"
)

target_link_libraries("${PROJECT_NAME}" PRIVATE "ox")
target_link_libraries("${PROJECT_NAME}" PRIVATE "fmt")
target_link_libraries("${PROJECT_NAME}" PRIVATE "sonic_heroes")
target_link_libraries("${PROJECT_NAME}" PRIVATE "memory")

install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
install(FILES "src/main.cpp" DESTINATION src)
