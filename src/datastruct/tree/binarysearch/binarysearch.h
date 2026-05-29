#include <memory>
#include <iostream>
#include <string>
#include <exception>
#include <stack>

template<class Object, typename Comparator = std::less<Object>>
class BinarySearchTree {
public:
    BinarySearchTree() {
        root = nullptr;
    }

    ~BinarySearchTree() {
        makeEmpty(root);
    }

    BinarySearchTree(const BinarySearchTree& rhs) {
        root = clone(rhs.root);
    }

    BinarySearchTree(BinarySearchTree&& rhs) noexcept {
        root = rhs.root;
    }

    BinarySearchTree& operator=(const BinarySearchTree& rhs) {
        auto temp = rhs;
        swap(*this, temp);
    }

    BinarySearchTree& operator=(BinarySearchTree&& rhs) noexcept {
        swap(*this, move(rhs));
    }

    const Object& findMin() const {
        auto t = findMin(root);
        if (!t) {
            throw runtime_error(" this tree is empty!");
        }
        return t->o;
    }

    const Object& findMax() const {
        auto t = findMax(root);
        if (!t) {
            throw runtime_error(" this tree is empty!");
        }
        return t->o;
    }

    bool contain(const Object& o) const {
        return contain(o, root);
    }

    bool isEmpty() const {
        return root->left || root->right;
    }

    void printTree(ostream& out = cout) const {
        printTree(root, out);
    }

    void makeEmpty() {
        makeEmpty(root);
    }

    void insert(const Object& o) {
        insert(o, root);
    }

    void insert(Object&& o) {
        insert(move(o), root);
    }

    void remove(const Object& o) {
        remove(o, root);
    }

private:
    struct BinaryNode {
        Object o;
        BinaryNode* left;
        BinaryNode* right;
        BinaryNode(const Object& _o, BinaryNode* _left, BinaryNode* _right) : o(_o), right(_right), left(_left) {}
        BinaryNode(Object&& _o, BinaryNode* _left, BinaryNode* _right) : o(move(_o)), right(_right), left(_left) {}
    };

    void insert(const Object& o, BinaryNode*& t) {
        while (t) {
            if (isLessThan(o, t->o)) {
                t = t->left;
            } else {
                t = t->right;
            }
        }

        t = new BinaryNode(o, nullptr, nullptr);
    }

    void insert(Object&& o, BinaryNode*& t) {
        while (t) {
            if (isLessThan(o, t->o)) {
                t = t->left;
            } else {
                t = t->right;
            }
        }

        t = new BinaryNode(std::move(o), nullptr, nullptr);
    }

    void remove(const Object& o, BinaryNode* t) {
        BinaryNode *parent = nullptr;
        while (t) {
            if (isLessThan(o, t->o)) {
                parent = t;
                t = t->left;
            } else if (isLessThan(t->o, o)) {
                parent = t;
                t = t->right;
            }

            if (t->right) {
                BinaryNode* min = findMin(t->right);
                t->o = min->o;
                return remove(min->o, min);
            }

            if (parent) {
                if (parent->left == t) {
                    parent->left = t->left;
                } else {
                    parent->right = t->left;
                }
            }
            delete t;
        }
    }

    BinaryNode* findMin(BinaryNode* t) const {
        if (t) {
            while (t->left) {
                t = t->left;
            }
        }

        return t;
    }

    BinaryNode* findMax(BinaryNode* t) const {
        if (t) {
            while (t->right) {
                t = t->right;
            }
        }

        return t;
    }

    bool contains(const Object& o, BinaryNode* t) {
        while (t) {
            if (isLessThan(o, t->o)) {
                t = t->left;
            } else if (isLessThan(t->o, o)) {
                t = t->right;
            }

            return true;
        }

        return false;
    }

    void makeEmpty(BinaryNode* t) {
        if (!t) {
            return;
        }

        std::stack<BinaryNode*> s;
        s.push(t);
        while (!s.empty()) {
            t = s.top();
            if (t->left) {
                s.push(t->left);
            }

            if (t->right) {
                s.push(t->right);
            }

            delete t;
        }
    }

    void printTree(BinaryNode* t, ostream& out) const {
        if (!t) {
            return;
        }

        std::stack<BinaryNode*> s;
        s.push(t);
        while (!s.empty()) {
            t = s.top();
            if (t->left) {
                s.push(t->left);
            }

            if (t->right) {
                s.push(t->right);
            }

            out << t->val << " ";
        }
    }

    BinaryNode* clone(BinaryNode* t) const {
        return t ? new BinaryNode(t->o, clone(t->left), clone(t->right)) : t;
    }

private:
    BinaryNode* root;
    Comparator isLessThan;
};
