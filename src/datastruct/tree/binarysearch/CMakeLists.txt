file(GLOB SRC "./*.cpp")

add_library(binarysearch STATIC ${SRC})
target_include_directories(binarysearch PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})