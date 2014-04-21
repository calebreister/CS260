#ifndef DOUBLY_LINKED_LIST_HH
#define DOUBLY_LINKED_LIST_HH

#include <string>
#include <iostream>

template<class DataType>
struct Node {
    DataType data;
    Node<DataType>* prev;
    Node<DataType>* next;
};

template<class DataType>
class DoublyLinkedList {
    private:
    Node<DataType>* head;
    Node<DataType>* tail;
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
    void print(std::ostream& output);
    void printReverse(std::ostream& output);
};

/////////////////////////////////////////////////////////////////////////////////////
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

template<class DataType>
void DoublyLinkedList<DataType>::removeNode(Node<DataType>* n) {
    if (n != NULL)
    {
        removeNode(n->next);
        delete n;
    }
}

template<class DataType>
bool DoublyLinkedList<DataType>::checkData(Node<DataType>* newNode, Node<DataType>* oldNode) {
    if (newNode->data == oldNode->data)
    {
        delete newNode;
        return true;
    }
    return false;
}

/**@brief Insert data into the list
 * @param data The string of data to add
 * @return Data inserted: true\n
 *         Duplicate data: false
 *
 * Notes:\n
 * - Duplicate data is not accepted\n
 * - The list is automatically organized alphabetically
 */
template<class DataType>
bool DoublyLinkedList<DataType>::insert(DataType data) {
    //no inserting a blank string
    if (data == "")
        return false;

    //Initialize
    Node<DataType>* n = new Node<DataType>;
    n->data = data;

    if (head == NULL)  //list empty?
    {
        head = n;
        tail = n;
    }
    else if (head->next == NULL && n->data <= head->data)  //1st item?
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
 * @param data The string to remove
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

///@brief Erases the contents of the linked list
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

//NOT UPDATED, overload operator
///@brief Prints the list to any output stream
///@param output The output stream to use
template<class DataType>
void DoublyLinkedList<DataType>::print(std::ostream& output) {
    if (head != NULL)
    {
        Node<DataType>* n = head;
        while (n->next != NULL)
        {
            output << n->data << std::endl;
            n = n->next;
        }
        output << n->data << std::endl << std::endl;
    }
}

template<class DataType>
void DoublyLinkedList<DataType>::printReverse(std::ostream& output) {
    if (head != NULL)
        {
            Node<DataType>* n = tail;
            while (n->prev != NULL)
            {
                output << n->data << std::endl;
                n = n->prev;
            }
            output << n->data << std::endl << std::endl;
        }
}


#endif
