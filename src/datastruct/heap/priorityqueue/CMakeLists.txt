aux_source_directory(. SRC_LIST)

add_library(priorityqueue STATIC ${SRC_LIST})
target_include_directories(priorityqueue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
