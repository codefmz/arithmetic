#include <memory>
#include <utility>

template< class Object>
class Vector {
public:
    typedef Object value_type;
    typedef value_type* iterator;
    typedef value_type& reference;
    typedef size_t size_type;
private:
    static std::allocator<Object> allo;
    iterator first_elem;
    iterator first_free;
    iterator end_elem;
public:
    Vector(int size = 0) {
        if (size > 0) {
            first_elem = allo.allocate(size + 1);
            first_free = first_elem + 1;
            end_elem = first_elem + size + 1;
        } else {
            first_elem = first_free = end_elem = nullptr;
        }
    }

    ~Vector() {
        free();
    }

    Vector(const Vector& vct) {
        size_t len = vct.size();
        first_elem = allo.allocate(len);
        auto temp = first_elem;
        for (auto i = vct.first_elem; i != vct.first_free; ++i) {
            allo.construct(temp++, *i);
        }
        end_elem = first_free = temp;
    }

    Vector& operator=(const Vector& vct) {
        free();
        size_t len = vct.size();
        first_elem = allo.allocate(len);
        auto temp = first_elem;
        for (auto i = vct.first_elem; i != vct.first_free; ++i) {
            allo.construct(temp++, *i);
        }
        end_elem = first_free = temp;
        return *this;
    }

    Vector(Vector&& vct) {
        first_elem = vct.frist_elem;
        first_free = vct.first_free;
        end_elem = vct.end_elem;
    }
    Vector& operator=(Vector&& vct) {
        free();
        first_elem = vct.frist_elem;
        first_free = vct.first_free;
        end_elem = vct.end_elem;
        return *this;
    }

    size_t size() {
        return first_free - first_elem;
    }
    size_t capacity() {
        return end_elem - first_elem;
    }


    Object* begin() const {
        return first_elem;
    }

    Object* end() const {
        return first_free;
    }

    const Object* cbegin() const {
        return first_elem;
    }
    const Object* cend() const {
        return first_free;
    }
    void push_back(const Object& o)
    {
        check_size();
        allo.construct(first_free++, o);
    }
    void push_back(Object&& o) {
        check_size();
        allo.construct(first_free++, std::move(o));
    }

    template<typename... Arg>
    void emplace(Arg&&...arg) {
        check_size();
        allo.construct(first_free++, arg...);
    }

    Object& back() {
        return *(first_free - 1);
    }
    Object& front() {
        return *first_elem;
    }

private:
    void check_size() {
        if (first_free == end_elem) {
            rellocate();
        }
    }
    void rellocate() {
        size_t len = size() ? 2 * size() : 10;
        auto new_first_elem = allo.allocate(len), temp = new_first_elem;
        for (auto i = first_elem; i != first_free; i++) {
            allo.construct(temp++, std::move(*i));
        }
        free();
        first_elem = new_first_elem;
        first_free = temp;
        end_elem = first_elem + len;
    }

    void free() {
        if (first_elem) {
            for (auto i = first_elem; i != first_free; ++i) {
                allo.destroy(i);
            }
            allo.deallocate(first_elem, end_elem - first_elem);
            first_elem = first_free = end_elem = nullptr;
        }
    }
};

template< class Object>
std::allocator<Object> Vector<Object>::allo;