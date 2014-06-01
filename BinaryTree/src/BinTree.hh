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
    bool remove(Node* n2d);
    const std::pair<Node*, uint32_t>
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
      //find the node to delete and delete it
    return remove(search(data, root, 0).first);
}

/**@brief performs a simple binary search
   @param data the data to search for
   @return an std:: pair<bool, uint32_t> of whether the data exists and the
           level that the data is on

If the data was not found, the first value is false. Disregard the level.\n
The level index starts at 0
*/
const std::pair<bool, uint32_t> BinTree::search(const int& data) const {
    const std::pair<Node*, uint32_t> result =  search(data, root, 0);
    if (result.first == NULL)
        return std::make_pair(false, 0);
    else
        return std::make_pair(true, result.second);
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

bool BinTree::remove(Node* n2d) {
    Node* temp;

    if (n2d == NULL)
        return false;
    else if (n2d->left == NULL && n2d->right == NULL) //n2d is a leaf
    {
        temp = n2d;
        n2d = NULL;
    }
    else if (n2d->left == NULL) //n2d has a right subtree, no left
    {
        temp = n2d;
        n2d = temp->right;
    }
    else if (n2d->right == NULL) //n2d has a left subtree, no left
    {
        temp = n2d;
        n2d = temp->left;
    }
    else //n2d has both a left and a right subtree
    {
        temp = n2d->left; //move 1 node left
        Node* prev = NULL;

          //move right as far as possible
        while (temp->right != NULL)
        {
            prev = temp;
            temp = temp->right;
        }

        n2d->data = temp->data;

        if (prev == NULL) //temp did not move
            n2d->left = temp->left;
        else
            prev->right = temp->left;
    }

    delete temp;
    nodeCount--;
    return true;
}

const std::pair<Node*, uint32_t>
    BinTree::search(const int& data, Node* n, uint32_t level) const {
    
	if (data == n->data)
		return std::make_pair(n, level);
	else if (data < n->data && n->left != NULL) //data is too big
		search(data, n->left, level + 1);
	else if (data > n->data && n->right != NULL) //data is too small
		search(data, n->right, level + 1);
	else //data does not exist
		return std::make_pair(nullptr, level);
      //don't know why, but it doesn't allow me to cast NULL, it seems to need
      //nullptr
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

#endif // BINTREE_HH
