add_executable(graph_test graphtest.cpp)
target_link_libraries(graph_test PRIVATE graph GTest::gtest GTest::gtest_main Threads::Threads)

add_test(NAME graph_test COMMAND graph_test)
