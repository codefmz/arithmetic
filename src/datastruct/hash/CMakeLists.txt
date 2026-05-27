file(GLOB SRC "./*.cpp")

add_library(hash STATIC ${SRC})
target_include_directories(hash PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(hashlist)
add_subdirectory(hashsquare)