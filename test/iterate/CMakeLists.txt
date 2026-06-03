add_executable(iterate_test iterateTest.cpp)
target_link_libraries(iterate_test PRIVATE iterate GTest::gtest GTest::gtest_main Threads::Threads)

add_test(NAME iterate_test COMMAND iterate_test)
