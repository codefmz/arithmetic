file(GLOB SRC "./*.cpp")

add_library(libdynamic STATIC ${SRC})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(libdynamic PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
