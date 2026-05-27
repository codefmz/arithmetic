file(GLOB SRC "./*.cpp")

add_library(hashsquare STATIC ${SRC})
target_link_libraries(hashsquare PUBLIC hash)
target_include_directories(hashsquare PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
