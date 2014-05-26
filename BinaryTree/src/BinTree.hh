///@file BinTree.hh
///@author Caleb Reister <calebreister@gmail.com>

#ifndef BINTREE_HH
#define BINTREE_HH

#include <ios>
#include <cstdint>
#include <cstddef>
#include <cstdarg>

struct Node {
    int data;
    Node* left = NULL;
    Node* right = NULL;
};

class BinTree {
private:
    Node* root;
    uint32_t valCount;
    void delNode(Node* n);
public:
    BinTree();
    BinTree(uint32_t argCount, ...); ///< Starting value constructor
    ~BinTree();
    //MANAGE DATA
    uint32_t count(); ///< get the number of items in the tree
    void inOrder(void (*func)(int data), uint32_t level = 0);
    void postOrder(void (*func)(int data), uint32_t level = 0);
    void preOrder(void (*func)(int data), uint32_t level = 0);
    void insert(int data);
    const bool remove(int data);
    //COPY
    BinTree(const BinTree& source); ///< copy constructor
    void operator=(const BinTree& right);
    friend BinTree operator+=(BinTree& left, const BinTree& right);
    BinTree operator+(const BinTree& right);
    //COMPARE
    friend bool operator==(const BinTree& a, const BinTree& b);
    friend bool operator!=(const BinTree& a, const BinTree& b);
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

BinTree::BinTree() {
    root = NULL;
    countVal = 0;
}

BinTree::BinTree(uint32_t argCount, ...) {
    root = NULL;
    countVal = 0;
    ///////////////////////////////////
    va_list args;
    va_start(args, argCount);
    for (uint32_t i = 0; i < argCount; i++)
        this->insert(va_arg(args, int));
    va_end (args);
}

//COPY CONSTRUCTOR
BinTree::BinTree(const BinTree& source) {
}

BinTree::~BinTree() {
     delNode(root);
}

///////////////////////////////////////////////////////////////////////////////
//PRIVATE

void BinTree::delNode(Node* n) {
    if (n != NULL)
    {
        delNode(n->left);
        delNode(n->right);
        delete n;
    }
}

///////////////////////////////////////////////////////////////////////////////
//PUBLIC

uint32_t BinTree::count {
    return valCount;
}

void BinTree::inOrder(void (*func)(int data), uint32_t level) {

}

void BinTree::postOrder(void (*func)(int data), uint32_t level) {

}

void BinTree::preOrder(void (*func)(int data), uint32_t level) {

}

void BinTree::insert(int data) {

}

const bool BinTree::remove(int data) {

}

///////////////////////////////////////////////////////////////////////////////
//COPY

void BinTree::operator=(const BinTree& right) {
}

BinTree operator+=(BinTree& left, const BinTree& right) {
}

BinTree BinTree::operator+(const BinTree& right) {

}

///////////////////////////////////////////////////////////////////////////////
//COMPARE

bool operator==(const BinTree& a, const BinTree& b) {

}

bool operator!=(const BinTree& a, const BinTree&) {

}

#endif // BINTREE_HH
