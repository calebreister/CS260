///@file main.cc
///@author Caleb Reister
#include <iostream>
#include "BinTree.hh"
using namespace std;

void print(const int& x, uint32_t l) {
    cout << x << " " << l << endl;
}

int main() {
    BinTree<int> t {1,2,10,5,4,3};
    t.traverse(IN_ORDER, print);
    cout << endl;
    cout << t.search(10).first << " " << t.search(10).second << endl;
    t.traverse(IN_ORDER, print);
}
