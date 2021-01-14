#include <iostream>
using namespace std;

template <class T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T> *leftChild, // left subtree
        *rightChild;              // right subtree

    binaryTreeNode() { leftChild = rightChild = NULL; }
    binaryTreeNode(const T &theElement) : element(theElement)
    {
        leftChild = rightChild = NULL;
    }
    binaryTreeNode(const T &theElement, binaryTreeNode *theLeftChild, binaryTreeNode *theRightChild)
        : element(theElement)
    {
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }
};

template <class E>
class linkedBinaryTree
{
public:
    linkedBinaryTree()
    {
        root = NULL;
        treeSize = 0;
    }

    binaryTreeNode<E> *root; // pointer to root
    int treeSize;            // number of nodes in tree
};

template <class E>
void visit(binaryTreeNode<E> *x)
{
    cout << x->element << " ";
}

template <class E>
void inOrder(binaryTreeNode<E> *t)
{
    if (t != NULL)
    {
        inOrder(t->leftChild);
        visit(t);
        inOrder(t->rightChild);
    }
}

template <class K, class E>
class binarySearchTree : public linkedBinaryTree<pair<const K, E>>

{
public:
    void insert(const pair<const K, E> &thePair)
    {
        binaryTreeNode<pair<const K, E>> *p = this->root,
                                         *pp = NULL;
        while (p != NULL)
        { // examine p->element
            pp = p;
            // move p to a child
            if (thePair.first < p->element.first)
                p = p->leftChild;
            else if (thePair.first > p->element.first)
                p = p->rightChild;
            else
            { // replace old value
                p->element.second = thePair.second;
                return;
            }
        }
        // get a node for thePair and attach to pp
        binaryTreeNode<pair<const K, E>> *newNode = new binaryTreeNode<pair<const K, E>>(thePair);
        if (this->root != NULL) // the tree is not empty
            if (thePair.first < pp->element.first)
                pp->leftChild = newNode;
            else
                pp->rightChild = newNode;
        else
            this->root = newNode; // insertion into empty tree
        this->treeSize++;
    }
};
template <class K, class E>
ostream &operator<<(ostream &out, const pair<K, E> &x)
{
    out << x.first;
    return out;
}

int main()
{
    int n;
    cin >> n;
    pair<int, int> a[100];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].first;
        a[i].second = a[i].first;
    }
    binarySearchTree<int, int> Tree;
    for (int i = 0; i < n; i++)
    {
        Tree.insert(a[i]);
    }
    binaryTreeNode<pair<int, int>> *root;
    inOrder(Tree.root);
}
