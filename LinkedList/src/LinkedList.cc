/**@file LinkedList.cc
 * @author Caleb Reister
 * @brief Implementation for simple LinkedList class
 */

#include <exception>
#include "LinkedList.hh"
using namespace std;

LinkedList::LinkedList() {
    head = NULL;
    count = 0;
}

LinkedList::~LinkedList() {
    //head = NULL;
    removeAll();
    delete head;
}

/**@brief Remove a single node
 * @param n The node to remove
 * This function removes a single node from the Linked List
 * and resolves the link to make it continuous.
 */
void LinkedList::removeNode(Node* n) {
    if (n != NULL)
    {
        removeNode(n->next);
        delete n;
    }
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
bool LinkedList::insert(std::string data) {
    //Initialize
    Node* n = new Node;
    n->data = data;

    if (head == NULL)  //list empty?
        head = n;
    else if (head->next == NULL && n->data <= head->data)  //1st item?
    {
        if (n->data == head->data)
        {
            delete n;
            return false;
        }
        else
        {
            n->next = head;
            head = n;
        }
    }
    else  //insert in the middle or at the end
    {
        Node* prev = head;
        //figure out where to insert
        while (prev->next != NULL &&
               prev->next->data <= n->data)
        {
            if (prev->next->data == n->data)  //check for duplicate data
            {
                delete n;
                return false;
            }
            prev = prev->next;
        }
        n->next = prev->next;  //insert data
        prev->next = n;
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
 * There was not error if false was returned.
 */
bool LinkedList::remove(std::string data) {
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
    /*else if (data == head->next->data) //remove 2nd item
     {
     Node* temp = head;
     head =
     }*/

    //find node to delete
    Node* current = head;
    Node* prev = NULL;
    while (current != NULL)
    {
        prev = current;
        current = current->next;
        if (current->data == data)
        {
            prev->next = current->next;
            delete current;
            count--;
            return true;
        }
    }
    return false;
}

///@brief Erases the contents of the linked list
void LinkedList::removeAll() {
    Node* newHead;
    while (head->next != NULL)
    {
        newHead = head->next;
        delete head;
        head = newHead;
    }
    head->data = "";
    count = 0;
}

/**@brief Get the number of items in the list
 * @return The number of items in the linked list
 *  as an unsigned int.
 */
unsigned int LinkedList::getCount() {
    return count;
}

///@brief Prints the list to any output stream
///@param output The output stream to use
void LinkedList::print(std::ostream& output) {
    Node* n = head;
    while (n->next != NULL)
    {
        output << n->data << endl;
        n = n->next;
    }
    output << n->data << endl << endl;
}

/**@brief Print the list backwards
 * @param output The output stream to use
 * @param current Parameter used for recursion, implementation detail
 *
 * Node* current is used internally, do not change its default
 * value. Failure to follow this advice will result in unpredictable
 * behavior.
 */
void LinkedList::printReverse(ostream& output, Node* current) {
    if (current == NULL)  //start chain reaction
    {
        printReverse(output, head);
        return;
    }

    if (current->next != NULL)
        printReverse(output, current->next);

    cout << current->data << endl;
}
