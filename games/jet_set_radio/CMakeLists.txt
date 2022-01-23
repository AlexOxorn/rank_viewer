add_library(
  "jsr"
#  include/jsr/data_extractor.hpp
#  include/jsr/rank_view.hpp
  include/jsr/enum.hpp
  include/jsr/structs.hpp
  include/jsr/variables.hpp
#  include/jsr/position_view.hpp

#  src/data_extractor.cpp
#  src/rank_view.cpp
#  src/position_view.cpp
)

target_link_libraries("jsr" "ox")
target_link_libraries("jsr" "fmt")
target_link_libraries("jsr" "display")
target_link_libraries("jsr" "memory")

target_include_directories(
  "jsr"
  PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
