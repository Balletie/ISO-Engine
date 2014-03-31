cmake_minimum_required (VERSION 2.6)
 
project (ISO-Engine)

find_package (SFML REQUIRED)

include_directories (${SFML_INCLUDE_DIR})

add_definitions(-std=gnu++11)

add_executable(iso main.cpp layer.cpp world.cpp transforms.cpp tile.cpp highlight.cpp)
target_link_libraries(iso sfml-window sfml-graphics sfml-system)
