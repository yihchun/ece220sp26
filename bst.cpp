#include <iostream>

template <class T>
class BSTree;

template <class T>
class BSTNode {
    BSTNode(const T &d) : data(d) { left = right = nullptr; }
    ~BSTNode() { delete left; delete right; }

    void print_inorder() const {
        if (left) left->print_inorder();
        std::cout << data << " ";
        if (right) right->print_inorder();
    }

    bool search(const T &d) const {
        if (d == data) return true;
        if (d < data) {
            return left && left->search(d);
        }
        return right && right->search(d);
    }

    unsigned int height() const {
        unsigned int lh, rh;
        lh = left  ?  left->height() : 0;
        rh = right ? right->height() : 0;
        return 1+std::max(lh,rh);
    }
    
    T data;
    BSTNode<T> *left;
    BSTNode<T> *right;
    friend class BSTree<T>;
};

template <class T>
class BSTree {
    BSTNode<T> *root;

public:
    BSTree() { root = nullptr; }
    ~BSTree() { delete root; }
    BSTree<T> &insert(const T &data) {
        BSTNode<T> **walk = &root;
        while (*walk) {
            if (data <= (*walk)->data) {
                walk = &((*walk)->left);
            } else {
                walk = &((*walk)->right);
            }
        }
        *walk = new BSTNode<T>(data);
        return *this;
    }
    bool search(const T &data) const {
        return root && root->search(data);
    }
    void print_inorder() const {
        if (root)
            root->print_inorder();
        std::cout << std::endl;
    }
    unsigned int height() const {
        if (!root) return 0;
        return root->height();
    }
    void delete_node(const T &data) {
        BSTNode<T> **walk = &root;
        while (*walk) {
            if (data == (*walk)->data)
                break;
            if (data < (*walk)->data) {
                walk = &((*walk)->left);
            } else {
                walk = &((*walk)->right);
            }
        }
        if (!*walk) return;
        if ((*walk)->left && (*walk)->right) {
            BSTNode<T> **walk2 = &((*walk)->left);
            while ((*walk2)->right)
                walk2 = &((*walk2)->right);
            (*walk)->data = (*walk2)->data;
            walk = walk2;
        }
        BSTNode<T> *tmp = *walk;
        if ((*walk)->right) {
            *walk = (*walk)->right;
        } else {
            *walk = (*walk)->left;
        }
        delete tmp;
    }

};

int main() {
    BSTree<int> t;
    const BSTree<int> *x = &t;
    t.insert(5).insert(6).insert(3).insert(4).insert(7);
    std::cout << t.search(3) << std::endl;
    std::cout << t.search(7) << std::endl;
    std::cout << t.search(67) << std::endl;
    std::cout << t.height() << std::endl;
    x->print_inorder();
    t.delete_node(5);
    t.print_inorder();
    // not allowed: x->insert(0);
    return 0;
}

