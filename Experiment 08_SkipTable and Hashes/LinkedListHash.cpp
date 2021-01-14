#include <iostream>
using namespace std;

template <class K>
class Hash;
template <>
class Hash<int>
{
public:
    size_t operator()(const int theKey) const
    {
        return size_t(theKey);
    }
};

template <class K, class E>
struct pairNode
{
    typedef pair<const K, E> pairType;
    pairType element;
    pairNode<K, E> *next;

    pairNode(const pairType &thePair) : element(thePair) {}
    pairNode(const pairType &thePair, pairNode<K, E> *theNext)
        : element(thePair) { next = theNext; }
};

template <class K, class E>
class sortedChain
{
public:
    sortedChain()
    {
        firstNode = NULL;
        dSize = 0;
    }
    ~sortedChain();
    int size() const { return dSize; }
    void find(const K &) const;
    void erase(const K &);
    void insert(const pair<const K, E> &);

protected:
    pairNode<K, E> *firstNode; // 指向链中第一个节点的指针
    int dSize;                 // 字典中的元素数
};

template <class K, class E>
sortedChain<K, E>::~sortedChain()
{ // 析构函数。删除所有节点。
    while (firstNode != NULL)
    { // 删除 firstNode
        pairNode<K, E> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template <class K, class E>
void sortedChain<K, E>::find(const K &theKey) const
{
    pairNode<K, E> *currentNode = firstNode;
    // 用theKey搜索匹配
    while (currentNode != NULL && currentNode->element.first != theKey)
        currentNode = currentNode->next;
    if (currentNode != NULL && currentNode->element.first == theKey) // 验证匹配
        cout << dSize << endl;
    else
        cout << "Not Found" << endl;
}

template <class K, class E>
void sortedChain<K, E>::insert(const pair<const K, E> &thePair)
{
    pairNode<K, E> *p = firstNode, *tp = NULL;

    // 移至以便可以在tp之后插入对
    while (p != NULL && p->element.first < thePair.first)
    {
        tp = p;
        p = p->next;
    }

    //检查是否有匹配的对
    if (p != NULL && p->element.first == thePair.first)
    { // 取代旧值
        p->element.second = thePair.second;
        cout << "Existed" << endl;
        return;
    }
    pairNode<K, E> *newNode = new pairNode<K, E>(thePair, p);
    if (tp == NULL)
        firstNode = newNode;
    else
        tp->next = newNode;

    dSize++;
    return;
}

template <class K, class E>
void sortedChain<K, E>::erase(const K &theKey)
{
    pairNode<K, E> *p = firstNode, *tp = NULL;
    while (p != NULL && p->element.first < theKey)
    {
        tp = p;
        p = p->next;
    }
    if (p != NULL && p->element.first == theKey)
    {
        if (tp == NULL)
            firstNode = p->next;
        else
            tp->next = p->next;

        delete p;
        dSize--;
        cout << dSize << endl;
    }
    else
        cout << "Delete Failed" << endl;
}

template <class K, class E>
class hashChains
{
public:
    hashChains(int theDivisor = 11)
    {
        divisor = theDivisor;
        dSize = 0;
        table = new sortedChain<K, E>[divisor]; //分配和初始化哈希表数组
    }
    ~hashChains() { delete[] table; }
    int size() const { return dSize; }
    void find(const K &theKey) const
    {
        table[hash(theKey) % divisor].find(theKey);
    }
    void insert(const pair<const K, E> &thePair)
    {
        int homeBucket = (int)hash(thePair.first) % divisor;
        //int homeSize = table[homeBucket].size();
        table[homeBucket].insert(thePair);
        // if (table[homeBucket].size() > homeSize)
        //     dSize++;
    }

    void erase(const K &theKey)
    {
        table[hash(theKey) % divisor].erase(theKey);
    }

protected:
    sortedChain<K, E> *table; // 哈希表
    Hash<K> hash;             // 将类型K映射到非负整数
    int dSize;                // 列表中的元素数
    int divisor;              // 哈希函数除数
};

int main()
{
    int n, dvisor, numble;
    cin >> dvisor >> n;
    hashChains<int, int> h(dvisor);
    for (int i = 0; i < n; i++)
    {
        pair<int, int> x;
        cin >> numble;
        switch (numble)
        {
        case 0:
            cin >> x.first;
            x.second = x.first;
            h.insert(x);
            break;
        case 1:
            cin >> x.first;
            h.find(x.first);
            break;
        case 2:
            cin >> x.first;
            x.second = x.first;
            h.erase(x.first);
            break;
        }
    }
    return 0;
}