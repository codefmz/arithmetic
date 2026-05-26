#include "gtest/gtest.h"
#include "kfifo.h"

#include <iostream>
#include <thread>

using std::thread;

class kfifoTest : public ::testing::Test {
protected:
    kfifoTest() {
    }
    ~kfifoTest() override {
    }
    void SetUp() override {
    }
    void TearDown() override {
    }
};



TEST_F(kfifoTest, kfifo_test) {
    KFIFO fifo(0);

    thread producer([&]() {
        int buf;
        uint32_t len;
        for (int i = 0; i < 10000; i++) {
            buf = i;
            do {
                len = fifo.put((const char *)&buf, sizeof(int));
            } while (len == 0);
        }
    });

    thread consumer([&]() {
        int buf = 0;
        uint32_t len;
        for (int i = 0; i < 10000; i++) {
            do {
                len = fifo.get((char *)&buf, sizeof(int));
            } while (len == 0);
            EXPECT_EQ(buf, i);
        }
    });

    producer.join();
    consumer.join();
}