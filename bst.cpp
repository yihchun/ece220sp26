#include <iostream>

template <class T>
class BSTree;

template <class T>
class BSTIterator;

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
    friend class BSTIterator<T>;
};

template <class T>
class BSTIterator : public std::iterator<std::forward_iterator_tag, T> {
public:
    BSTIterator() { }
    BSTIterator(BSTNode<T> *root) { initalize(root); }
    BSTIterator(const BSTIterator &from) { loc = from.loc; }
    BSTIterator &operator=(const BSTIterator &from) {
        loc = from.loc; return *this; }
    bool operator==(const BSTIterator &with) const {
        return loc == with.loc; }
    bool operator!=(const BSTIterator &with) const {
        return loc != with.loc; }
    BSTIterator operator++() { step(); return *this; }
    BSTIterator operator++(int) {
        BSTIterator tmp(*this); step(); return tmp; }
    T &operator*() const { return loc.top().first->data; }
private:
    void initalize(BSTNode<T> *root) {
        while (root) {
            loc.push(std::make_pair(root, 0));
            root = root->left;
        }
        if (!loc.empty())
            loc.top().second++;
    }
    void step() {
        if (loc.empty()) return;
        do {
            switch (loc.top().second) {
            case 0:
                loc.top().second++;
                break;
            case 1:
                loc.top().second++;
                if (loc.top().first->right) {
                    BSTNode<T> *walk = loc.top().first->right;
                    while (walk) {
                        loc.push(std::make_pair(walk, 0));
                        walk = walk->left;
                    }
                    loc.top().second++;
                }
                break;
            case 2:
                loc.pop();
                break;
            }
        } while (!loc.empty() && loc.top().second != 1);
    }
    std::stack<std::pair<BSTNode<T> *, int> > loc;
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
            tmp->right = nullptr;
        } else {
            *walk = (*walk)->left;
            tmp->left = nullptr;
        }
        delete tmp;
    }

    BSTIterator<T> begin() const { return BSTIterator<T>(root); }
    BSTIterator<T> end() const { return BSTIterator<T>(); }

};

int main() {
    BSTree<int> t;
    BSTree<int> t2;
    const BSTree<int> *x = &t;
    t.insert(5).insert(6).insert(3).insert(4).insert(7);
    std::cout << t.search(3) << std::endl;
    std::cout << t.search(7) << std::endl;
    std::cout << t.search(67) << std::endl;
    std::cout << t.height() << std::endl;
    x->print_inorder();
    for (auto v: t2)
        std::cout << v << " ";
    std::cout << "\n";
    
    t.delete_node(5);
    t.print_inorder();
    for (BSTIterator<int> it = t.begin(); it != t.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    t.delete_node(3);
    t.print_inorder();
    t.delete_node(4);
    t.print_inorder();
    t.delete_node(6);
    t.print_inorder();
    t.delete_node(7);
    t.print_inorder();
    for (BSTIterator<int> it = t.begin(); it != t.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // not allowed: x->insert(0);
    return 0;
}

