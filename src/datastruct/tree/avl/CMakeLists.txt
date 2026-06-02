file(GLOB SRC "./*.cpp")

add_library(avl STATIC ${SRC})
target_include_directories(avl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
