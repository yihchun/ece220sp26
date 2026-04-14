#include <iostream>

template <class T>
class List;

template <class T>
class Node {
public:
    T data;
    Node (T new_data) {
        data = new_data;
        next = nullptr;
    }
private:
    Node<T> *next;
    friend class List<T>;
};

template <class T>
class List {
    List() {
        head = nullptr;
    }
    ~List() {
        Node<T> *walk;
        if (!head) return;
        while (walk=head->next) {
            delete head;
            head = walk;
        }
        delete head;
    }
    void insert(T new_data) {
    }
private:
    Node<T> *head;
}
