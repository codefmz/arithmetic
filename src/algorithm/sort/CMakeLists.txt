file(GLOB SRC "./*.cpp")

add_library(sort STATIC ${SRC})
target_include_directories(sort PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
