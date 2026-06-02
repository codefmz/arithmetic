file(GLOB SRC "./*.cpp")

add_library(radixtree STATIC ${SRC})
target_include_directories(radixtree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})