cmake_minimum_required(VERSION "3.16.3")

# set the project name and version
project(rank_viewer VERSION 0.5)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(OXLIB_CANVAS ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(CMAKE_CXX_FLAGS "-O0 -Wall -Wextra -fdiagnostics-color=always -fsanitize=address,undefined -g")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    SET(CMAKE_CXX_FLAGS "-O3 -fdiagnostics-color=always -march=native")
elseif(CMAKE_BUILD_TYPE STREQUAL "Perf")
    SET(CMAKE_CXX_FLAGS "-O0")
endif()

add_subdirectory("fmt")
add_subdirectory("ox_lib")
add_subdirectory("display")
add_subdirectory("memory")
add_subdirectory("games")

add_executable(
    "${PROJECT_NAME}"
    "main.cpp"
)

target_link_libraries("${PROJECT_NAME}" PRIVATE "ox")
target_link_libraries("${PROJECT_NAME}" PRIVATE "fmt")
target_link_libraries("${PROJECT_NAME}" PRIVATE "display")
target_link_libraries("${PROJECT_NAME}" PRIVATE "sonic_heroes")
target_link_libraries("${PROJECT_NAME}" PRIVATE "sonic_colors")
target_link_libraries("${PROJECT_NAME}" PRIVATE "shadow")
target_link_libraries("${PROJECT_NAME}" PRIVATE "sa2")
target_link_libraries("${PROJECT_NAME}" PRIVATE "jsr")
target_link_libraries("${PROJECT_NAME}" PRIVATE "memory")
target_link_libraries("${PROJECT_NAME}" PRIVATE "unleashed")

include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)

if( supported )
    message(STATUS "IPO / LTO enabled")
    set_property(TARGET "${PROJECT_NAME}" PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    get_property(languages GLOBAL PROPERTY ENABLED_LANGUAGES)
    message(STATUS "languages: ${languages}")
    message(STATUS "IPO / LTO not supported: <${error}>")
endif()

install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
install(FILES "src/main.cpp" DESTINATION src)
