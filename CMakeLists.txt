cmake_minimum_required(VERSION 3.5.0)
project(cppcore VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
#specify whether the chosen C++ standard must be strictly adhered to by the compiler
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/tub
    ${PROJECT_SOURCE_DIR}/src/datastruct/disjset
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

link_directories(
    ${PROJECT_SOURCE_DIR}/lib
)

enable_testing()

add_subdirectory(src)
add_subdirectory(tub)

#target
add_executable(${target} main.cpp)
target_link_libraries(${target} gtest tub lib${target})
#强制链接动态库，避免main函数没有使用，然后编译器优化，没有带上这个
target_link_options(${target} PRIVATE "/WHOLEARCHIVE:lib${target}.lib")
add_custom_command(TARGET ${target}
    COMMAND echo "compile ${target} test finish!!!"
)