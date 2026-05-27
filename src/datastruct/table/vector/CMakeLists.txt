file(GLOB SRC "./*.cpp")

add_library(vector STATIC ${SRC})
target_include_directories(vector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
