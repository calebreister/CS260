///@file main.cc
///@author Caleb Reister
#include <iostream>
#include "BinTree.hh"
using namespace std;

void print(const int& x, uint32_t l) {
    cout << x << " " << l << endl;
}

int main() {
    BinTree t(3,2,3,1);
    t.remove(2);
}

