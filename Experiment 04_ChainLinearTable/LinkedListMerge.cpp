#include <iostream>
using namespace std;

struct chainNode
{
    int element;
    chainNode *next;
    chainNode() {}
    chainNode(const int &element)
    {
        this->element = element;
    }
    chainNode(const int &element, chainNode *next)
    {
        this->element = element;
        this->next = next;
    }
};

class chain
{
    friend ostream &operator<<(ostream &out, chain &x); //运算符重载
public:
    chain(int initialCapacity = 10);
    ~chain();
    void insert(int theIndex, const int &theElement); //插入数据
    void bubbleSort();                                //插入排序
    void sum();                                       //求异或和
    void meld(chain &a, chain &b);                    //两链表合并
    class iterator
    {
    public:
        iterator(chainNode *n = NULL) { node = n; }
        int &operator*() const { return node->element; }
        int *operator->() const { return &node->element; }
        iterator &operator++() //前置
        {
            node = node->next;
            return *this;
        }
        iterator operator++(int) //后置
        {
            iterator old = *this;
            node = node->next;
            return old;
        }
        bool operator!=(const iterator right) const //不等于
        {
            return node != right.node;
        }
        bool operator==(const iterator right) const //等于
        {
            return node == right.node;
        }

    protected:
        chainNode *node;
    };
    chain::iterator begin() { return iterator(firstNode); } //迭代器开头
    chain::iterator end() { return iterator(NULL); }        //迭代器末尾

private:
    chainNode *firstNode;              
    int listSize;
};

//构造函数
chain::chain(int initialCapacity)
{
    firstNode = NULL;
    listSize = 0;
}

//链表的析构函数，用于删除链表中的所有节点
chain::~chain()
{
    while (firstNode != NULL)
    {
        chainNode *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

//在索引theIndex插入theElement
void chain::insert(int theIndex, const int &theElement)
{
    // 第一个节点前插入
    if (theIndex == 0)
        firstNode = new chainNode(theElement, firstNode);
    else
    {
        chainNode *p = firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next; //将p移动至第theIndex-个元素
        p->next = new chainNode(theElement, p->next);
    }
    listSize++;
}

//及时终止的冒泡排序
void chain::bubbleSort()
{
    if (listSize < 1)
        return;
    chainNode *p = firstNode;
    chainNode *q = firstNode->next;
    bool sorted = true;
    for (int i = 0; sorted && i < listSize; i++)
    {
        sorted = false;
        for (int j = 0; j < listSize - 1 - i; j++)
        {
            if (p->element > q->element)
            {
                swap(p->element, q->element);
                sorted = true;
            }
            p = p->next;
            q = q->next;
        }
        p = firstNode;
        q = firstNode->next;
    }
}

//两链表合并
void chain::meld(chain &a, chain &b)
{
    chain::iterator t1 = a.begin();
    chain::iterator t2 = b.begin();
    for (int i = 0; i < b.listSize; i++)
    {
        insert(i, *t2);
        t2++;
    }

    for (int i = 0; i < a.listSize; i++)
    {
        insert(i, *t1);
        t1++;
    }
}

//求异或和
void chain::sum()
{
    int sum = 0, i = 0;
    for (chain::iterator it = this->begin(); it != this->end(); it++)
    {

        sum += ((*it) ^ i);    
        i++;
    }
    cout << sum << endl;
}

//重载运算符，输出链表
ostream &operator<<(ostream &out, chain &x)
{
    chainNode *p = x.firstNode;
    while (p != NULL)
    {
        out << p->element << " ";
        p = p->next;
    }
    return out;
}

int main()
{
    int m, n, theElement;
    cin >> m >> n;
    chain l1, l2, l3;
    for (int i = 0; i < m; i++)
    {
        cin >> theElement;
        l1.insert(i, theElement);
    }
    for (int i = 0; i < n; i++)
    {
        cin >> theElement;
        l2.insert(i, theElement);
    }
    l1.bubbleSort();
    l1.sum();
    l2.bubbleSort();
    l2.sum();
    l3.meld(l1, l2);
    l3.bubbleSort();
    l3.sum();
}