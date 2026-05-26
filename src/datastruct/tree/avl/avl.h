#include <iostream>
#include <string>
#include <exception>
#include <memory>

using namespace std;

template<class Object, typename Comparator = less<Object>>
class AvlTree {
public:
    AvlTree() {
        root = nullptr;
    }
    ~AvlTree() {
        makeEmpty(root);
    }
    AvlTree(const AvlTree& rhs) {
        root = clone(rhs.root);
    }
    AvlTree(AvlTree&& rhs) noexcept {
        root = rhs.root;
    }
    AvlTree& operator=(const AvlTree& rhs) {
        auto temp = rhs;
        swap(*this, temp);
    }
    AvlTree& operator=(AvlTree&& rhs) noexcept {
        swap(*this, move(rhs));
    }

    const Object& findMin()const {
        auto t = findMin(root);
        if (!t) {
            throw runtime_error(" this tree is empty!");
        }
        return t->o;
    }
    const Object& findMax() const
    {
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
    struct AvlNode {
        Object o;
        AvlNode* left;
        AvlNode* right;
        int height;
        AvlNode(const Object& _o, AvlNode* _left, AvlNode* _right, int _height = 0)
            : o(_o), right(_right), left(_left), height(_height) { }
        AvlNode(Object&& _o, AvlNode* _left, AvlNode* _right, int _height = 0)
            :o(move(_o)), right(_right), left(_left), height(_height) { }
    };

    AvlNode* root;
    Comparator isLessThan;
    static const int ALLOWED_IMBALANCE = 1;
    int height(AvlNode* t)const {
        return t ? t->height : -1;
    }
    void balance(AvlNode*& t) {
        if (!t) {
            return;
        }

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
            if (height(t->left->left) >= height(t->left->right)) {
                rotateWithLeftChild(t);
            } else {
                doubleWithLeftChild(t);
            }
        } else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
            if (height(t->right->right) >= height(t->right->left)) {
                rotateWithRightChild(t);
            } else {
                doubleWithRightChild(t);
            }
        }
        t->height = max(height(t->left), height(t->right)) + 1;
    }
    void rotateWithLeftChild(AvlNode*& k2) {
        AvlNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k2 = k1;
    }
    void rotateWithRightChild(AvlNode*& k2) {
        AvlNode* k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k2 = k1;
    }

    void doubleWithLeftChild(AvlNode*& k3) {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(AvlNode*& k3) {
        rotateWithLeftChild(k3->right);
        rotateWithRightChild(k3);
    }

    void insert(const Object& o, AvlNode*& t) {
        if (!t) {
            t = new AvlNode(o, nullptr, nullptr);
        } else if (isLessThan(o, t->o)) {
            insert(o, t->left);
        } else if (isLessThan(t->o, o)) {
            insert(o, t->right);
        }
        //这里没有对相等的情况进行处理
        balance(t);
    }

    void insert(Object&& o, AvlNode*& t) {
        if (!t) {
            t = new AvlNode(move(o), nullptr, nullptr);
        } else if (isLessThan(o, t->o)) {
            insert(move(o), t->left);
        } else if (isLessThan(t->o, o)) {
            insert(move(o), t->right);
        }
        //这里没有对相等的情况进行处理
        balance(t);
    }

    void remove(const Object& o, AvlNode*& t) {
        if (!t) {
            return;
        } else if (isLessThan(o, t->o)) {
            return remove(o, t->left);
        } else if (isLessThan(t->o, o)) {
            return remove(o, t->right);
        } else if (t->right && t->left) {
            t->o = findMin(t->right)->o;
            remove(t->o, t->right);
        } else {
            AvlNode* oldNode = t;
            t = (t->left) ? t->left : t->right;
            delete oldNode;
        }
        balance(t);
    }

    AvlNode* findMin(AvlNode* t) const {
        if (!t) {
            return nullptr;
        } else if (!t->left) {
            return t;
        }
        findMin(t->left);
    }

    AvlNode* findMax(AvlNode* t)const {
        if (t) {
            while (t->right) {
                t = t->right;
            }
        }
        return t;
    }

    bool contains(const Object& o, AvlNode* t) {
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

    void makeEmpty(AvlNode*& t) {
        if (t) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullptr;
        }
    }

    void printTree(AvlNode* t, ostream& out) const {
        if (t) {
            printTree(t->left, out);
            out << t->o << endl;
            printTree(t->right, out);
        }
    }
    AvlNode* clone(AvlNode* t) const {
        return t ? new AvlNode(t->o, clone(t->left), clone(t->right)) : t;
    }
};