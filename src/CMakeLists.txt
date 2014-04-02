file(GLOB SOURCES *.cpp)

add_executable(iso ${SOURCES})
target_link_libraries(iso sfml-window sfml-graphics sfml-system)
add_definitions(-std=gnu++11)
install(TARGETS iso RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin)

