

#include <iostream>
#include <queue>
using namespace std;

template <class T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T> *leftChild, // left subtree
        *rightChild;              // right subtree
    T leftSize;
    binaryTreeNode() { leftChild = rightChild = NULL; }
    binaryTreeNode(const T &theElement) : element(theElement)
    {
        leftChild = rightChild = NULL;
    }
    binaryTreeNode(const T &theElement,
                   binaryTreeNode *theLeftChild,
                   binaryTreeNode *theRightChild)
        : element(theElement)
    {
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }
};

template <class K, class E>
class binarySearchTree
{
public:
    binarySearchTree()
    {
        root = NULL;
        treeSize = 0;
    }
    bool empty() const { return treeSize == 0; }
    int size() const { return treeSize; }
    pair<const K, E> *find(const K &theKey) const;
    void insert(const pair<const K, E> &thePair);
    void erase(const K &theKey);
    void search(int &rank, binaryTreeNode<pair<const K, E>> *t, int &res);
    void inOrder(binaryTreeNode<pair<const K, E>> *t);

    //private:
    binaryTreeNode<pair<const K, E>> *root;
    int treeSize;
};

template <class K, class E>
pair<const K, E> *binarySearchTree<K, E>::find(const K &theKey) const
{
    binaryTreeNode<pair<const K, E>> *p = root;
    K result = 0;
    while (p != NULL)
    {

        if (theKey < p->element.first)
        {
            result = result ^ p->element.second;
            p = p->leftChild;
        }
        else if (theKey > p->element.first)
        {
            result ^= p->element.second;
            p = p->rightChild;
        }
        else
        {
            cout << (result ^ theKey) << endl;
            return &p->element;
        }
    }
    // no matching pair
    cout << 0 << endl;
    return NULL;
}

template <class K, class E>
void binarySearchTree<K, E>::insert(const pair<const K, E> &thePair)
{
    binaryTreeNode<pair<const K, E>> *p = root,
                                     *pp = NULL;
    K result = 0;
    while (p != NULL)
    {
        pp = p;
        if (thePair.first < p->element.first)
        {
            result ^= p->element.second;
            p = p->leftChild;
        }
        else if (thePair.first > p->element.first)
        {
            result ^= p->element.second;
            p = p->rightChild;
        }
        else
        {
            p->element.second = thePair.second;
            cout << 0 << endl;
            return;
        }
    }

    binaryTreeNode<pair<const K, E>> *newNode = new binaryTreeNode<pair<const K, E>>(thePair);
    if (root != NULL)
        if (thePair.first < pp->element.first)
            pp->leftChild = newNode;
        else
            pp->rightChild = newNode;
    else
        root = newNode;
    treeSize++;
    cout << result << endl;
}

template <class K, class E>
void binarySearchTree<K, E>::erase(const K &theKey)
{
    K result = 0;
    binaryTreeNode<pair<const K, E>> *p = root,
                                     *pp = NULL;
    while (p != NULL && p->element.first != theKey)
    {
        pp = p;
        if (theKey < p->element.first)
        {
            result ^= p->element.second;
            p = p->leftChild;
        }
        else
        {
            result ^= p->element.second;
            p = p->rightChild;
        }
    }
    if (p == NULL)
    {
        cout << 0 << endl;
        return;
    }

    cout << (result ^ p->element.second) << endl;

    if (p->leftChild != NULL && p->rightChild != NULL)
    {

        binaryTreeNode<pair<const K, E>> *s = p->rightChild,
                                         *ps = p;
        while (s->leftChild != NULL)
        {
            ps = s;
            s = s->leftChild;
        }

        binaryTreeNode<pair<const K, E>> *q =
            new binaryTreeNode<pair<const K, E>>(s->element, p->leftChild, p->rightChild);
        if (pp == NULL)
            root = q;
        else if (p == pp->leftChild)
            pp->leftChild = q;
        else
            pp->rightChild = q;
        if (ps == p)
            pp = q;
        else
            pp = ps;
        delete p;
        p = s;
    }
    binaryTreeNode<pair<const K, E>> *c;
    if (p->leftChild != NULL)
        c = p->leftChild;
    else
        c = p->rightChild;

    // delete p
    if (p == root)
        root = c;
    else
    { // is p left or right child of pp?
        if (p == pp->leftChild)
            pp->leftChild = c;
        else
            pp->rightChild = c;
    }
    treeSize--;
    delete p;
}

template <class K, class E>
void binarySearchTree<K, E>::search(int &rank, binaryTreeNode<pair<const K, E>> *t, int &res)
{
    if (rank > 0 && t != NULL)
    {
        search(rank, t->leftChild, res);
        //if (t != NULL)
        rank--;
        if (rank == 0)
        {
            res = t->element.second;
            return;
        }
        search(rank, t->rightChild, res);
    }
}
template <class K, class E>
void binarySearchTree<K, E>::inOrder(binaryTreeNode<pair<const K, E>> *t)
{
    if (t != NULL)
    {
        inOrder(t->leftChild);
        cout << t->element.second<<" ";
        inOrder(t->rightChild);
    }
}

int main()
{
    // binarySearchTree<int, int> tree;
    // int m;
    // int a, b;
    // int res = 0; //寻找名次对应的element
    // cin >> m;
    // for (int i = 0; i < m; i++)
    // {
    //     cin >> a >> b;

    //     if (a == 0)
    //     {
    //         pair<int, int> p;
    //         p.first = p.second = b;
    //         tree.insert(p);
    //     }
    //     else if (a == 1)
    //     {
    //         tree.find(b);
    //     }
    //     else if (a == 2)
    //     {
    //         tree.erase(b);
    //     }
    //     else if (a == 3)
    //     {
    //         tree.search(b, tree.root, res);
    //         tree.find(res);
    //     }
    //     else if (a == 4)
    //     {
    //         tree.search(b, tree.root, res);
    //         tree.erase(res);
    //     }
    // }
    //tree.inOrder(tree.root);
  
}