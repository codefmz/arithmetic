file(GLOB SRC "./*.cpp")

add_library(merge STATIC ${SRC})
target_include_directories(merge PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
