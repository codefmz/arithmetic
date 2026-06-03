add_executable(merge_test mergeTest.cpp)
target_link_libraries(merge_test PRIVATE merge GTest::gtest GTest::gtest_main Threads::Threads)

add_test(NAME merge_test COMMAND merge_test)
