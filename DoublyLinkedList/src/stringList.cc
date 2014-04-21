///@file stringList.cc
///@brief A test file for the LinkedList class

#include <iostream>
#include "DoublyLinkedList.hh"
using namespace std;

enum userAction {
    LIST_ADD, LIST_REMOVE, LIST_ERASE, LIST_COUNT, LIST_PRINT_REV, QUIT
};
userAction showMenu();

int main() {
    DoublyLinkedList<string> list;
    userAction input;
    list.insert("b");
    list.insert("a");
    list.insert("d");
    list.insert("c");
    list.insert("c");

    cout << "Please choose an action..." << endl
         << "a - add to list" << endl
         << "r - remove from list" << endl
         << "c - count the items in the list" << endl
         << "p - print the list in reverse" << endl
         << "x - erase list" << endl
         << "Q - quit" << endl << endl;

    do
    {
        list.print(cout);
        input = showMenu();

        if (input == LIST_ADD)
        {
            string addToList;
            cout << "Please input the string to add..." << endl;
            cin.ignore();
            getline(cin, addToList);
            list.insert(addToList);
        }
        else if (input == LIST_REMOVE)
        {
            string removeFromList;
            cout << "Please input the string remove..." << endl;
            cin.ignore();
            getline(cin, removeFromList);
            list.remove(removeFromList);
        }
        else if (input == LIST_COUNT)
            cout << list.getCount() << endl;
        else if (input == LIST_PRINT_REV)
        {
            list.printReverse(cout);
            cout << endl;
        }
        else if (input == LIST_ERASE)
            list.removeAll();
        else if (input == QUIT)
            return 0;
    } while (true);
}

///@brief Choose an action to perform on a linked list, strictly user interface.
userAction showMenu() {
    char userInput;
        cout << "-> ";
    cin >> userInput;

    switch (userInput)
    {
        case 'a':
            return LIST_ADD;
            break;
        case 'r':
            return LIST_REMOVE;
            break;
        case 'x':
            char eraseNotice;
            cout << "Are you sure you want to erase the entire list? [y/n] ";
            cin >> eraseNotice;
            return eraseNotice == 'y' ? LIST_ERASE : showMenu();
            break;
        case 'c':
            return LIST_COUNT;
            break;
        case 'p':
            return LIST_PRINT_REV;
            break;
        case 'Q':
            return QUIT;
            break;
        default:
            cout << "CHOICE INVALID. PLEASE TRY AGAIN..." << endl;
            return showMenu();
            break;
    }

    return QUIT;
}
