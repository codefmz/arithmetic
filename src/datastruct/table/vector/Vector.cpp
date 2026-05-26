#include <iostream>
#include "Vector.h"
#include "gtest/gtest.h"
#include "class.h"

using namespace std;

class vectorTest : public ::testing::Test {
protected:
    vectorTest() {
    }
    ~vectorTest() override {
    }
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(vectorTest, test_vector) {
    Vector<int> vct;
    vct.push_back(3);
    vct.push_back(2);
    vct.push_back(1);
    vct.push_back(5);
    vct.push_back(0);

    for (auto i = vct.begin(); i != vct.end(); ++i) {
        std::cout << *i << std::endl;
    }
}

TEST_F(vectorTest, test_vector2) {
    Vector<Dog> dogVct;
    const Dog dog("哈巴狗", "cute");

    dog.say();

    Dog dog2{ "zzz","gggg" };
    dogVct.push_back(Dog("哈巴狗1", "cute1"));
    dogVct.push_back(dog);
    dogVct.push_back(Dog("哈巴狗3", "cute1"));
    dogVct.emplace("hhhhh", "ggggg");
    for (auto i = dogVct.begin(); i != dogVct.end(); i++) {
        cout << " dog = " << i->name << "  " << i->chs << endl;
    }
    cout << " front = " << dogVct.front().name << endl;
    cout << " back = " << dogVct.back().name << endl;
}