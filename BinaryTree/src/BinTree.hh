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
    Node<DataType>* root;
    uint32_t nodeCount;
    void delNode(Node<DataType>* n);
    bool remove(Node<DataType>** n2d);
    
    const std::pair<Node<DataType>**, uint32_t>
    static search(const DataType& data, Node<DataType>** n, uint32_t level);
    
    static void inOrder(void (*func)(const DataType&, uint32_t),
                        Node<DataType>* n, uint32_t level);
    static void preOrder(void (*func)(const DataType&, uint32_t),
                         Node<DataType>* n, uint32_t level);
    static void preOrder(Node<DataType>* n, BinTree<DataType>& dest);
    static void postOrder(void (*func)(const DataType&, uint32_t),
                          Node<DataType>* n, uint32_t level);
public:
    BinTree();
    BinTree(std::initializer_list<DataType> data); ///< Starting value constructor
    ~BinTree();
    //MANAGE DATA//////////////////////////////////////////////
    uint32_t count() const; ///< get the number of items in the tree
    void insert(const DataType& data);
    void insert(std::initializer_list<DataType> data);
    const bool remove(const DataType& data);
    const std::pair<bool, uint32_t> search(const DataType& data);
    void traverse(TreeTraverse order, void (*func)(const DataType&, uint32_t)) const;
    void erase();
    //COPY/////////////////////////////////////////////////////
    BinTree(const BinTree<DataType>& source); ///< copy constructor
    void operator=(const BinTree<DataType>& right);
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

template<class DataType>
void BinTree<DataType>::insert(std::initializer_list<DataType> data) {
    for (DataType i : data)
        insert(i);
}


template<class DataType>
const bool BinTree<DataType>::remove(const DataType& data) {
    Node<DataType>** n2d = search(data, &root, 0).first;
    return remove(n2d);
}

/**@brief performs a simple binary search
@param data the data to search for
@return an std:: pair<bool, uint32_t> of whether the data exists and the
level that the data is on

If the data was not found, the first value is false. Disregard the level.\n
The level index starts at 0
*/
template<class DataType>
const std::pair<bool, uint32_t> BinTree<DataType>::search(const DataType& data) {
    const auto result = search(data, &root, 0); //infers type during compile
    if (*(result.first) == NULL)
        return std::make_pair(false, 0);
    else
        return std::make_pair(true, result.second);
}

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

template<class DataType>
void BinTree<DataType>::operator+=(const BinTree<DataType>& right) {
    right.preOrder(right.root, *this);
}

template<class DataType>
BinTree<DataType> operator+(const BinTree<DataType>& left, const BinTree<DataType>& right) {
    BinTree<DataType> result(left);
    result += right;
    return result;
}

///////////////////////////////////////////////////////////////////////////////
//PRIVATE
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

template<class DataType>
bool BinTree<DataType>::remove(Node<DataType>** n2d) {
    Node<DataType>* temp;

    if (*n2d == NULL)
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

template<class DataType>
const std::pair<Node<DataType>**, uint32_t>
BinTree<DataType>::search(const DataType& data, Node<DataType>** n, uint32_t level) {
    
	if (data == (*n)->data)
		return std::make_pair(n, level);
	else if (data < (*n)->data && (*n)->left != NULL) //data is too big
		search(data, &(*n)->left, level + 1);
	else if (data > (*n)->data && (*n)->right != NULL) //data is too small
		search(data, &(*n)->right, level + 1);
	else //data does not exist
		return std::make_pair(nullptr, level);
    //don't know why, but it doesn't allow me to cast NULL, it seems to need
    //nullptr
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
        func(n->data, 0);
        preOrder(func, n->left, level + 1);
        preOrder(func, n->right, level + 1);
    }
}

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
        func(n->data, 0);
    }
}

#endif // BINTREE_HH
