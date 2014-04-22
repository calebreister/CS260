/**@file DoublyLinkedList.hh
 * @author Caleb Reister <calebreister@gmail.com>
 * @brief Declaration and implementation of the
 * DoublyLinkedList class template
 */

#ifndef DOUBLY_LINKED_LIST_HH
#define DOUBLY_LINKED_LIST_HH

#include <string>
#include <iostream>

/////////////////////////////////////////////////////////////////////////
//PROTOTYPES
template<class DataType>
class DoublyLinkedList;

template<class DataType>
std::ostream& operator<<(std::ostream& stream,
                         const DoublyLinkedList<DataType>& data);

template<class DataType>
bool operator==(const DoublyLinkedList<DataType>& a,
                const DoublyLinkedList<DataType>& b);

template<class DataType>
bool operator!=(const DoublyLinkedList<DataType>& a,
                const DoublyLinkedList<DataType>& b);

template<class DataType>
bool operator>(const DoublyLinkedList<DataType>& a,
               const DoublyLinkedList<DataType>& b);

template<class DataType>
bool operator<(const DoublyLinkedList<DataType>& a,
               const DoublyLinkedList<DataType>& b);

template<class DataType>
bool operator>=(const DoublyLinkedList<DataType>& a,
                const DoublyLinkedList<DataType>& b);

template<class DataType>
bool operator<=(const DoublyLinkedList<DataType>& a,
                const DoublyLinkedList<DataType>& b);

//////////////////////////////////////////////////////////////
//CLASS DECLARATIONS
///@brief A singe node for a DoublyLinkedList
template<class DataType>
struct Node {
    DataType data;
    Node<DataType>* prev;
    Node<DataType>* next;
};

template<class DataType>
class DoublyLinkedList {
    private:
    Node<DataType>* head;  ///the beginning of the list
    Node<DataType>* tail;  ///the end of the list
    unsigned int count;  ///the number of items in the list
    void removeNode(Node<DataType>* n);
    bool checkData(Node<DataType>* newNode, Node<DataType>* oldNode);

    public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    bool insert(DataType data);
    bool remove(DataType data);
    void removeAll();
    unsigned int getCount();
    void printReverse(std::ostream& output);
    //operator overloads
    DoublyLinkedList<DataType>& operator=(const DoublyLinkedList<DataType>& data);
    friend std::ostream& operator<< <>(std::ostream& stream,
                                       const DoublyLinkedList& data);
    friend bool operator== <>(const DoublyLinkedList& a,
                              const DoublyLinkedList& b);
    friend bool operator!= <>(const DoublyLinkedList& a,
                              const DoublyLinkedList& b);
    friend bool operator> <>(const DoublyLinkedList& a,
                             const DoublyLinkedList& b);
    friend bool operator< <>(const DoublyLinkedList& a,
                             const DoublyLinkedList& b);
    friend bool operator>= <>(const DoublyLinkedList& a,
                              const DoublyLinkedList& b);
    friend bool operator<= <>(const DoublyLinkedList& a,
                              const DoublyLinkedList& b);
};

/////////////////////////////////////////////////////////////////////////////////////
//MEMBERS
template<class DataType>
DoublyLinkedList<DataType>::DoublyLinkedList() {
    head = NULL;
    tail = NULL;
    count = 0;
}

template<class DataType>
DoublyLinkedList<DataType>::~DoublyLinkedList() {
    removeAll();
}

/**@brief Remove a single node from the list and resolve the broken link
 * @param n The node to remove
 */
template<class DataType>
void DoublyLinkedList<DataType>::removeNode(Node<DataType>* n) {
    if (n != NULL)
    {
        removeNode(n->next);
        delete n;
    }
}

/**@brief Checks Nodes for equality, and deletes the new one if they are the
 * the same, useful when adding a new Node to the list.
 * @param newNode The Node that is deleted conditionally
 * @param oldNode The Node to check newNode against
 * @return true if the nodes are equal
 */
