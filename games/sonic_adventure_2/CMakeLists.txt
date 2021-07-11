add_library(
  "sa2"
  include/sa2/data_extractor.hpp
  include/sa2/rank_view.hpp
  include/sa2/enum.hpp
  include/sa2/structs.hpp
  include/sa2/variables.hpp
  include/sa2/position_view.hpp

  src/data_extractor.cpp
  src/rank_view.cpp
  src/position_view.cpp
)

target_link_libraries("sa2" "ox")
target_link_libraries("sa2" "fmt")
target_link_libraries("sa2" "display")
target_link_libraries("sa2" "memory")

target_include_directories(
  "sa2"
  PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
