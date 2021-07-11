add_library(
  "display"
  rank.hpp
  position_dump.hpp
  common.hpp
)

target_link_libraries("display" "ox")
target_link_libraries("display" "fmt")

target_include_directories(
  "display"
  PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}"
)
