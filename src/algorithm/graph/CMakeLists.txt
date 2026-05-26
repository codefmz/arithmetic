file(GLOB SRC "./*.cpp")

add_library(libgraph STATIC ${SRC})
target_link_libraries(libgraph PRIVATE libdisjset)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(libgraph PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
