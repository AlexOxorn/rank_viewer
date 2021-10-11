cmake_minimum_required(VERSION "3.16.3")

# set the project name and version
project(rank_viewer VERSION 0.5)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_C_COMPILER "clang-10")
# set(CMAKE_CXX_COMPILER "/usr/bin/clang++-10")
set(CMAKE_CXX_FLAGS "-g -rdynamic -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable -Og")

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
target_link_libraries("${PROJECT_NAME}" PRIVATE "sa2")
target_link_libraries("${PROJECT_NAME}" PRIVATE "memory")

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
