add_library(
  "memory"
  dolphin_process.cpp
  dolphin_process.hpp
  process.cpp
  process.hpp
)

target_link_libraries("memory" "ox")

target_include_directories(
  "memory"
  PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}"
)
