add_library(
  "unleashed"
  include/unleashed/data_extractor.hpp
  include/unleashed/rank_view.hpp
  include/unleashed/enum.hpp
  include/unleashed/structs.hpp
   include/unleashed/variables.hpp
  include/unleashed/position_view.hpp

  src/data_extractor.cpp
  src/rank_view.cpp
  src/position_view.cpp
)

target_link_libraries("unleashed" "ox")
target_link_libraries("unleashed" "display")
target_link_libraries("unleashed" "memory")

target_include_directories(
  "unleashed"
  PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