template<class DataType>
bool DoublyLinkedList<DataType>::checkData(Node<DataType>* newNode,
                                           Node<DataType>* oldNode) {
    if (newNode->data == oldNode->data)
    {
        delete newNode;
        return true;
    }
    return false;
}

/**@brief Insert data into the list
 * @param data The data of data to add, can be any type with the
 * appropriate operators.
 * @return Data inserted: true\n
 *         Duplicate data: false
 *
 * Notes:\n
 * - Duplicate data is not accepted\n
 * - The list is automatically organized alphabetically
 */
template<class DataType>
bool DoublyLinkedList<DataType>::insert(DataType data) {
    //Initialize
    Node<DataType>* n = new Node<DataType>;
    n->data = data;

    if (head == NULL)  //list empty?
    {
        head = n;
        tail = n;
    }
    else if (n->data <= head->data)  //1st item?
    {
        if (checkData(n, head))
            return false;
        n->next = head;
        head->prev = n;
        head = n;
    }
    else if (n->data >= tail->data)  //last item?
    {
        if (checkData(n, tail))
            return false;
        tail->next = n;
        n->prev = tail;
        tail = n;
    }
    else  //insert in the middle
    {
        Node<DataType>* current = head;
        //find where to insert
        while (current->data < n->data)
            current = current->next;

        //check the data
        if (checkData(n, current))
            return false;

        //update pointers
        n->next = current;
        n->prev = current->prev;
        current->prev->next = n;
        current->prev = n;
    }

    //make sure head does not have a previous and tail
    //does not have a next pointer
    tail->next = NULL;
    head->prev = NULL;

    count++;
    return true;
}

/**@brief Removes the specified data from the linked list
 * @param data The data to remove, any type with the appropriate operators
 * @return True if data was removed, false otherwise.
 *
 * Notes:\n
 * - True is returned only when the data was inserted
 * - If the data does not exist for any reason, false is returned\n\n
 *
 * False is not necessarily an error condition, it just means that
 * the data was not found in the list.
 */
template<class DataType>
bool DoublyLinkedList<DataType>::remove(DataType data) {
    if (head == NULL)  //No data in the list
        return false;

    else if (data == head->data)  //remove 1st item
    {
        Node<DataType>* temp = head;
        head = head->next;
        delete temp;
        count--;
        if (count == 0)
        {
            delete head;
            head = NULL;
            tail = NULL;
        }
        return true;
    }
    else if (data == tail->data)  //last item
    {
        Node<DataType>* temp = tail;
        tail = tail->prev;
        delete temp;
        tail->next = NULL;
        count--;
        return true;
    }

    //find node to delete
    Node<DataType>* current = head;
    while (current != NULL)
    {
        current = current->next;
        if (current->data == data)
        {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            count--;
            return true;
        }
    }

    return false;
}

///@brief Erases the contents of the linked list and cleans up appropriately
template<class DataType>
void DoublyLinkedList<DataType>::removeAll() {
    if (count > 0)
    {
        Node<DataType>* newHead;
        while (head->next != NULL)
        {
            newHead = head->next;
            delete head;
            head = newHead;
        }
        //assert(head == tail);
        count = 0;
        delete head;
        head = NULL;
        tail = NULL;
    }
}

/**@brief Get the number of items in the list
 * @return The number of items in the linked list
 *  as an unsigned int.
 */
template<class DataType>
unsigned int DoublyLinkedList<DataType>::getCount() {
    return count;
}

///@brief Prints the list in reverse to the specified output stream
template<class DataType>
void DoublyLinkedList<DataType>::printReverse(std::ostream& stream) {
    if (head != NULL)
    {
        Node<DataType>* n = tail;
        while (n->prev != NULL)
        {
            stream << n->data << std::endl;
            n = n->prev;
        }
        stream << n->data << std::endl << std::endl;
    }
}

