aux_source_directory(./src RT_SRC)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/include/util
)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_library(rt_static STATIC ${RT_SRC})
add_custom_command(TARGET rt_static
    PRE_BUILD
    COMMAND echo "compile radix tree"
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/include/* ${PROJECT_SOURCE_DIR}/include/
)