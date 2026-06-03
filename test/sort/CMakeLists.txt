add_executable(sort_test testsort.cpp)
target_link_libraries(sort_test PRIVATE sort GTest::gtest GTest::gtest_main Threads::Threads tub)

add_test(NAME sort_test COMMAND sort_test)
