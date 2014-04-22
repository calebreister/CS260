///@file testCode.cc
///@brief A test file for the DoublyLinkedList class

#include <iostream>
#include "DoublyLinkedList.hh"
#include "Dog.hh"
using namespace std;

void runComparisons(DoublyLinkedList<int>& a,
                    DoublyLinkedList<int>& b);
void runComparisons(const Dog& a, const Dog& b);

int main() {
    DoublyLinkedList<int> l1, l2;
    cout << "a = l1; b = l2" << endl;
    runComparisons(l1, l2);

    DoublyLinkedList<Dog> dogs;
    Dog dog1;
    Dog dog2;
    runComparisons(dog1, dog2);

    dog1.name = "Fido";
    dog1.noodle = IDIOT;
    dog1.weightLbs = 10;
    dog2.name = "Barbarian the Barbarian";
    dog2.noodle = MR_PEABODY;
    dog2.weightLbs = 2500;
    dogs.insert(dog1);
    dogs.insert(dog2);
    cout << dogs;
    dogs.remove(dog2);
    dogs.remove(dog1);
    cout << dogs;
    runComparisons(dog1, dog2);
}

void runComparisons(DoublyLinkedList<int>& a,
                    DoublyLinkedList<int>& b) {
    a.insert(2);
    a.insert(1);
    a.insert(2);
    a.insert(5);
    a.insert(30);
    a.insert(3);
    cout << "a\n" << a << endl;

    b = a;
    cout << "Equality tests\n"
         << "a == b? " << (a == b) << endl
         << "a != b? " << (a != b) << endl;

    a.remove(30);
    a.remove(2);
    a.remove(1);
    cout << "!= test" << endl
         << "a != b? " << (a != b) << endl
         << "a != b? " << (a != b) << endl;

    a.removeAll();
    b.removeAll();
    a.insert(2);
    a.insert(1);
    a.insert(3);
    b.insert(4);
    b.insert(5);
    b.insert(6);
    cout << "a\n" << a << endl
         << "b\n" << b << endl;
    cout << "a = {1,2,3}; b = {4,5,6}" << endl
         << "a > b? " << (a > b) << endl
         << "a < b? " << (a < b) << endl
         << "a >= b? " << (a >= b) << endl
         << "a <= b? " << (a <= b) << endl;
    a = b;
    cout << "a = b" << endl
         << "a > b? " << (a > b) << endl
         << "a < b? " << (a < b) << endl
         << "a >= b? " << (a >= b) << endl
         << "a <= b? " << (a <= b) << endl;
    cout << "--------------------------------------------------" << endl;
}

void runComparisons(const Dog& a, const Dog& b) {
    cout << "dog1\n" << a
         << "dog2\n" << b
         << "dog1 == dog2? " << (a == b) << endl
         << "dog1 != dog2? " << (a != b) << endl
         << "dog1 > dog2? " << (a > b) << endl
         << "dog1 < dog2? " << (a < b) << endl
         << "dog1 >= dog2? " << (a >= b) << endl
         << "dog1 <= dog2? " << (a <= b) << endl;
}
