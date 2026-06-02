file(GLOB SRC "./*.cpp")

add_library(tub STATIC ${SRC})
target_include_directories(tub PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
