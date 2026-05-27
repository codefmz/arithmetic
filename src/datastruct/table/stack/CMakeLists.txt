file(GLOB SRC "./*.cpp")

add_library(stack STATIC ${SRC})
target_include_directories(stack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
