aux_source_directory(. SRC_LIST)

add_library(libpriorityqueue STATIC ${SRC_LIST})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(libpriorityqueue PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)