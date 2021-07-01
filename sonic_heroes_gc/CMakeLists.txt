add_library(
  "sonic_heroes"
  data_extractor.cpp
  data_extractor.hpp
  enum.hpp
  structs.hpp
  variables.hpp
)

target_link_libraries("sonic_heroes" "ox")
target_link_libraries("sonic_heroes" "fmt")

target_include_directories(
  "sonic_heroes"
  PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}"
)
