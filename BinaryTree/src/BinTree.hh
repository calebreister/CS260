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
    uint32_t nodeCount;
    void delNode(Node* n);
    const std::pair<bool, uint32_t>
        search(const int& data, Node* n, uint32_t level) const;
    static void inOrder(void (*func)(const int&, uint32_t),
                        Node* n, uint32_t level);
    static void preOrder(void (*func)(const int&, uint32_t),
                         Node* n, uint32_t level);
    static void preOrder(Node* n, BinTree& dest);
    static void postOrder(void (*func)(const int&, uint32_t),
                          Node* n, uint32_t level);
public:
    enum Traverse {IN_ORDER, PRE_ORDER, POST_ORDER};
    BinTree();
    BinTree(uint32_t argCount, ...); ///< Starting value constructor
    ~BinTree();
      //MANAGE DATA//////////////////////////////////////////////
    uint32_t count() const; ///< get the number of items in the tree
    void add(const int& data);
    const bool remove(const int& data);
    const std::pair<bool, uint32_t> search(const int& data) const;
    void traverse(Traverse order, void (*func)(const int&, uint32_t)) const;
    void erase();
      //COPY/////////////////////////////////////////////////////
    BinTree(const BinTree& source); ///< copy constructor
    void operator=(const BinTree& right);
    void operator+=(const BinTree& right);
    friend BinTree operator+(const BinTree& left, const BinTree& right);
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

BinTree::BinTree() {
    root = NULL;
    nodeCount = 0;
}

BinTree::BinTree(uint32_t argCount, ...) {
    root = NULL;
    nodeCount = 0;
      ///////////////////////////////////
    va_list args;
    va_start(args, argCount);
    for (uint32_t i = 0; i < argCount; i++)
        this->add(va_arg(args, int));
    va_end (args);
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
        nodeCount--;
    }
}

const std::pair<bool, uint32_t>
    BinTree::search(const int& data, Node* n, uint32_t level) const {
    
	if (data == n->data)
		return std::make_pair(true, level);
	else if (data < n->data && n->left != NULL)
		search(data, n->left, level + 1);
	else if (data > n->data && n->right != NULL)
		search(data, n->right, level + 1);
	else
		return std::make_pair(false, 0);
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
void BinTree::inOrder(void (*func)(const int&, uint32_t),
                      Node* n, uint32_t level) {
    if (n != NULL)
    {
        inOrder(func, n->left, level + 1);
        func(n->data, level);
        inOrder(func, n->right, level + 1);
    }
}

/**@brief traverses the tree visiting parents, left children, and right
   children in that order
   @param (*func)(const int&) The function to run on each node
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
void BinTree::preOrder(void (*func)(const int&, uint32_t),
                       Node* n, uint32_t level) {
    if (n != NULL)
    {
        func(n->data, 0);
        preOrder(func, n->left, level + 1);
        preOrder(func, n->right, level + 1);
    }
}

void BinTree::preOrder(Node* n, BinTree& dest) {
    
    if (n != NULL)
    {
        dest.add(n->data);
        preOrder(n->left, dest);
        preOrder(n->right, dest);
    }
}

/**@brief traverses the tree visiting left children, right
   children, and parents in that order
   @param (*func)(const int&) The function to run on each node
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
void BinTree::postOrder(void (*func)(const int&, uint32_t),
                        Node* n, uint32_t level) {
    if (n != NULL)
    {
        postOrder(func, n->left, level + 1);
        postOrder(func, n->right, level + 1);
        func(n->data, 0);
    }
}

///////////////////////////////////////////////////////////////////////////////
//PUBLIC

///@brief Return the number of nodes in the tree
uint32_t BinTree::count() const {
    return nodeCount;
}

void BinTree::add(const int& data) {
    Node* nn = new Node;
    nn->data = data;

    if (root == NULL)
        root = nn;
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
    nodeCount++;
}

const bool BinTree::remove(const int& data) {
    if (root == NULL)
        return false;

    Node* current = root;
    Node* prev;

      //find the node to delete
    while (current != NULL && current->data != data)
    {
        prev = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }
    
    if (current == NULL)  //the value does not exist
        return false;
    else if (current->left == NULL && current->right == NULL)
        delete current;  //current is a leaf
    else if (current->left != NULL && current->right != NULL)
    {   //current has a left and right subtree
        Node* temp;
        temp = current->left;  //move 1 to the left
        
        //move right until NULL is found
        while (temp->right->right != NULL)
            temp = temp->right;
          //NOTE: temp points to the parent of the replacement data

          //assign that value to current and delete that node
        current->data = temp->right->data;
        delete temp->right;
        temp->right = NULL;
        
        nodeCount--;
        return true;
    }
    else if (current->right == NULL)  //current has left subtree
    {
        if (prev->left == current)
            prev->left = current->left;
        else
            prev->right = current->left;
        delete current;
    }
    else  //current has right subtree
    {
        if (prev->left == current)
            prev->left = current->right;
        else
            prev->right = current->left;
        delete current;
    }

    if (prev->left == current)
        prev->left = NULL;
    else
        prev->right = NULL;

    nodeCount--;
    return true;
}

///@brief performs a simple binary search
///@param data the data to search for
const std::pair<bool, uint32_t> BinTree::search(const int& data) const {
    return search(data, root, 0);
}

void BinTree::traverse(Traverse order, void (*func)(const int&, uint32_t)) const {
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

void BinTree::erase() {
    delNode(root);
    root = NULL;
}

///////////////////////////////////////////////////////////////////////////////
//COPY

BinTree::BinTree(const BinTree& source) {
    root = NULL;
    nodeCount = 0;
    source.preOrder(source.root, *this);
}

void BinTree::operator=(const BinTree& right) {
    this->erase();  //erase the tree if it exists
    right.preOrder(right.root, *this);
}

void BinTree::operator+=(const BinTree& right) {
    right.preOrder(right.root, *this);
}

BinTree operator+(const BinTree& left, const BinTree& right) {
    BinTree result(left);
    result += right;
    return result;
}

#endif // BINTREE_HH
