add_executable(lock_free_stack_test lock_free_stack_test.cpp)
target_link_libraries(lock_free_stack_test
    PRIVATE
        lock_free_stack
        GTest::gtest
        GTest::gtest_main
        Threads::Threads
)

add_test(NAME lock_free_stack_test COMMAND lock_free_stack_test)
