#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <list>
#include <utility>

template<typename Object, typename Container = std::list<Object>>
class Stack
{
public:
    Stack() = default;
    std::size_t size() const {
        return c.size();
    }
    bool empty() const {
        return c.empty();
    }
    void push(const Object& o) {
        c.push_back(o);
    }
    void push(Object&& o) {
        c.push_back(std::move(o));
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
    Container c;
};

#endif
