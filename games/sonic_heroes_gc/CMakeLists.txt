add_library(
  "sonic_heroes"
  include/sonic_heroes/data_extractor.hpp
  include/sonic_heroes/rank_view.hpp
  include/sonic_heroes/enum.hpp
  include/sonic_heroes/structs.hpp
  include/sonic_heroes/variables.hpp

  src/data_extractor.cpp
  src/rank_view.cpp
)

target_link_libraries("sonic_heroes" "ox")
target_link_libraries("sonic_heroes" "fmt")
target_link_libraries("sonic_heroes" "display")
target_link_libraries("sonic_heroes" "memory")

target_include_directories(
  "sonic_heroes"
  PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
