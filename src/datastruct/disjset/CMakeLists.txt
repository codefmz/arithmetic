file(GLOB SRC "./*.cpp")

add_library(disjset STATIC ${SRC})
target_include_directories(disjset PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})