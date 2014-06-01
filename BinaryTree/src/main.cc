///@file main.cc
///@author Caleb Reister
#include <iostream>
#include "BinTree.hh"
using namespace std;

void print(const int& x, uint32_t l) {
    cout << x << " " << l << endl;
}

int main() {
    BinTree t(5,2,-2,3,1,0);
    t.traverse(BinTree::IN_ORDER, print);
    cout << endl;
    t.remove(2);
    t.traverse(BinTree::IN_ORDER, print);
}