/////////////////////////////////////////////////////////////////////////////////
//OPERATORS
///@brief Performs a deep copy of the list
///
///NOTE: this process may be taxing depending on the size of the list, as
///all of the contents are copied.\n\n
///This function has been fully tested, and the addresses are all different according
///to the debugger.
template<class DataType>
DoublyLinkedList<DataType>&
DoublyLinkedList<DataType>::operator=(const DoublyLinkedList<DataType>& data) {
    if (this == &data)
        return *this;

    this->removeAll();
    Node<DataType>* current = data.head;
    while (current != NULL) {
        this->insert(current->data);
        current = current->next;
    }
    return *this;
}

///@brief prints the list from head to tail, each node on a new line
template<class DataType>
std::ostream& operator<<(std::ostream& stream,
                         const DoublyLinkedList<DataType>& data) {
    if (data.head != NULL)
    {
        Node<DataType>* n = data.head;
        while (n->next != NULL)
        {
            stream << n->data << std::endl;
            n = n->next;
        }
        stream << n->data << std::endl << std::endl;
    }

    return stream;
}

///@brief checks the two lists for equality, checks counts first
template<class DataType>
bool operator==(const DoublyLinkedList<DataType>& a,
                const DoublyLinkedList<DataType>& b) {
    if (a.count != b.count)
        return false;

    Node<DataType>* currentA = a.head;
    Node<DataType>* currentB = b.head;
    while (currentA != NULL && currentB != NULL)
    {
        if (currentA->data != currentB->data)
            return false;
        currentA = currentA->next;
        currentB = currentB->next;
    }
    return true;
}

template<class DataType>
bool operator!=(const DoublyLinkedList<DataType>& a,
                const DoublyLinkedList<DataType>& b) {
    return a == b ? false : true;
}

///@return true if a > b, false if not or if the counts are different
template<class DataType>
bool operator>(const DoublyLinkedList<DataType>& a,
               const DoublyLinkedList<DataType>& b) {
    if (a.count != b.count)
        return false;

    Node<DataType>* currentA = a.head;
    Node<DataType>* currentB = b.head;
    while (currentA != NULL && currentB != NULL)
    {
        if (currentA->data <= currentB->data)
            return false;
        currentA = currentA->next;
        currentB = currentB->next;
    }
    return true;
}

///@return true if a < b, false if not or if the counts are different
template<class DataType>
bool operator<(const DoublyLinkedList<DataType>& a,
               const DoublyLinkedList<DataType>& b) {
    if (a.count != b.count)
        return false;

    Node<DataType>* currentA = a.head;
    Node<DataType>* currentB = b.head;
    while (currentA != NULL && currentB != NULL)
    {
        if (currentA->data >= currentB->data)
            return false;
        currentA = currentA->next;
        currentB = currentB->next;
    }
    return true;
}

///@return true if a >= b, false if not or if the counts are different
template<class DataType>
bool operator>=(const DoublyLinkedList<DataType>& a,
                const DoublyLinkedList<DataType>& b) {
    if (a.count != b.count)
        return false;

    Node<DataType>* currentA = a.head;
    Node<DataType>* currentB = b.head;
    while (currentA != NULL && currentB != NULL)
    {
        if (currentA->data < currentB->data)
            return false;
        currentA = currentA->next;
        currentB = currentB->next;
    }
    return true;
}

///@return true if a <= b, false if not or if the counts are different
template<class DataType>
bool operator<=(const DoublyLinkedList<DataType>& a,
                const DoublyLinkedList<DataType>& b) {
    if (a.count != b.count)
        return false;

    Node<DataType>* currentA = a.head;
    Node<DataType>* currentB = b.head;
    while (currentA != NULL && currentB != NULL)
    {
        if (currentA->data > currentB->data)
            return false;
        currentA = currentA->next;
        currentB = currentB->next;
    }
    return true;
}

#endif
