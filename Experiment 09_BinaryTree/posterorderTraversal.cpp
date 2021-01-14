#include <iostream>
using namespace std;

template <class T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T> *leftChild, *rightChild;
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

template <class T>
class binaryTree
{
public:
    void postOrder(binaryTreeNode<T> *t);
    void visit(binaryTreeNode<T> *x);
    int searchRoot(T theElement, T *array, int len)
    { //找到子树的根
        for (int i = 0; i < len; i++)
            if (array[i] == theElement)
                return i;
        return -1;
    }
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
binaryTreeNode<T> *binaryTree<T>::ResumeBinaryTree(T *preTree, T *inTree, int len) //前序遍历，中序遍历，中序数组长度
{
    if (len <= 0) //空树
        return NULL;
    binaryTreeNode<T> *temp = new binaryTreeNode<T>;
    temp->element = *preTree;                                                                      //前序遍历的第一个为二叉树的根
    int index = searchRoot(*preTree, inTree, len);                                                 //找到中序遍历中root所在位置，区分左子树和右子树
    temp->leftChild = ResumeBinaryTree(preTree + 1, inTree, index);                            //左子树就是前序遍历的preTree+1开始到preTree+index停止,中序就是inTree 到inTree+index-1
    temp->rightChild = ResumeBinaryTree(preTree + index + 1, inTree + index + 1, len - index - 1); //右子树就是剩下的节点
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

