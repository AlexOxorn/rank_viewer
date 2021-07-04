cmake_minimum_required(VERSION "3.16.3")

# set the project name and version
project(rank_viewer VERSION 0.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(DCMAKE_CXX_FLAGS "-Werror -Wall -Wextra -O2")

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
target_link_libraries("${PROJECT_NAME}" PRIVATE "sa2")
target_link_libraries("${PROJECT_NAME}" PRIVATE "memory")

install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
install(FILES "src/main.cpp" DESTINATION src)
