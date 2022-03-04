#ifndef NODE_H
#define NODE_H


#include <iostream>

template<class T>
class Node {  // Node class for a circular linked list implementation.
public:
    T data;
    Node<T> *prev;
    Node<T> *next;

    Node(T data) {  // First custom constructor.
        this->data = data;
        this->prev = NULL;
        this->next = NULL;
    }

    Node(T data, Node<T> *prev, Node<T> *next) {  // Second custom constructor
        this->data = data;
        this->prev = prev;
        this->next = next;
    }

    friend std::ostream &operator<<(std::ostream &os, const Node &node) {  // Overloaded operator to print node to output stream.
        os << node.data;

        return os;
    }
};

#endif //NODE_H
