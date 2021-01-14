#include <iostream>
#include <queue>
using namespace std;

template <class T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T> *leftChild, // left subtree
        *rightChild;              // right subtree
    int leftSize;
    binaryTreeNode() { leftChild = rightChild = NULL; }
    binaryTreeNode(const T &theElement) : element(theElement)
    {
        leftChild = rightChild = NULL;
        leftSize = 0;
    }
    binaryTreeNode(const T &theElement,
                   binaryTreeNode *theLeftChild,
                   binaryTreeNode *theRightChild)
        : element(theElement)
    {
        leftChild = theLeftChild;
        rightChild = theRightChild;
        leftSize = numberOfNodes(theLeftChild);
    }

    binaryTreeNode(const T &theElement,
                   binaryTreeNode *theLeftChild, binaryTreeNode *theRightChild,
                   int theleftSize) : element(theElement)
    {
        leftChild = theLeftChild;
        rightChild = theRightChild;
        leftSize = theleftSize;
    }

    int numberOfNodes(binaryTreeNode<T> *theNode)
    {
        if (theNode == NULL)
            return 0;
        else
            return numberOfNodes(theNode->leftChild) + numberOfNodes(theNode->rightChild) + 1;
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
    void search(K thekey);
    void del(K thekey);
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
        root = newNode; //空树，根节点
    treeSize++;
    cout << result << endl;
    //更新插入后的leftSize
    p = root;
    while (p->element != thePair)
    {
        if (p->element.second < thePair.second)
            p = p->rightChild;
        else if (p->element.second > thePair.second) //可以往左移，则leftSize++
        {
            p->leftSize++;
            p = p->leftChild;
        }
    }
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
    //找到输出异或和
    cout << (result ^ p->element.second) << endl;

    // 更新leftSize
    p = root;
    while (p != NULL && p->element.first != theKey)
    {
        if (p->element.first < theKey)
        {
            p = p->rightChild;
        }
        else if (p->element.first > theKey)
        { // 删除节点在当前节点的左子树
            p->leftSize--;
            p = p->leftChild;
        }
    }

    if (p->leftChild != NULL && p->rightChild != NULL)
    { //此时有两个孩子
        binaryTreeNode<pair<const K, E>> *s = p->rightChild,
                                         *ps = p;
        while (s->leftChild != NULL)
        {
            s->leftSize--; ///删除节点在左侧，更新listSize
            ps = s;
            s = s->leftChild;
        }

        binaryTreeNode<pair<const K, E>> *q =
            new binaryTreeNode<pair<const K, E>>(s->element, p->leftChild, p->rightChild, p->leftSize);
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
    //要删除节点只有一个孩子
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
void binarySearchTree<K, E>::search(K thekey)
{
    binaryTreeNode<pair<const K, E>> *theNode = root;
    int result = 0;
    while (theNode != NULL && theNode->leftSize != thekey)
    {
        result ^= theNode->element.second;
        if (theNode->leftSize > thekey) // 应在左子树搜索，thekey不变
        {
            theNode = theNode->leftChild;
        }
        else if (theNode->leftSize < thekey) // 应在右子树搜索,thekey为减去左子树和根节点
        {                                    // 应在右子树搜索
            thekey = thekey - theNode->leftSize - 1;
            theNode = theNode->rightChild;
        }
    }
    if (theNode == NULL)
        cout << 0 << endl;
    else
        cout << (result ^ theNode->element.second) << endl;
}

template <class K, class E>
void binarySearchTree<K, E>::del(K thekey)
{
    K result = 0;
    binaryTreeNode<pair<const K, E>> *p = root,
                                     *pp = NULL;
    while (p != NULL && p->leftSize != thekey)
    {
        pp = p;
        if (thekey < p->leftSize)
        {
            result ^= p->element.second;
            p = p->leftChild;
        }
        else if (thekey > p->leftSize)
        {
            thekey = thekey - p->leftSize - 1; //向右更新thekey
            result ^= p->element.second;
            p = p->rightChild;
        }
    }
    if (p == NULL)
    {
        cout << 0 << endl;
        return;
    }
    //找到输出异或和
    cout << (result ^ p->element.second) << endl;
    thekey = p->element.first;
    // 更新leftSize
    p = root;

    while (p != NULL && p->element.first != thekey)
    {
        if (p->element.first < thekey)
        {
            p = p->rightChild;
        }
        else if (p->element.first > thekey)
        { // 删除节点在当前节点的左子树
            p->leftSize--;
            p = p->leftChild;
        }
    }

    if (p->leftChild != NULL && p->rightChild != NULL)
    { //此时有两个孩子
        binaryTreeNode<pair<const K, E>> *s = p->rightChild,
                                         *ps = p;
        while (s->leftChild != NULL)
        {
            s->leftSize--; ///删除节点在左侧，更新listSize
            ps = s;
            s = s->leftChild;
        }

        binaryTreeNode<pair<const K, E>> *q =
            new binaryTreeNode<pair<const K, E>>(s->element, p->leftChild, p->rightChild, p->leftSize);
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
    //要删除节点只有一个孩子
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
void binarySearchTree<K, E>::inOrder(binaryTreeNode<pair<const K, E>> *t)
{
    if (t != NULL)
    {
        inOrder(t->leftChild);
        cout << t->element.second << " ";
        inOrder(t->rightChild);
    }
}

int main()
{
    binarySearchTree<int, int> tree;
    int m;
    int a, b;

    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;

        if (a == 0)
        {
            pair<int, int> p;
            p.first = p.second = b;
            tree.insert(p);
        }
        else if (a == 1)
        {
            tree.find(b);
        }
        else if (a == 2)
        {
            tree.erase(b);
        }
        else if (a == 3)
        {
            tree.search(b - 1);
        }
        else if (a == 4)
        {
            tree.del(b - 1);
        }
    }
    //tree.inOrder(tree.root);
}
