file(GLOB SRC "./*.cpp")

add_library(list STATIC ${SRC})
target_include_directories(list PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
