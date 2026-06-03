cmake_minimum_required(VERSION 3.16)

project(alg VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_BUILD_TYPE MATCHES debug)
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
    message(STATUS "Debug mode")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
    message(STATUS "Release mode")
endif()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_package(GTest CONFIG REQUIRED)
find_package(plog CONFIG REQUIRED)

add_subdirectory(tub)
add_subdirectory(src)
enable_testing()
add_subdirectory(test)

add_executable(alg main.cpp)
target_link_libraries(alg PRIVATE plog::plog GTest::gtest binarysearch lock_free_stack)
