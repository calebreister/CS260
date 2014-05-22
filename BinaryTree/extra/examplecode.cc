#include <iostream>
#include <iomanip>
#include <cmath>
#include <stack>
#include <array>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

struct Node {
    int data;
    Node* left = NULL;
    Node* right = NULL;
};

//Depth of a tree: starts at 0

class BinTree {
private:
    Node* root = NULL;
    void printNodeInOrder(Node* n);
    void delNode(Node* n);
public:
    ~BinTree();
    void insert(int data);
    bool remove(int data);
    void printInOrder();
};

/////////////////////////////////////////////////////////////
int main() {
    BinTree test;
    test.insert(10);
    test.insert(5);
    test.insert(2);
    test.insert(3);
    test.insert(20);
    test.insert(7);
    test.insert(18);
    test.insert(16);
    test.insert(25);
}

//////////////////////////////////////////////////////////
BinTree::~BinTree() {
    delNode(root);
}

void BinTree::insert(int data) {
    Node* nn = new Node;
    nn->data = data;

    if (root == NULL)
    {
        root = nn;
        return;
    }
    else
    {
        Node* current = root;
        Node* parent;

        //find the parent of nn
        while (current != NULL)
        {
            parent = current;
            if (nn->data < current->data)
                current = current->left;
            else if (nn->data > current->data)
                current = current->right;
            else
            {
                delete nn;
                return;
            }
        }

        //adjust parent pointers
        if (nn->data < parent->data)
            parent->left = nn;
        else
            parent->right = nn;
    }
}

bool BinTree::remove(int data) {
    //multiple cases when removing
    /*POSSIBLE CASES:
      1: leaf
      2: only data on left
      3: only data on right
      4: data on both left and right
      5: deleting the root
     */

    //LOOK AT BOOKS IMPLEMENTATION
    if (root == NULL)
        return false;
    else if (root->left == NULL && root->right == NULL)
    {
        delete root;
        root = NULL;
        return true;
    }

    Node* parent;
    Node* n2d = root;
    //find the node with data
    while (n2d != NULL && n2d->data != data)
    {
        parent = n2d;
        if (n2d->data > data)
            n2d = n2d->left;
        else
            n2d = n2d->right;
    }

    if (n2d == NULL)
        return false;

    if (n2d->left == NULL && n2d->right == NULL) //if it is a leaf
    {
        if (parent->left->data == n2d->data)
            parent->left = NULL;
        else
            parent->right = NULL;
    }
    else if (n2d->left == NULL)
    {
        if (parent->left->data == n2d->data)
            parent->left = n2d->right;
        else
            parent->right = n2d->right;
    }
    else if (n2d->right == NULL)
    {
        if (parent->left->data == n2d->data)
            parent->left = n2d->left;
        else
            parent->right = n2d->left;
    }
    else if (n2d->left != NULL && n2d->right != NULL)
    {
        //2 options to find a replacement:
        //right once, left as far as possible
        //left once, right as far as possible

        Node* temp = n2d->right;
        while (temp->left != NULL)
            temp = temp->left;
        n2d->data = temp->data;
        if (n2d == parent)
            parent->right = temp->right;
        else
            parent->left = temp->right;
        delete temp;
        return true;
    }

    delete n2d;
    return true;
}

void BinTree::printNodeInOrder(Node* n) {
    if (n != NULL)
    {
        printNodeInOrder(n->left);
        cout << n->data << '\n';
        printNodeInOrder(n->right);
    }
}

void BinTree::printInOrder() {
    printNodeInOrder(root);
}

void BinTree::delNode(Node* n) {
    if (n != NULL)
    {
        delNode(n->left);
        delNode(n->right);
        delete n;
    }
}
