file(GLOB SRC "./*.cpp")

add_library(queue STATIC ${SRC})
target_include_directories(queue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
