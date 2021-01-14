#include <iostream>
using namespace std;

template <class T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T> *leftChild,
        *rightChild;              

    binaryTreeNode() { leftChild = rightChild = NULL; }
    binaryTreeNode(const T &theElement) : element(theElement)
    {
        leftChild = rightChild = NULL;
    }
    binaryTreeNode(const T &theElement, binaryTreeNode *theLeftChild,binaryTreeNode *theRightChild) 
    : element(theElement)
    {
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }
};

template <class T>
class binaryTree
{
public:
    void postOrder(binaryTreeNode<T> *t);
    void visit(binaryTreeNode<T> *x);
    int searchRoot(T theElement, T *array, int len)
    {
        for (int i = 0; i < len; i++)
            if (array[i] == theElement)
                return i;
        return -1;
    }
    binaryTreeNode<T> *reduction(T *preOrder, T *inOrder, int phead, int ptail, int ihead, int itail);

    binaryTreeNode<T> *ResumeBinaryTree(T *preTree, T *inTree, int len);

protected:
    binaryTreeNode<T> *root;
};

template <class T>
void binaryTree<T>::visit(binaryTreeNode<T> *x)
{
    cout << x->element << " ";
}

template <class T>
void binaryTree<T>::postOrder(binaryTreeNode<T> *t)
{
    if (t != NULL)
    {
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        visit(t);
    }
}

template <class T>
binaryTreeNode<T> *binaryTree<T>::ResumeBinaryTree(T *preTree, T *inTree, int len)
{
    if (len <= 0)
        return NULL;
    binaryTreeNode<T> *temp = new binaryTreeNode<T>;
    temp->element = *preTree;
    int index = searchRoot(*preTree, inTree, len);
    temp->leftChild = ResumeBinaryTree(preTree + 1, inTree, index);
    temp->rightChild = ResumeBinaryTree(preTree + index + 1, inTree + index + 1, len - index - 1);
    return temp;
}



int main()
{
    int number;
    cin >> number;
    int m_preTree[number];
    int m_inTree[number];
    for (int i = 0; i < number; i++)
    {
        cin >> m_preTree[i];
    }
    for (int i = 0; i < number; i++)
    {
        cin >> m_inTree[i];
    }
    binaryTree<int> T;
    T.postOrder(T.ResumeBinaryTree(m_preTree, m_inTree, number));
  
}

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
    binaryTreeNode(const T &theElement,
                   binaryTreeNode *theLeftChild,
                   binaryTreeNode *theRightChild)
        : element(theElement)
    {
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }
};

template <class T>
class arrayQueue
{
public:
    arrayQueue(int initialCapacity = 10);
    ~arrayQueue() { delete[] queue; }
    bool empty() const { return theFront == theBack; }
    int size() const
    {
        return (theBack - theFront + arrayLength) % arrayLength;
    }
    T &front()
    {
        return queue[(theFront + 1) % arrayLength];
    }
    T &back()
    {
        return queue[theBack];
    }
    void pop()
    {
        theFront = (theFront + 1) % arrayLength;
        queue[theFront].~T();
    }
    void push(const T &theElement);

private:
    int theFront;
    int theBack;
    int arrayLength;
    T *queue;
};

template <class T>
arrayQueue<T>::arrayQueue(int initialCapacity)
{
    arrayLength = initialCapacity;
    queue = new T[arrayLength];
    theFront = 0;
    theBack = 0;
}

template <class T>
void arrayQueue<T>::push(const T &theElement)
{
    if ((theBack + 1) % arrayLength == theFront)
    {
        T *newQueue = new T[2 * arrayLength];

        int start = (theFront + 1) % arrayLength;
        if (start < 2)

            copy(queue + start, queue + start + arrayLength - 1, newQueue);
        else
        {
            copy(queue + start, queue + arrayLength, newQueue);
            copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
        }

        theFront = 2 * arrayLength - 1;
        theBack = arrayLength - 2;
        arrayLength *= 2;
        queue = newQueue;
    }

    theBack = (theBack + 1) % arrayLength;
    queue[theBack] = theElement;
}

struct booster
{
    int degradeToLeaf,     // degradation to leaf
        degradeFromParent; // degradation from parent
    bool boosterHere;      // true iff booster here

    void output(ostream &out) const
    {
        out << boosterHere << ' ' << degradeToLeaf << ' '
            << degradeFromParent << ' ';
    }
};

// overload <<
ostream &operator<<(ostream &out, booster x)
{
    x.output(out);
    return out;
}

