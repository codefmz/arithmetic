file(GLOB SRC "./*.cpp")

add_library(dynamic STATIC ${SRC})
target_link_libraries(dynamic PUBLIC hash)
target_include_directories(dynamic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
