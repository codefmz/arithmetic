#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Dog {
    string name;
    char* chs;
    Dog(const string& s, const char* as) :name(s) {
        chs = new char[strlen(as) + 1];
        memcpy(chs, as, strlen(as) + 1);
        cout << __FILE__ << "(" << __LINE__ << "): " << __func__ << " Dog Construct" << endl;
    }

    Dog(const Dog& dog) :name(dog.name) {
        chs = new char[strlen(dog.chs) + 1];
        memcpy(chs, dog.chs, strlen(dog.chs) + 1);
        cout << __FILE__ << "(" << __LINE__ << "): " << __func__ << " Dog left const Construct" << endl;
    }

    Dog(Dog&& dog) noexcept :name(dog.name), chs(dog.chs) {
        dog.chs = nullptr;
        cout << __FILE__ << "(" << __LINE__ << "): " << __func__ << " Dog right const Construct" << endl;
    }

    ~Dog() {
        if (chs) {
            delete[] chs;
            chs = nullptr;
            cout << __FILE__ << "(" << __LINE__ << "): " << __func__ << "not nullptr Dog Delete" << endl;
        }
        cout << __FILE__ << "(" << __LINE__ << "): " << __func__ << " Dog Delete" << endl;
    }

    void say() const {
        cout << "const dog say !" << endl;
    }

    void say() {
        cout << "dog say !" << endl;
    }

};

bool operator < (const Dog& d1, const Dog& d);

ostream& operator<<(ostream& out, const Dog& d);