template <class E>
class linkedBinaryTree
{
public:
    linkedBinaryTree()
    {
        root = NULL;
        treeSize = 0;
    }
    ~linkedBinaryTree() { erase(); };
    bool empty() const { return treeSize == 0; }
    int size() const { return treeSize; }
    E *rootElement() const;
    void makeTree(const E &element, linkedBinaryTree<E> &, linkedBinaryTree<E> &);
    linkedBinaryTree<E> &removeLeftSubtree();
    linkedBinaryTree<E> &removeRightSubtree();
    void preOrder(void (*theVisit)(binaryTreeNode<E> *))
    {
        visit = theVisit;
        preOrder(root);
    }
    void inOrder(void (*theVisit)(binaryTreeNode<E> *))
    {
        visit = theVisit;
        inOrder(root);
    }
    void postOrder(void (*theVisit)(binaryTreeNode<E> *))
    {
        visit = theVisit;
        postOrder(root);
    }
    void levelOrder(void (*)(binaryTreeNode<E> *));
    void preOrderOutput()
    {
        preOrder(output);
        cout << endl;
    }
    void inOrderOutput()
    {
        inOrder(output);
        cout << endl;
    }
    void postOrderOutput()
    {
        postOrder(output);
        cout << endl;
    }
    void levelOrderOutput()
    {
        levelOrder(output);
        cout << endl;
    }
    void erase()
    {
        postOrder(dispose);
        root = NULL;
        treeSize = 0;
    }
    int height() const { return height(root); }

protected:
    binaryTreeNode<E> *root;                   // pointer to root
    int treeSize;                              // number of nodes in tree
    static void (*visit)(binaryTreeNode<E> *); // visit function
    static int count;                          // used to count nodes in a subtree
    static void preOrder(binaryTreeNode<E> *t);
    static void inOrder(binaryTreeNode<E> *t);
    static void postOrder(binaryTreeNode<E> *t);
    static void countNodes(binaryTreeNode<E> *t)
    {
        visit = addToCount;
        count = 0;
        preOrder(t);
    }
    static void dispose(binaryTreeNode<E> *t) { delete t; }
    static void output(binaryTreeNode<E> *t)
    {
        cout << t->element << ' ';
    }
    static void addToCount(binaryTreeNode<E> *t)
    {
        count++;
    }
    static int height(binaryTreeNode<E> *t);
};

template<class T>
void (*linkedBinaryTree<T>::visit)(binaryTreeNode<T> *);

template <class E>
E *linkedBinaryTree<E>::rootElement() const
{ 
    if (treeSize == 0)
        return NULL; // no root
    else
        return &root->element;
}

template <class E>
void linkedBinaryTree<E>::makeTree(const E &element,
                                   linkedBinaryTree<E> &left, linkedBinaryTree<E> &right)
{
    root = new binaryTreeNode<E>(element, left.root, right.root);
    treeSize = left.treeSize + right.treeSize + 1;
    left.root = right.root = NULL;
    left.treeSize = right.treeSize = 0;
}

template <class E>
linkedBinaryTree<E> &linkedBinaryTree<E>::removeLeftSubtree()
{

    linkedBinaryTree<E> leftSubtree;
    leftSubtree.root = root->leftChild;
    count = 0;
    leftSubtree.treeSize = countNodes(leftSubtree.root);
    root->leftChild = NULL;
    treeSize -= leftSubtree.treeSize;
    return leftSubtree;
}
template <class E>
linkedBinaryTree<E> &linkedBinaryTree<E>::removeRightSubtree()
{

    linkedBinaryTree<E> rightSubtree;
    rightSubtree.root = root->rightChild;
    count = 0;
    rightSubtree.treeSize = countNodes(rightSubtree.root);
    root->rightChild = NULL;
    treeSize -= rightSubtree.treeSize;

    return rightSubtree;
}

template <class E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E> *t)
{
    if (t != NULL)
    {
        linkedBinaryTree<E>::visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

template <class E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E> *t)
{
    if (t != NULL)
    {
        inOrder(t->leftChild);
        linkedBinaryTree<E>::visit(t);
        inOrder(t->rightChild);
    }
}

template <class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E> *t)
{ // Postorder traversal.
    if (t != NULL)
    {
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        linkedBinaryTree<E>::visit(t);
    }
}

template <class E>
void linkedBinaryTree<E>::levelOrder(void (*theVisit)(binaryTreeNode<E> *))
{ 
    arrayQueue<binaryTreeNode<E> *> q;
    binaryTreeNode<E> *t = root;
    while (t != NULL)
    {
        theVisit(t); 

        if (t->leftChild != NULL)
            q.push(t->leftChild);
        if (t->rightChild != NULL)
            q.push(t->rightChild);

        // get next node to visit
        
        if (q.empty())
        {
            return;
        }
        else
        {
            t = q.front();
            q.pop();
        }
    }
}

template <class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E> *t)
{ // Return height of tree rooted at *t.
    if (t == NULL)
        return 0;                   // empty tree
    int hl = height(t->leftChild);  // height of left
    int hr = height(t->rightChild); // height of right
    if (hl > hr)
        return ++hl;
    else
        return ++hr;
}
struct st
{
    int left;
    int right;
};

int main()
{
    linkedBinaryTree<int> a;
    int n;
    cin >> n;
    linkedBinaryTree<int> t[100001];
    struct st s[100001];
    int height[100001];
    int size[100001];
    for (int i = 1; i <= n; i++)
    {
        int L, R;
        cin >> L >> R;
        s[i].left = L;
        s[i].right = R;
    }

    for (int i = n; i >= 1; i--)
    {
        if (s[i].left != -1 && s[i].right != -1)
        {
            t[i].makeTree(i, t[s[i].left], t[s[i].right]);
        }
        if (s[i].left != -1 && s[i].right == -1)
        {
            t[i].makeTree(i, t[s[i].left], a);
        }
        if (s[i].left == -1 && s[i].right != -1)
        {
            t[i].makeTree(i, a, t[s[i].right]);
        }
        if (s[i].left == -1 && s[i].right == -1)
        {
            t[i].makeTree(i, a, a);
        }

        height[i] = t[i].height();
        size[i] = t[i].size();
    }

    t[1].levelOrderOutput();

    for (int i = 1; i <= n; i++)
    {
        cout << size[i] << " ";
    }
    cout << endl;

    for (int i = 1; i <= n; i++)
    {
        cout << height[i] << " ";
    }
}
