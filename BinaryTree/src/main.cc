///@file 
///@author Caleb Reister
#include <iostream>
#include "BinTree.hh"
using namespace std;

void print(int x) {
    cout << x << " ";
}

int main() {
    BinTree t(10,5,1,3,4,2,6,8,9,23,10);
    t.remove(5);
    cout << t.count() << endl;
    t.traverse(BinTree::IN_ORDER, print);
    return 0;
}

