#include "DoublyLinkedList.hh"
using namespace std;

DoublyLinkedList::DoublyLinkedList() {
    head = NULL;
    tail = NULL;
    count = 0;
}

DoublyLinkedList::~DoublyLinkedList() {
    removeAll();
}

void DoublyLinkedList::removeNode(Node* n) {
    if (n != NULL)
    {
        removeNode(n->next);
        delete n;
    }
}

bool DoublyLinkedList::checkData(Node* newNode, Node* oldNode) {
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
bool DoublyLinkedList::insert(std::string data) {
    //Initialize
    Node* n = new Node;
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
        n->prev = tail;
        tail->next = n;
        tail = n;
    }
    else  //insert in the middle
    {
        Node* current = head->next;
        //find where to insert
        while (current->data < n->data)
            current = current->next;

        //check the data
        if (checkData(n, current->next))
            return false;

        //update pointers
        n->next = current;
        n->prev = current->prev;
        current->prev->next = n;
        current->prev = n;
    }

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
bool DoublyLinkedList::remove(std::string data) {
    if (head == NULL)  //No data in the list
        return false;

    if (data == head->data)  //remove 1st item
    {
        Node* temp = head;
        head = head->next;
        delete temp;
        count--;
        return true;
    }
    /*else if (data == head->next->data) //2 items
     {
     Node* temp = head;
     head = head->next;
     }*/
    else if (data == tail->data)  //last item
    {
        Node* temp = tail;
        tail = tail->prev;
        delete temp;
        count--;
        return true;
    }

    //find node to delete
    Node* current = head;
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

//NOT YET UPDATED
///@brief Erases the contents of the linked list
void DoublyLinkedList::removeAll() {
    Node* newHead;
    while (head->next != NULL)
    {
        newHead = head->next;
        delete head;
        head = newHead;
    }
    delete head;
    head = NULL;
    tail = NULL;
}

/**@brief Get the number of items in the list
 * @return The number of items in the linked list
 *  as an unsigned int.
 */
unsigned int DoublyLinkedList::getCount() {
    return count;
}

//NOT UPDATED, overload operator
///@brief Prints the list to any output stream
///@param output The output stream to use
void DoublyLinkedList::print(std::ostream& output) {
    Node* n = head;
    while (n->next != NULL)
    {
        output << n->data << endl;
        n = n->next;
    }
    output << n->data << endl << endl;
}
