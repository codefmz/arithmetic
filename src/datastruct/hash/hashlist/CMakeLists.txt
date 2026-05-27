file(GLOB SRC "./*.cpp")

add_library(hashlist STATIC ${SRC})
target_link_libraries(hashlist PUBLIC hash)
target_include_directories(hashlist PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
