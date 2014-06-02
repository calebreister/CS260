///@file BinTree.hh
///@author Caleb Reister <calebreister@gmail.com>

#ifndef BINTREE_HH
#define BINTREE_HH

#include <ios>
#include <utility>
#include <initializer_list>
#include <cstdint>
#include <cstddef>
#include <cstdarg>

template<class dataType>
class BinTree;

template<class DataType>
BinTree<DataType> operator+(const BinTree<DataType>& left,
                            const BinTree<DataType>& right);

template<class DataType>
struct Node {
    DataType data;
    Node<DataType>* left = NULL;
    Node<DataType>* right = NULL;
};

enum TreeTraverse {IN_ORDER, PRE_ORDER, POST_ORDER};

///@brief A binary tree template
template<class DataType>
class BinTree {
private:
    Node<DataType>* root; ///< the starting node
    uint32_t nodeCount; ///< the number of nodes in the tree
    void delNode(Node<DataType>* n);
    bool remove(Node<DataType>** n2d);
    
    const std::pair<Node<DataType>**, uint32_t>
    search(const DataType& data, Node<DataType>*& n, uint32_t level) const;
    
    static void inOrder(void (*func)(const DataType&, uint32_t),
                        Node<DataType>* n, uint32_t level);
    static void preOrder(void (*func)(const DataType&, uint32_t),
                         Node<DataType>* n, uint32_t level);
    static void preOrder(Node<DataType>* n, BinTree<DataType>& dest);
    static void postOrder(void (*func)(const DataType&, uint32_t),
                          Node<DataType>* n, uint32_t level);
public:
    BinTree(); ///< default constructor
    BinTree(std::initializer_list<DataType> data);
    ~BinTree();
    //MANAGE DATA//////////////////////////////////////////////
    uint32_t count() const; ///< get the number of items in the tree
    void insert(const DataType& data);
    void insert(std::initializer_list<DataType> data);
    const bool remove(const DataType& data);
    const std::pair<bool, uint32_t> search(const DataType& data); //search
    void traverse(TreeTraverse order, void (*func)(const DataType&, uint32_t)) const;
    void erase(); ///< erases the contents of the tree
    //COPY/////////////////////////////////////////////////////
    BinTree(const BinTree<DataType>& source); ///< copy constructor
    void operator=(const BinTree<DataType>& right); ///< overwrites the contents
                                                    ///  of the tree
    void operator+=(const BinTree<DataType>& right);
    friend BinTree<DataType> operator+ <>(const BinTree<DataType>& left,
                                          const BinTree<DataType>& right);
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
template<class DataType>
BinTree<DataType>::BinTree() {
    root = NULL;
    nodeCount = 0;
}

/**@brief starting value constructor
   @param data a list of values of DataType to insert into the tree,
          the first value becomes root
*/
template<class DataType>
BinTree<DataType>::BinTree(std::initializer_list<DataType> data) {
    root = NULL;
    nodeCount = 0;
    insert(data);
}

template<class DataType>
BinTree<DataType>::~BinTree() {
    delNode(root);
}

///////////////////////////////////////////////////////////////////////////////
//PUBLIC

///@brief Return the number of nodes in the tree
template<class DataType>
uint32_t BinTree<DataType>::count() const {
    return nodeCount;
}

/**@brief adds data to the tree
   @param data the data to add
*/
template<class DataType>
void BinTree<DataType>::insert(const DataType& data) {
    Node<DataType>* nn = new Node<DataType>;
    nn->data = data;

    if (root == NULL)
        root = nn;
    else
    {
        Node<DataType>* current = root;
        Node<DataType>* parent;

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

/**@brief insert multiple pieces of data, copies by value
   @param data the data to add (in a brace-enclosed initializer list)

NOTE: this is not reccomended for anything that uses large amounts of memory
*/
template<class DataType>
void BinTree<DataType>::insert(std::initializer_list<DataType> data) {
    for (DataType i : data) //for DataType i in list data
        insert(i);
}

/**@brief remove some data from the list
   @param data the data to remove
   @return true if the data was found and removed, false if the data
           does not exist
*/
template<class DataType>
const bool BinTree<DataType>::remove(const DataType& data) {
    Node<DataType>** n2d = search(data, root, 0).first;
    if (*n2d == NULL)
        return false;
    return remove(n2d);
}

/**@brief performs a binary search of the tree
   @param data the data to search for
   @return an std:: pair<bool, uint32_t> of whether the data exists and the
           level that the data is on

* If the data was not found, the first value is false. Disregard the level
* The level index starts at 0
*/
template<class DataType>
const std::pair<bool, uint32_t> BinTree<DataType>::search(const DataType& data) {
    const auto result = search(data, root, 0); //infers type during compile
    if (*(result.first) == NULL)
        return std::make_pair(false, 0);
    else
        return std::make_pair(true, result.second);
}

/**@brief runs a user-supplied function on every node in the tree in the
          specified order
   @param the order the order in which to hit each node, options are
          IN_ORDER, PRE_ORDER, and POST_ORDER; see below for what each does
   @param void (*func)(const DataType&, uint32_t the function to run on each
          node, the passed function must have the same parameter and return types

* IN_ORDER: see inOrder()
* PRE_ORDER: see preOrder(void (*func)(const DataType&, uint32_t),
                          Node<DataType>* n, uint32_t level)
* POST_ORDER: see postOrder()
*/
template<class DataType>
void BinTree<DataType>::traverse(TreeTraverse order,
                                 void (*func)(const DataType&, uint32_t)) const {
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

template<class DataType>
void BinTree<DataType>::erase() {
    delNode(root);
    root = NULL;
}

///////////////////////////////////////////////////////////////////////////////
//COPY
template<class DataType>
BinTree<DataType>::BinTree(const BinTree<DataType>& source) {
    root = NULL;
    nodeCount = 0;
    source.preOrder(source.root, *this);
}

template<class DataType>
void BinTree<DataType>::operator=(const BinTree<DataType>& right) {
    this->erase();  //erase the tree if it exists
    right.preOrder(right.root, *this);
}

/**@brief copies the contents from one tree to another without overwriting data
   @param right the tree to copy from (right operand)

When called, this function copies the contents one by one in preorder. It uses
preOrder(Node<DataType>* n, BinTree<DataType>& dest).
*/
template<class DataType>
void BinTree<DataType>::operator+=(const BinTree<DataType>& right) {
    right.preOrder(right.root, *this);
}

/**@brief combines two trees
   @param left the left operand
   @param right the right operand
   @return a BinTree<DataType> that contains the contents of both trees
*/
template<class DataType>
BinTree<DataType> operator+(const BinTree<DataType>& left,
                            const BinTree<DataType>& right)
{
    BinTree<DataType> result(left);
    result += right;
    return result;
}

///////////////////////////////////////////////////////////////////////////////
//PRIVATE
/**@brief deletes a node and all of its children
   @param n the node to delete
*/
template<class DataType>
void BinTree<DataType>::delNode(Node<DataType>* n) {
    if (n != NULL)
    {
        delNode(n->left);
        delNode(n->right);
        delete n;
        nodeCount--;
    }
}

/**@brief removes the specified node from the tree
   @param n2d the node to remove
   @return true if the node was removed, false if it was not found

Takes a double pointer as input. This is necessary so that the actual
node within the tree (and not just a pointer to it) can be set to NULL.
It is possible to do this using references, but because there is going to
potentially be multiple levels of recursion, I have decided that it would be
difficult to debug. Instead of dealing the pointers passed by reference, a
double pointer (as in **, not double*). The memory usage should be the same,
however, what does change is how I access the values. When using double
pointers, you have to access the values of a node like this...

~~~~~{.cc}
Node<int>* np;
np = new Node<int>;
np->data = 10;
///////////////////
Node<int>** npp = &np;
*npp = NULL; //sets np to be NULL (creates a memory leak here)
np = new Node<int>;
(*np)->data = 10; //accesses the members of np
~~~~~
*/
template<class DataType>
bool BinTree<DataType>::remove(Node<DataType>** n2d) {
    Node<DataType>* temp;

    if (n2d == NULL)
        return false;
    else if ((*n2d)->left == NULL && (*n2d)->right == NULL) //n2d is a leaf
    {
        temp = *n2d;
        *n2d = NULL;
    }
    else if ((*n2d)->left == NULL) //n2d has a right subtree, no left
    {
        temp = *n2d;
        *n2d = temp->right;
    }
    else if ((*n2d)->right == NULL) //n2d has a left subtree, no left
    {
        temp = *n2d;
        *n2d = temp->left;
    }
    else //n2d has both a left and a right subtree
    {
        temp = (*n2d)->left; //move 1 node left
        Node<DataType>* prev = NULL;

        //move right as far as possible
        while (temp->right != NULL)
        {
            prev = temp;
            temp = temp->right;
        }

        (*n2d)->data = temp->data;

        if (prev == NULL) //temp did not move
            (*n2d)->left = temp->left;
        else
            prev->right = temp->left;
    }

    delete temp;
    nodeCount--;
    return true;
}

/**@brief searches the tree recursively
   @param data the data to look for
   @param n the starting node
   @param level the number of branches from root (starts at 0)
   @return a pointer, passed by reference to the Node with the data,
           the level of that node

Disregard the level if the returned double pointer is NULL
*/
template<class DataType>
const std::pair<Node<DataType>**, uint32_t>
BinTree<DataType>::search(const DataType& data, Node<DataType>*& n,
                          uint32_t level) const
{    
	if (data == n->data)
		return std::make_pair(&n, level);
	else if (data < n->data && n->left != NULL) //data is too big
		search(data, n->left, level + 1);
	else if (data > n->data && n->right != NULL) //data is too small
		search(data, n->right, level + 1);
	else //data does not exist
		return std::make_pair(nullptr, level);
    //don't know why, but it doesn't allow me to put NULL here,
    //it seems to need nullptr
}

/**@brief traverses the tree starting at the left and working right
@param (*func)(const DataType& data) The function to run on each node
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
template<class DataType>
void BinTree<DataType>::inOrder(void (*func)(const DataType&, uint32_t),
                                 Node<DataType>* n, uint32_t level) {
    if (n != NULL)
    {
        inOrder(func, n->left, level + 1);
        func(n->data, level);
        inOrder(func, n->right, level + 1);
    }
}

/**@brief traverses the tree visiting parents, left children, and right
children in that order
@param (*func)(const DataType&) The function to run on each node
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
template<class DataType>
void BinTree<DataType>::preOrder(void (*func)(const DataType&, uint32_t),
                                  Node<DataType>* n, uint32_t level) {
    if (n != NULL)
    {
        func(n->data, level);
        preOrder(func, n->left, level + 1);
        preOrder(func, n->right, level + 1);
    }
}

/**@brief traverses a tree in preorder and inserts it in another tree
   @param n, the node to start at (used in recursion)
   @param dest the tree to insert the copy of the data into
*/
template<class DataType>
void BinTree<DataType>::preOrder(Node<DataType>* n, BinTree<DataType>& dest) {
    
    if (n != NULL)
    {
        dest.insert(n->data);
        preOrder(n->left, dest);
        preOrder(n->right, dest);
    }
}

/**@brief traverses the tree visiting left children, right
children, and parents in that order
@param (*func)(const DataType&) The function to run on each node
@param the level of each node, root = 0

1. Traverse left subtree
2. Traverse right subtree
3. Visit node

xA tree set up like this (* has a value, x is NULL)...

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
template<class DataType>
void BinTree<DataType>::postOrder(void (*func)(const DataType&, uint32_t),
                                  Node<DataType>* n, uint32_t level) {
    if (n != NULL)
    {
        postOrder(func, n->left, level + 1);
        postOrder(func, n->right, level + 1);
        func(n->data, level);
    }
}

#endif // BINTREE_HH
