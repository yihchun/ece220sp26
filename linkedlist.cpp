#include <iostream>

template <class T>
class List;

template <class T>
class LinkedListIterator;

template <class T>
class Node {
public:
    T data;
    Node (T new_data) {
        data = new_data;
        next = nullptr;
    }
    ~Node() { std::cout << this << " getting freed\n"; }
private:
    Node<T> *next;
    friend class List<T>;
    friend class LinkedListIterator<T>;
};

template <class T>
class LinkedListIterator : public std::iterator<std::forward_iterator_tag, T> {
public:
    LinkedListIterator() { loc = nullptr; }
    LinkedListIterator(Node<T> *l) { loc = l; }
    LinkedListIterator(const LinkedListIterator &from) { loc = from.loc; }
    LinkedListIterator &operator=(const LinkedListIterator &from) {
        loc = from.loc; return *this; }
    bool operator==(const LinkedListIterator &with) const {
        return loc == with.loc; }
    bool operator!=(const LinkedListIterator &with) const {
        return loc != with.loc; }
    LinkedListIterator operator++() { loc = loc->next; return *this; }
    LinkedListIterator operator++(int) {
        LinkedListIterator tmp(*this);
        loc = loc->next; return tmp; }
    T &operator*() const { return loc->data; }

private:
    Node<T> *loc;
};

template <class T>
class smartptr {
public:
    smartptr() { ptr = nullptr; refct = nullptr; }
    smartptr(T *p) { ptr = p; refct = new unsigned int(1); }
    ~smartptr() { demote(); }
    smartptr(smartptr<T> &from) {
        ptr = from.ptr; refct = from.refct; (*refct)++; }
    smartptr &operator=(smartptr<T> &from) { demote();
        ptr = from.ptr; refct = from.refct; (*refct)++; return *this; }
    smartptr &operator=(T *p) { demote(); ptr = p; refct = new unsigned int(1); }
    T &operator*() { return *ptr; }
    
private:
    void demote() {
        if (!refct) return;
        (*refct)--;
        if (*refct == 0) {
            std::cout << ptr << " getting freed by smartptr\n";
            delete ptr; delete refct;
        }
    }
    
    T *ptr;
    unsigned int *refct;
};

template <class T>
class List {
public:
    List() {
        head = nullptr;
    }
    ~List() {
        Node<T> *walk;
        if (!head) return;
        while ((walk=head->next)) {
            delete head;
            head = walk;
        }
        delete head;
    }
    void insert(T new_data) {
        Node<T> *mynode = new Node<T>(new_data);
        mynode->next = head;
        head = mynode;
        /* head = new Node<T>(new_data, head); */
    }

    LinkedListIterator<T> begin() const { return LinkedListIterator<T>(head); }
    LinkedListIterator<T> end() const { return LinkedListIterator<T>(); }
private:
    Node<T> *head;
};

int main() {
    List<int> l;
    l.insert(1);
    l.insert(2);
    l.insert(3);

    for (auto it = l.begin(); it != l.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for (auto a: l) {
        std::cout << a << " ";
    }
    std::cout << std::endl;

    smartptr<int> p(new int(2));
    smartptr<int> q(new int(3));
    p = q;
    smartptr<int> r(q);
    std::cout << *p << std::endl;
}
