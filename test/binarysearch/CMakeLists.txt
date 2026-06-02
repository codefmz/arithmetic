add_executable(binarysearch_test binarysearch_test.cpp)
target_link_libraries(binarysearch_test PRIVATE binarysearch GTest::gtest GTest::gtest_main Threads::Threads tub)

add_test(NAME binarysearch_test COMMAND binarysearch_test)