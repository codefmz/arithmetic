file(GLOB SRC "./*.cpp")

add_library(libhashsquare STATIC ${SRC})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(libhashsquare PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
