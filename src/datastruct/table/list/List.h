template <typename Object>
class List {
private:
    struct Node {
        Object data;
        Node* prev;
        Node* next;

        Node(const Object& d = Object{}, Node* p = nullptr, Node* n = nullptr)
            :data(d), prev(p), next{ n }{}
        Node(Object&& d, Node* p = nullptr, Node* n = nullptr)
            :data(move(d)), prev(p), next{ n }{}
    };
private:
    size_t theSize;
    Node* tail;
    Node* head;
    void init() {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
public:
    class const_iterator {
    protected:
        Node* current;// 不希望用户能够直接访问到节点，而是只能通过迭代器去访问
        const_iterator(Node* p) :current{ p } {};
        const_iterator() :current{ nullptr } {};
        friend class List<Object>;
    public:
        const Object& operator*() {
            return current->data;
        }
        const_iterator& operator++() {
            current = current->next();
            return *this;
        }

        const_iterator& operator++(int) {
            const_iterator old = *this;
            ++(*this);
            return old;
        }
        bool operator==(const const_iterator& rhs) const {
            return current == rhs.current;
        }
        bool operator!=(const const_iterator& rhs) const {
            return !(current == rhs.current);
        }
    };

    class iterator :public const_iterator {
    protected:
        iterator(Node* p) :const_iterator(p) {};

        friend class List<Object>;
    public:
        Object& operator*() {
            return const_iterator::current->data;
        }
        iterator& operator++()  {
            this->current = this->current->next;
            return *this;
        }
        iterator& operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }
        iterator& operator--() {
            this->current = this->current->prev;
            return *this;
        }
        iterator& operator--(int)
        {
            iterator old = *this;
            --(*this);
            return old;
        }
    };
public:
    List() {
        init();
    }
    ~List() {
        if (head && tail) {
            clear();
            delete head;
            head = nullptr;
            delete tail;
            tail = nullptr;
        }
    }
    List(const List& list) {
        cout << __FILE__ << "(" << __LINE__ << "): " << __func__ << " list copy construct" << endl;
        init();
        for (auto x : list) {
            push_back(x);
        }
    }
    List& operator=(const List& list) {
        cout << __FILE__ << "(" << __LINE__ << "): " << __func__ << " list operator = " << endl;
        List copy = list;
        std::swap(*this, copy);
        return *this;
    }
    List(List&& list) noexcept :theSize(list.theSize), head(list.head), tail(list.tail) {
        cout << __FILE__ << "(" << __LINE__ << "): " << __func__ << " left value reference " << endl;
        list.theSize = 0;
        list.head = list.tail = nullptr;
    };
    List& operator=(List&& list) noexcept {
        cout << __FILE__ << "(" << __LINE__ << "): " << __func__ << " right value refence = " << endl;
        swap(theSize, list.theSize);
        swap(head, list.head);
        swap(tail, list.tail);
        return *this;
    }
    iterator begin() const {
        return iterator(head->next);
    }

    iterator end() const {
        return iterator(tail);
    }
    const_iterator cbegin() const {
        return const_iterator(head->next);
    }

    size_t size() const {
        return theSize;
    }
    bool empty() const {
        return theSize == 0;
    }
    void clear() {
        erase(begin(), end());
    }
    Object& front() {
        return head->next->data;
    }
    const Object& front() const {
        return head->next->data;
    }
    Object& back() {
        return tail->prev->data;
    }
    const Object& back() const {
        return tail->prev->data;
    }
    void push_front(const Object& o) {
        insert(begin(), o);
    }
    void push_front(Object&& o) {
        insert(begin(), move(o));
    }
    void push_back(const Object& o) {
        insert(end(), o);
    }
    void push_back(Object&& o) {
        insert(end(), move(o));
    }
    void pop_back() {
        erase(--end());
    }
    void pop_front() {
        erase(begin());
    }
    iterator insert(iterator itr, const Object& x) {
        Node* p = itr.current;
        theSize++;
        Node* newNode = new Node(x, p->prev, p);
        p->prev = p->prev->next = newNode;
        return newNode;
    }
    iterator insert(iterator itr, Object&& x) {
        Node* p = itr.current;
        theSize++;
        Node* newNode = new Node(std::move(x), p->prev, p);
        p->prev = p->prev->next = newNode;
        return newNode;
    }
    iterator erase(iterator itr) {
        assertIsValid(itr);
        Node* p = itr.current;
        iterator retVal{ p->next }; //返回现在的iterator
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        theSize--;
        return retVal;
    }
    iterator erase(iterator from, iterator to) {
        while (from != to) {
            from = erase(from);
        };
        return to;
    }
    bool assertIsValid(const iterator& iter) {
        if (!iter.current || iter.current == head || iter.current == tail) {
            throw runtime_error(" iterator is valid!");
        }
    }
};
