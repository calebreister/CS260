///@file testCode.cc
///@brief A test file for the DoublyLinkedList class

#include <iostream>
#include "DoublyLinkedList.hh"
#include "Dog.hh"
using namespace std;

void runComparisons(const DoublyLinkedList<int>& a,
                    const DoublyLinkedList<int>& b);
void runComparisons(const Dog& a, const Dog& b);

int main() {

}

void runComparisons(const DoublyLinkedList<int>& a,
                    const DoublyLinkedList<int>& b) {
    //int tests
    DoublyLinkedList<int> l1;
    DoublyLinkedList<int> l2;

    l1.insert(2);
    l1.insert(1);
    l1.insert(2);
    l1.insert(5);
    l1.insert(30);
    l1.insert(3);
    cout << "l1\n" << l1 << endl;

    l2 = l1;
    cout << "Equality tests\n"
         << "l1 == l2? " << (l1 == l2) << endl
         << "l1 != l2? " << (l1 != l2) << endl;

    l1.remove(30);
    l1.remove(2);
    l1.remove(1);
    cout << "!= test" << endl
         << "l1 != l2? " << (l1 != l2) << endl
         << "l1 != l2? " << (l1 != l2) << endl;

    l1.removeAll();
    l2.removeAll();
    l1.insert(2);
    l1.insert(1);
    l1.insert(3);
    l2.insert(4);
    l2.insert(5);
    l2.insert(6);
    cout << "l1\n" << l1 << endl
         << "l2\n" << l2 << endl;
    cout << "l1 = {1,2,3}; l2 = {4,5,6}" << endl
         << "l1 > l2? " << (l1 > l2) << endl
         << "l1 < l2? " << (l1 < l2) << endl
         << "l1 >= l2? " << (l1 >= l2) << endl
         << "l1 <= l2? " << (l1 <= l2) << endl;
    l1 = l2;
    cout << "l1 = l2" << endl
         << "l1 > l2? " << (l1 > l2) << endl
         << "l1 < l2? " << (l1 < l2) << endl
         << "l1 >= l2? " << (l1 >= l2) << endl
         << "l1 <= l2? " << (l1 <= l2) << endl;
}

void runComparisons(const Dog& a, const Dog& b) {

}
