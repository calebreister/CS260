#ifndef DOUBLY_LINKED_LIST_HH
#define DOUBLY_LINKED_LIST_HH

#include <string>
#include <iostream>

struct Node {
    std::string data;
    Node* prev;
    Node* next;
};

class DoublyLinkedList {
    private:
    Node* head;
    Node* tail;
    unsigned int count;  ///the number of items in the list
    void removeNode(Node* n);
    bool checkData(Node* newNode, Node* oldNode);

    public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    bool insert(std::string data);
    bool remove(std::string data);
    void removeAll();
    unsigned int getCount();
    void print(std::ostream& output);
    void printReverse(std::ostream& output);
};

#endif
