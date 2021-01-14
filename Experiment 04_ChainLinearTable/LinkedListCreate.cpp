#include <iostream>
using namespace std;

template <class T>
struct chainNode
{
    T element;
    chainNode<T> *next;
    chainNode() {}
    chainNode(const T &element)
    {
        this->element = element;
    }
    chainNode(const T &element, chainNode<T> *next)
    {
        this->element = element;
        this->next = next;
    }
};

template <class T>
class chain
{
public:
    chain(int initialCapacity = 10);
    ~chain();
    T getsize() { return listSize; }
    void insert(int theIndex, const T &theElement); //插入
    void erase(int theElement);                     //删除
    void reverse();                                 //原地转置
    void search(int theElement) const;              //查询
    void sum();                                     //异或和
    void output(ostream &out) const;                //输出
    class iterator                                  //声明定义迭代器
    {
    public:
        iterator(chainNode<T> *n = NULL) { node = n; }
        int &operator*() const { return node->element; }
        int *operator->() const { return &node->element; }
        iterator &operator++()
        {
            node = node->next;
            return *this;
        }
        iterator operator++(int)
        {
            iterator old = *this;
            node = node->next;
            return old;
        }
        bool operator!=(const iterator right) const
        {
            return node != right.node;
        }
        bool operator==(const iterator right) const
        {
            return node == right.node;
        }

    protected:
        chainNode<T> *node;
    };
    chain::iterator begin() { return iterator(firstNode); } //迭代器开头
    chain::iterator end() { return iterator(NULL); }        //迭代器末尾
private:
    chainNode<T> *firstNode;
    int listSize;
};

//构造函数
template <class T>
chain<T>::chain(int initialCapacity)
{
    firstNode = NULL;
    listSize = 0;
}

//链表的析构函数，用于删除链表中的所有节点
template <class T>
chain<T>::~chain()
{
    while (firstNode != NULL)
    {
        chainNode<T> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}
//在索引theIndex插入theElement
template <class T>
void chain<T>::insert(int theIndex, const T &theElement)
{
    // 第一个节点前插入
    if (theIndex == 0)
        firstNode = new chainNode<T>(theElement, firstNode);
    else
    {
        chainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next; //将p移动至第theIndex-1个元素
        p->next = new chainNode<T>(theElement, p->next);
    }
    listSize++;
}

//删除元素
template <class T>
void chain<T>::erase(int theElement)
{ //单独考虑删除第一个节点元素
    chainNode<T> *currentNode = firstNode;
    chainNode<T> *nextNode = firstNode->next;
    if (currentNode->element == theElement)
    {
        firstNode = currentNode->next;
        delete currentNode;
        listSize--;
    }
    //删除其他节点
    else
    {
        while (nextNode != NULL)
        {
            if (nextNode->element == theElement)
            {
                currentNode->next = nextNode->next; //令前一个节点的next
                delete nextNode;                    //指向被删除节点的下一个
                listSize--;
                break;
            }
            currentNode = currentNode->next;
            nextNode = nextNode->next;
        }
        if (nextNode == NULL)
            cout << "-1" << endl;
    }
}

//原地逆置
template <class T>
void chain<T>::reverse()
{
    chainNode<T> *currentNode = NULL;
    for (currentNode; firstNode; swap(firstNode, currentNode))
        swap(currentNode, firstNode->next);
    firstNode = currentNode;
    // chainnode<T> *temporarynode = firstnode;
    // firstnode = firstnode->next;
    // temporarynode->next = NULL;
    // chainnode<T> *cnode = firstnode->next;
    // for (int i = 0; i != listsize - 3; i++)
    // {
    //     firstnode->next = temporarynode;
    //     temporarynode = firstnode;
    //     firstnode = cnode;
    //     cnode = firstnode->next;
    // }
    // firstnode->next = temporarynode;
    // cnode->next = firstnode;
    // firstnode = cnode;
}

//查询
template <class T>
void chain<T>::search(int theElement) const
{
    chainNode<T> *p = firstNode;
    int index = 0;
    //用while循环遍历链表直到p->element==参数
    while (p != NULL && p->element != theElement)
    {
        p = p->next;
        index++;
    }

    if (p == NULL)
        cout << -1 << endl;
    else
        cout << index << endl;
    
}

//求异或和
template <typename T>
void chain<T>::sum()
{

    int sum = 0, i = 0;
    for (chain<T>::iterator it = this->begin(); it != this->end(); it++)
    {

        sum += ((*it) ^ i);
        i++;
    }

    cout << sum << endl;
}

//输出函数
template <class T>
void chain<T>::output(ostream &out) const
{
    for (chainNode<T> *currentNode = firstNode;
         currentNode != NULL;
         currentNode = currentNode->next)
        out << currentNode->element << "  ";
}

//运算符重载
template <class T>
ostream &operator<<(ostream &out, const chain<T> &x)
{
    x.output(out);
    return out;
}

int main()
{
    int m, n, theElement, theIndex;
    cin >> m >> n;
    chain<int> l;
    for (int i = 0; i < m; i++)
    {
        cin >> theElement;
        l.insert(i, theElement);
    }
    for (int i = 0; i < n; i++)
    {
        cin >> theIndex;
        switch (theIndex)
        {
        case 1:
            cin >> theIndex >> theElement;
            l.insert(theIndex, theElement);
            break;
        case 2:
            cin >> theElement;
            l.erase(theElement);
            break;
        case 3:
            l.reverse();
            break;
        case 4:
            cin >> theElement;
            l.search(theElement);
            break;
        case 5:
            l.sum();
        }
    }
}