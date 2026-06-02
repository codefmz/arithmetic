#ifndef MY_CLASS_H
#define MY_CLASS_H

#include <iostream>
#include <string>
#include <cstring>


struct Dog {
    std::string name;
    char* chs;
    Dog(const std::string& s, const char* as) :name(s) {
        chs = new char[strlen(as) + 1];
        memcpy(chs, as, strlen(as) + 1);
    }

    Dog(const Dog& dog) :name(dog.name) {
        chs = new char[strlen(dog.chs) + 1];
        memcpy(chs, dog.chs, strlen(dog.chs) + 1);
    }

    Dog(Dog&& dog) noexcept :name(dog.name), chs(dog.chs) {
        dog.chs = nullptr;
    }

    ~Dog() {
        if (chs) {
            delete[] chs;
            chs = nullptr;
        }
    }

    Dog& operator=(const Dog& dog) {
        if (this != &dog) {
            if (chs) {
                delete[] chs;
                chs = nullptr;
            }
            chs = new char[strlen(dog.chs) + 1];
            memcpy(chs, dog.chs, strlen(dog.chs) + 1);
            name = dog.name;
        }
        return *this;
    }

    Dog& operator=(Dog&& dog) noexcept { 
        if (this != &dog) {
            if (chs) {
                delete[] chs;
                chs = nullptr;
            }
            chs = dog.chs;
            name = dog.name;
            dog.chs = nullptr;
        }
        return *this;
    }

    void say() const {
        std::cout << "const dog say !" << std::endl;
    }

    void say() {
        std::cout << "dog say !" << std::endl;
    }

};

bool operator < (const Dog& d1, const Dog& d2);

std::ostream& operator<<(std::ostream& out, const Dog& d);

#endif
