///@file BinTree.hh
///@author Caleb Reister <calebreister@gmail.com>

#ifndef BINTREE_HH
#define BINTREE_HH

#include <ios>
#include <utility>
#include <cstdint>
#include <cstddef>
#include <cstdarg>

struct Node {
    int data;
    Node* left = NULL;
    Node* right = NULL;
};

/**@brief A binary tree template
 */
class BinTree {
private:
    Node* root;
    void delNode(Node* n);
    const bool recursiveSearch(const int& data, Node* n);
    static void inOrder(void (*func)(int), Node* n, uint32_t level);
    static void preOrder(void (*func)(int), Node* n, uint32_t level);
    static void postOrder(void (*func)(int), Node* n, uint32_t level);
public:
    enum Traverse {IN_ORDER, PRE_ORDER, POST_ORDER};
    BinTree();
    BinTree(uint32_t argCount, ...); ///< Starting value constructor
    ~BinTree();
      //MANAGE DATA//////////////////////////////////////////////
    uint32_t count(); ///< get the number of items in the tree
    void insert(const int& data);
    const bool remove(const int& data);
    const bool search(const int& data);
    void traverse(Traverse order, void (*func)(int));
      //COPY/////////////////////////////////////////////////////
    BinTree(const BinTree& source); ///< copy constructor
    void operator=(const BinTree& right);
    void operator+=(const BinTree& right);
    BinTree operator+(const BinTree& right);
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

BinTree::BinTree() {
    root = NULL;
}

BinTree::BinTree(uint32_t argCount, ...) {
    root = NULL;
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

const bool BinTree::recursiveSearch(const int& data, Node* n) {
	if (data == n->data)
		return true;
	else if (data < n->data && n->left != NULL)
		recursiveSearch(data, n->left);
	else if (data > n->data && n->right != NULL)
		recursiveSearch(data, n->right);
	else
		return false;
}

/**@brief traverses the tree starting at the left and working right
   @param (*func)(const int& data) The function to run on each node
   @param the level of each node, root = 0

   1. Traverse left subtree
   2. Visit node
   3. Traverse right subtree

   A tree set up like this (* has a value, x is NULL)...

   0|     *
   ||   /   \
   1|  *     *
   || / \   / \
   2|x   *  x  *
   ||   / \   / \
   3|  *   *  x  *

   ...will be traversed like this (numbers are the order in which the
   function is run).

   0|     5
   ||   /   \
   1|  1     6
   || / \   / \
   2|x   3  x  7
   ||   / \   / \
   3|  2   4  x  8
*/
void BinTree::inOrder(void (*func)(int), Node* n, uint32_t level) {
    if (n != NULL)
    {
        inOrder(func, n->left, level + 1);
        func(n->data);
        inOrder(func, n->right, level + 1);
    }
}

/**@brief traverses the tree visiting parents, left children, and right
   children in that order
   @param (*func)(int) The function to run on each node
   @param the level of each node, root = 0

   1. Visit node
   2. Traverse left subtree
   3. Traverse right subtree

   A tree set up like this (* has a value, x is NULL)...

   0|     *
   ||   /   \
   1|  *     *
   || / \   / \
   2|x   *  x  *
   ||   / \   / \
   3|  *   *  x  *

   ...will be traversed like this (numbers are the order in which the
   function is run).

   0|     1
   ||   /   \
   1|  2     6
   || / \   / \
   2|x   3  x  7
   ||   / \   / \
   3|  4   5  x  8
*/
void BinTree::preOrder(void (*func)(int), Node* n, uint32_t level) {
    if (n != NULL)
    {
        func(n->data);
        preOrder(func, n->left, level + 1);
        preOrder(func, n->right, level + 1);
    }
}

/**@brief traverses the tree visiting left children, right
   children, and parents in that order
   @param (*func)(int) The function to run on each node
   @param the level of each node, root = 0

   1. Traverse left subtree
   2. Traverse right subtree
   3. Visit node

   A tree set up like this (* has a value, x is NULL)...

   0|     *
   ||   /   \
   1|  *   *
   || / \   / \
   2|x   *  x  *
   ||   / \   / \
   3|  *   *  x  *

   ...will be traversed like this (numbers are the order in which the
   function is run).

   0|     5
   ||   /   \
   1|   4    8
   || / \   / \
   2|x   3  x  7
   ||   / \   / \
   3|  1   2  x  6
*/
void BinTree::postOrder(void (*func)(int), Node* n, uint32_t level) {
    if (n != NULL)
    {
        postOrder(func, n->left, level + 1);
        postOrder(func, n->right, level + 1);
        func(n->data);
    }
}

///////////////////////////////////////////////////////////////////////////////
//PUBLIC

///@brief Return the number of nodes in the tree
uint32_t BinTree::count() {
}

void BinTree::insert(const int& data) {
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

const bool BinTree::remove(const int& data) {
    if (root == NULL)
        return false;

    Node* current = root;
    Node* prev;
    Node* temp;

    while (current != NULL && current->data != data)
    {
        prev = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }
    
    if (current == NULL)
        return false;
    else if (current->left != NULL && current->right != NULL)
    {   //both left and right subtree
        temp = current->left;

        while (temp->right != NULL)  //find a node to use as the replacement
            temp = temp->right;

        int tempData = temp->data;
        remove(temp->data);
        current->data = tempData;
    }
    else if (current->right == NULL)  //no right subtree
    {
        temp = current;
        prev->right = current->left;
        delete temp;
    }
    else if (current->left == NULL)  //no left subtree
    {
        temp = current;
        prev->left = current->right;
        delete temp;
    }
    return true;
}

///@brief performs a simple binary search
///@param data the data to search for
const bool BinTree::search(const int& data) {
    return recursiveSearch(data, root);
}

void BinTree::traverse(Traverse order, void (*func)(int)) {
    switch (order) {
    case IN_ORDER:
        inOrder(func, root, 0);
        break;
    case PRE_ORDER:
        preOrder(func, root, 0);
        break;
    case POST_ORDER:
        postOrder(func, root, 0);
        break;
    }
}

///////////////////////////////////////////////////////////////////////////////
//COPY

void BinTree::operator=(const BinTree& right) {
}

void BinTree::operator+=(const BinTree& right) {
}

BinTree BinTree::operator+(const BinTree& right) {

}

#endif // BINTREE_HH
