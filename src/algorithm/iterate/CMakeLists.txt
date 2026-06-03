file(GLOB SRC "./*.cpp")

add_library(iterate STATIC ${SRC})
target_include_directories(iterate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
