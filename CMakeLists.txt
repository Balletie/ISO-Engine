cmake_minimum_required (VERSION 2.6)
 
project (ISO-Engine)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})
find_package (SFML REQUIRED system window graphics )

if(SFML_FOUND)
	include_directories (${SFML_INCLUDE_DIR})
endif()

add_subdirectory(src)
