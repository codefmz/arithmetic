#include <list>


template<class Object>
class Queue
{
public:
    Queue() = default;
    size_t size()
    {
        return c.size();
    }
    bool empty()
    {
        return c.empty();
    }
    void clear()
    {
        return c.clear();
    }
    void push(const Object& o)
    {
        c.push_back(o);
    }
    void push(Object&& o)
    {
        c.push_back(move(o));
    }
private:
    std::list<Object> c;
};