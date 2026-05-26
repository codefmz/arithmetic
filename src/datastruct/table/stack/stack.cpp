#include <iostream>
#include <regex>
#include "stack.h"
#include "gtest/gtest.h"
#include "class.h"

using namespace std;

class stackTest : public ::testing::Test {
protected:
    stackTest() {
    }
    ~stackTest() override {
    }
    void SetUp() override {
    }
    void TearDown() override {
    }
};

int calculateStack(const vector<string>& vct)
{
    // 6 * (5 +(2 + 3) * 8 + 3 )
    //Vector<string> strVec;
    //strVec.push_back("6");
    //strVec.push_back("5");
    //strVec.push_back("2");
    //strVec.push_back("3");
    //strVec.push_back("+");
    //strVec.push_back("8");
    //strVec.push_back("*");
    //strVec.push_back("+");
    //strVec.push_back("3");
    //strVec.push_back("+");
    //strVec.push_back("*");

    Stack<int> ss;
    for (auto& i : vct) {
        if (isWord(i)) {
            int num = stoi(i);
            ss.push(num);
        } else {
            int num1 = ss.top();
            ss.pop();
            int num2 = ss.top();
            ss.pop();
            int result = 0;
            if (i == "-") {
                result = num2 - num1;
            } else if (i == "+") {
                result = num2 + num1;
            } else if (i == "*") {
                result = num2 * num1;
            } else if (i == "/") {
                result = num2 / num1;
            }
            ss.push(result);
        }
    }

	cout << " result = " << ss.top() << endl;
	return ss.top();
}

void strSplit(vector<string>& vct, const string& s)
{
    regex num_regex("-?\\d+(\\.?\\d+)?|[+\\-/*//(//)]");
    for (sregex_iterator it(s.begin(), s.end(), num_regex), end_it; it != end_it; ++it) {
        vct.push_back(it->str());
    }
}

void getPostfix(vector<string>& vct, const vector<string>& splitVct)
{
    Stack<string> ss;
    for (auto& i : splitVct) {
        if (isWord(i)) {
            vct.push_back(i);
        } else {
            if (ss.empty()) {
                ss.push(i);
            } else {
                if (i != ")") {
                    int priority1 = getOpPriority(i);
                    int priority2 = getOpPriority(ss.top());
                    while (priority1 <= priority2 && ss.top() != "(") {
                        vct.push_back(ss.top());
                        ss.pop();
                        priority2 = getOpPriority(ss.top());
                    }
                    ss.push(i);
                } else {
                    while (ss.top() != "(") {
                        vct.push_back(ss.top());
                        ss.pop();
                    }
                    ss.pop();
                }
            }
        }
    }

    while (!ss.empty()) {
        vct.push_back(ss.top());
        ss.pop();
    }
}

bool isWord(const string& s)
{
    return isdigit(s.c_str()[0]);
}

int getOpPriority(const string& word)
{
    if (word == "+" || word == "-") {
        return 1;
    } else if (word == "*" || word == "/") {
        return 2;
    } else if (word == "(" || word == ")") {
        return 3;
    }
    return 0;
}

TEST_F(stackTest, test1) {
    list<int> aList;
    aList.push_back(4);
    aList.push_back(5);
    aList.push_back(6);
    aList.push_back(7);
    aList.push_back(1);
    aList.push_back(2);
    aList.push_back(3);


    for (auto& i : aList) {
        cout << " i = " << i << endl;
    }
    cout << " size = " << aList.size() << endl;
    cout << " front = " << aList.front() << endl;
}

TEST_F(stackTest, test2) {
	// 6 * (5 +(2 + 3) * 8 + 3 )
	vector<string> splitVct;
	vector<string> vct;
	string s = "(6 * 4 - 3 / 2) * 9";
	strSplit(splitVct, s);
	getPostfix(vct, splitVct);
	calculateStack(vct);
}