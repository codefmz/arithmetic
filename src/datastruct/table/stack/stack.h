#include <list>
#include <string>
#include <vector>

using namespace std;

template<typename Object, typename Container = std::list<Object>>
class Stack
{
public:
    Stack() = default;
    size_t size() {
        return c.size();
    }
    bool empty() {
        return c.empty();
    }
    void push(const Object& o) {
        c.push_back(o);
    }
    void push(Object&& o) {
        c.push_back(move(o));
    }
    void pop() {
        c.pop_back();
    }
    Object& top() {
        return c.back();
    }
    const Object& top() const {
        return c.back();
    }
private:
    std::list<Object> c;
};


//计算后缀表达式的值
int calculateStack(const vector<string>& vct);
/*
* 将 s 分隔为数值与符号，存放到 vct 中
*/
void strSplit(vector<string>& vct, const string& s);

void getPostfix(vector<string>& vct, const vector<string>& splitVct);

bool isWord(const string& s);

int getOpPriority(const string& word);