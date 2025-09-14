add_library(
        "display"
        rank.hpp
        rankX.hpp
        rankX.cpp
        display_rank.hpp
        position_dump.hpp
        common.hpp
        common.cpp
)

target_link_libraries("display" "ox")
target_link_libraries(display m)

target_include_directories(
  "display"
  PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}"
)
