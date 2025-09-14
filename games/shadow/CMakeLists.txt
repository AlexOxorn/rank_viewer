add_library(
        shadow
        include/shadow/enum.hpp
        include/shadow/structs.hpp
        include/shadow/variables.hpp
        include/shadow/data_extractor.hpp
        include/shadow/rank_view.hpp
        src/data_extractor.cpp
        src/rank_view.cpp
)

target_link_libraries("shadow" "ox")
target_link_libraries("shadow" "display")
target_link_libraries("shadow" "memory")

target_include_directories(
  "shadow"
  PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
