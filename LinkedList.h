#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {  // Linked List class for a circular linked list.
public: 
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse=false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: 
    Node<T> *head;

    int size;
};

template<class T>
LinkedList<T>::LinkedList() {  // Default Constructor
    head = NULL;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {  // Copy Constructor
    if (obj.head) {
        Node<T> *curr, *prev, *curr1;
        head = new Node<T>(obj.head->data);
        size = 1;
        curr1 =  obj.head->next;
        prev = head;
        while (curr1 != obj.head) {
            curr = new Node<T>(curr1->data);
            prev->next = curr;
            curr->prev = prev;
            size++;
            prev = curr;
            curr1 = curr1->next;
        }
        prev->next = head;
        head->prev = prev;
    }
    else {
        head = NULL;
        size = 0;
    }
}

template<class T>
LinkedList<T>::~LinkedList() {  // Destructor
    if (head) {
        Node<T> *curr, *temp;
        curr = head->next;
        while (curr != head) {
            temp = curr;
            curr = curr->next;
            delete temp;
        }
        delete head;
    }
    head = NULL;
    size = 0;
}

template<class T>
int LinkedList<T>::getSize() const {  // Returns size of the list.
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const {  // Returns whether the list is empty.
    return size < 1;
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {  // Returns whether the list contains the given node.
    if (!head)
        return false;
    if (head == node) 
        return true;
    Node<T> *curr;
    curr = head->next;
    while (curr != head) {
        if (curr == node)
            return true;
        curr = curr->next;
    }
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {  // Returns the first node in the list.
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {  // Returns the last node in the list.
    if (head)
        return head->prev;
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {  // Returns pointer to list node with given data. 
    if (!head)
        return NULL;
    if (head->data == data) 
        return head;
    Node<T> *curr;
    curr = head->next;
    while (curr != head) {
        if (curr->data == data)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

template<class T> 
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const {  // Returns pointer to list node at given index.
    if (!head)
        return NULL;
    if (index < 0 || index >= size)
        return NULL;
    if (!index)
        return head;
    Node<T> *curr;
    curr = head;
    for (int i=0;i<index;i++) 
        curr = curr->next;
    return curr;

}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) {  // Inserts a new node with given data at the front.
    Node<T> *node = new Node<T>(data);
    if (!head) {
        head = node;
        head->prev = head;
        head->next = head;
        size++;
        return;
    }
    node->next = head;
    node->prev = head->prev;
    head->prev->next = node;
    head->prev = node;
    head = node;
    size++;
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {  // Inserts a new node with given data at the front.
    Node<T> *node = new Node<T>(data);
    if (!head) {
        head = node;
        head->prev = head;
        head->next = head;
        size++;
        return;
    }
    node->next = head;
    node->prev = head->prev;
    head->prev->next = node;
    head->prev = node;
    size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) {  // Inserts a new node after the given node.
    if (!head)
        return;
    if (head == node) {
        Node<T> *temp = new Node<T>(data);
        temp->prev = head;
        temp->next = head->next;
        head->next->prev = temp;
        head->next = temp;
        size++;
        return;
    }
    Node<T> *curr;
    curr = head->next;
    while (curr != head) {
        if (curr == node) {
            Node<T> *temp = new Node<T>(data);
            temp->prev = curr;
            temp->next = curr->next;
            curr->next->prev = temp;
            curr->next = temp;
            size++;
            return;
        }
        curr = curr->next;
    }
}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k) {  // Insert a new node at every kth position. 
    if (!head)
        return;
    if (k < 2)
        return;
    int n = size / (k-1);
    Node<T> *curr;
    curr = head;
    for (int i=0;i<n;i++) {
        for (int j=0;j<k-2;j++)
            curr = curr->next;
        Node<T> *temp = new Node<T>(data);
        temp->prev = curr;
        temp->next = curr->next;
        curr->next->prev = temp;
        curr->next = temp;
        size++;
        curr = temp->next;
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {  // Removes given node from the list.
    if (!head)
        return;
    if ((head == node) && (head->next == head)) {
        delete head;
        head = NULL;
        size = 0;
        return;
    }
    if (head == node) {
        Node<T> *temp;
        temp = head;
        head->next->prev = head->prev;
        head->prev->next = head->next;
        head = head->next;
        delete temp;
        size--;
        return;
    }
    Node<T> *curr;
    curr = head->next;
    while (curr != head) {
        if (curr == node) {
            Node<T> *temp;
            temp = curr;
            curr->next->prev = curr->prev;
            curr->prev->next = curr->next;
            delete temp;
            size--; 
            return;
        }
        curr = curr->next;
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {  // Removes all nodes with given data from the list.
    if (!head)
        return;
    if ((head->data == data) && (head->next == head)) {
        delete head;
        head = NULL;
        size = 0;
        return;
    }
    while (head->data == data) {
        Node<T> *temp;
        temp = head;
        head->next->prev = head->prev;
        head->prev->next = head->next;
        head = head->next;
        delete temp;
        size--;
    }
    Node<T> *curr;
    curr = head->next;
    while (curr != head) {
        if (curr->data == data) {
            Node<T> *temp;
            temp = curr;
            curr->next->prev = curr->prev;
            curr->prev->next = curr->next;
            curr = curr->next;
            delete temp;
            size--; 
        }
        else 
            curr = curr->next;
    }
}

template<class T>
void LinkedList<T>::removeAllNodes() {  // Removes all nodes from the list.
    if (!head)
        return;
    Node<T> *curr, *temp;
    curr = head->next;
    while (curr != head) {
        temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete head;
    head = NULL;
    size = 0;
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) {  // Removes every node at the kth position.
    if (!head)
        return;
    if (k < 2)
        return;
    int n = size / k;
    Node<T> *curr;
    curr = head;
    for (int i=0;i<n;i++) {
        for (int j=0;j<k-1;j++)
            curr = curr->next;
        Node<T> *temp;
        temp = curr;
        curr->next->prev = curr->prev;
        curr->prev->next = curr->next;
        curr = curr->next;
        delete temp;
        size--;
    }
}

template<class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2) {  // Swaps the two given nodes in the list.
    if (!head)
        return;
    if (this->contains(node1) && this->contains(node2)) {
        if (head == node1) 
            head = node2;
        else if (head == node2) 
            head = node1;
        if (node1->next == node2) {
            node1->prev->next = node2;
            node2->next->prev = node1;
            node1->next = node2->next;
            node2->prev = node1->prev;
            node1->prev = node2;
            node2->next = node1;
            return;
        }
        if (node2->next == node1) {
            node2->prev->next = node1;
            node1->next->prev = node2;
            node2->next = node1->next;
            node1->prev = node2->prev;
            node2->prev = node1;
            node1->next = node2;
            return;
        }
        Node<T> *p1, *p2; 
        node1->prev->next = node2;
        node1->next->prev = node2;
        node2->prev->next = node1;
        node2->next->prev = node1;
        p1 = node1->next;
        p2 = node1->prev;
        node1->next = node2->next;
        node1->prev = node2->prev;
        node2->next = p1;
        node2->prev = p2;
    }
}

template<class T>
void LinkedList<T>::shuffle(int seed) {  // Shuffles list elements with a given seed.
    if (!head)
        return;
    for (int i=0;i<size;i++) 
        this->swap(getNodeAtIndex(i),getNodeAtIndex((i*i+seed)%size));
}

template<class T>
void LinkedList<T>::print(bool reverse) const {  // Prints the linked list.
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse) {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do {
            std::cout << *node << std::endl;
            node = node->prev;
        }
        while (node != this->getLastNode());
    } else {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do {
            std::cout << *node << std::endl;
            node = node->next;
        }
        while (node != this->getFirstNode());
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {  // Overloaded assignment operator.
    if (head) {
        Node<T> *curr, *temp;
        curr = head->next;
        while (curr != head) {
            temp = curr;
            curr = curr->next;
            delete temp;
        }
        delete head;
        head = NULL;
        size = 0;
    }
    if (!rhs.head)
        return *this;
    Node<T> *curr, *prev, *curr1;
    head = new Node<T>(rhs.head->data);
    size = 1;
    curr1 =  rhs.head->next;
    prev = head;
    while (curr1 != rhs.head) {
        curr = new Node<T>(curr1->data);
        prev->next = curr;
        curr->prev = prev;
        size++;
        prev = curr;
        curr1 = curr1->next;
    }
    prev->next = head;
    head->prev = prev; 
    return *this;
}

#endif //LINKEDLIST_H