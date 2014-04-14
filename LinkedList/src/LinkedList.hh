/**@file LinkedList.hh
 * @author Caleb Reister
 * @brief Header for simple LinkedList class
 */

#ifndef LINKED_LIST_HH
#define LINKED_LIST_HH

#include <string>
#include <iostream>

///@brief Defines a string node for a linked list
struct Node {
    std::string data = "";
    Node* next = NULL;
};

///@brief Defines a simple linked list
class LinkedList {
    private:
    Node* head;
    unsigned int count; ///the number of items in the list
    void removeNode(Node* n);

    public:
    LinkedList();
    ~LinkedList();
    bool insert(std::string data);
    bool remove(std::string data);
    void removeAll();
    unsigned int getCount();
    void print(std::ostream& output);
};

#endif
