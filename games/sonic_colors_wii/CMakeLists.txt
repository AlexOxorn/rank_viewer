add_library(
  "sonic_colors"
  include/sonic_colors/data_extractor.hpp
  include/sonic_colors/rank_view.hpp
  include/sonic_colors/position_view.hpp
  include/sonic_colors/enum.hpp
  include/sonic_colors/structs.hpp
  include/sonic_colors/variables.hpp

  src/data_extractor.cpp
  src/rank_view.cpp
  src/position_view.cpp
)

target_link_libraries("sonic_colors" "ox")
target_link_libraries("sonic_colors" "display")
target_link_libraries("sonic_colors" "memory")

target_include_directories(
  "sonic_colors"
  PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
