#include <memory>
#include <iostream>
#include <string>
#include <exception>

using namespace std;

template<class Object, typename Comparator = less<Object>>
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

    const Object& findMin()const {
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
        BinaryNode(const Object& _o, BinaryNode* _left, BinaryNode* _right) :o(_o), right(_right), left(_left) {}
        BinaryNode(Object&& _o, BinaryNode* _left, BinaryNode* _right) :o(move(_o)), right(_right), left(_left) {}
    };
    BinaryNode* root;
    Comparator isLessThan;
    void insert(const Object& o, BinaryNode*& t) {
        if (!t) {
            t = new BinaryNode(o, nullptr, nullptr);
        } else if (isLessThan(o, t->o)) {
            insert(o, t->left);
        } else if (isLessThan(t->o, o)) {
            insert(o, t->right);
        }
        //这里没有对相等的情况进行处理
    }

    void insert(Object&& o, BinaryNode*& t) {
        if (!t) {
            t = new BinaryNode(move(o), nullptr, nullptr);
        } else if (isLessThan(o, t->o)) {
            insert(move(o), t->left);
        }
        else if (isLessThan(t->o, o))
        {
            insert(move(o), t->right);
        }
        //这里没有对相等的情况进行处理
    }
    void remove(const Object& o, BinaryNode*& t) {
        if (!t) {
            return nullptr;
        } else if (isLessThan(o, t->o)) {
            return remove(o, t->left);
        } else if (islessThan(t->o, o)) {
            return remove(o, t->right);
        } else if (t->right && t->left) {
            t->o = findMin(t->right)->o;
            remove(t->o, t->right);
        } else {
            BinaryNode* oldNode = t;
            t = (t->left) ? t->left : t->right;
            delete oldNode;
        }
    }

    BinaryNode* findMin(BinaryNode* t) const {
        if (!t) {
            return nullptr;
        } else if (!t->left) {
            return t;
        }
        findMin(t->left);
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
        if (!t) {
            return false;
        } else if (isLessThan(o, t->o)) {
            return contain(o, t->left);
        } else if (isLessThan(t->o, o)) {
            return contain(o, t->right);
        } else {
            return true;
        }
    }
    void makeEmpty(BinaryNode*& t) {
        if (t) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullptr;
        }
    }
    void printTree(BinaryNode* t, ostream& out) const {
        if (t) {
            printTree(t->left, out);
            out << t->o << endl;
            printTree(t->right, out);
        }
    }
    BinaryNode* clone(BinaryNode* t) const {
        return t ? new BinaryNode(t->o, clone(t->left), clone(t->right)) : t;
    }
};
