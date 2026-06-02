add_executable(avl_test avl_test.cpp)
target_link_libraries(avl_test PRIVATE avl GTest::gtest GTest::gtest_main Threads::Threads tub)

add_test(NAME avl_test COMMAND avl_test)
