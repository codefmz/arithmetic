file(GLOB SRC "./*.cpp")

add_library(kfifo STATIC ${SRC})
target_include_directories(kfifo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
