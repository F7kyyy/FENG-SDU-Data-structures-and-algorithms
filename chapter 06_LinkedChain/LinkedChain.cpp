#include <iostream>
#include <exception>
#include <sstream>
using namespace std;

class illegalParameterValue //定义异常类
{
public:
    illegalParameterValue(string theMessage = "Illegal parameter value") //初始化
    {
        message = theMessage;
    }
    void outputMessage() { cout << message << endl; }

private:
    string message;
};
class illegalIndex //定义异常类
{
public:
    illegalIndex(string theMessage = "Illegal index") //初始化
    {
        message = theMessage;
    }
    void outputMessage() { cout << message << endl; }

private:
    string message;
};

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
    chain(int initialCapacity = 10);             //该参数无实际意义，只是为了和arrayList类型相容
    ~chain();                                    //析构函数
    void set(int theIndex, const T &theElement); //改变theIndex上的值
    void reverse();                              //倒转
    int lastIndexof(const T &theElement) const;  //最后一次出现元素的theIndex
    void insert(int theIndex, const T &theElement); //插入
    void output(ostream &out) const;
    int size() const { return listSize; } //元素个数
    T &get(int theIndex) const;           //返回element
    void insertSort();                    //插入排序
protected:
    void checkIndex(int theIndex) const;
    chainNode<T> *firstNode;
    int listSize;
};

//构造函数
template <class T>
chain<T>::chain(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << "Must be >0";
        throw illegalParameterValue(s.str());
    }
    firstNode = NULL;
    listSize = 0;
}
template <class T>
chain<T>::~chain()
{ //链表的析构函数，用于删除链表中的所有节点
    while (firstNode != NULL)
    {
        chainNode<T> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template <class T>
void chain<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= listSize)
    {
        ostringstream s;
        s << "Initial capacity = " << theIndex << "Must be >0";
        throw illegalIndex(s.str());
    }
}

template <class T>
void chain<T>::set(int theIndex, const T &theElement)
{
    checkIndex(theIndex);
    chainNode<T> *currentNode = firstNode;
    for (int i = 0; i < theIndex; i++)
        currentNode = currentNode->next;
    currentNode->element = theElement;
}

template <class T>
int chain<T>::lastIndexof(const T &theElement) const
{
    chainNode<T> *currentNode = firstNode;
    int index = 0, result = 0;
    for (currentNode; currentNode != NULL; currentNode = currentNode->next) //因为是找最后一个，所以将链表全部遍历
    {
        index++; //记录元素的标号
        if (currentNode->element == theElement)
        {
            result = index; //找到相同的值就更新标号
        }
    }
    if (result == 0)
        return -1;
    else
        return result;
}

template <class T>
void chain<T>::reverse()
{
    chainNode<T> *currentNode = NULL;
    for (currentNode; firstNode; swap(firstNode, currentNode))
        swap(currentNode, firstNode->next);
    firstNode = currentNode;
}

template <class T>
//在索引theIndex插入theElement
void chain<T>::insert(int theIndex, const T &theElement)
{
    if ((theIndex < 0) || theIndex > listSize)
    {
        ostringstream s;
        s << "index =" << theIndex << "size =" << listSize;
        throw illegalIndex(s.str());
    }
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
template <class T>
void chain<T>::output(ostream &out) const
{
    for (chainNode<T> *currentNode = firstNode;
         currentNode != NULL;
         currentNode = currentNode->next)
        out << currentNode->element << "  ";
}

template <class T>
ostream &operator<<(ostream &out, const chain<T> &x)
{
    x.output(out);
    return out;
}

template <class T>
T &chain<T>::get(int theIndex) const
{
    chainNode<T> *currentNode = firstNode;
    for (int i = 0; i < theIndex; i++)    //指向 theIndex的前一个元素
        currentNode = currentNode->next;
    return currentNode->element;
}

template <class T>
void chain<T>::insertSort()
{
    int j = 0;
    for (int i = 0; i < listSize; i++) //就是正常的插入排序
    {
        T t = get(i);
        for (j = i - 1; j >= 0 && t < get(j); j--)
        {
            set(j + 1, get(j));
        }
        set(j + 1, t);
    }
}

template <class T>
class extendedChain : public chain<T>
{
public:
    extendedChain(int initialCapacity = 10) : chain<T>(initialCapacity) {}
    extendedChain(const extendedChain<T> &c) : chain<T>(c) {}
    void push_back(const T &theElement);

protected:
    chainNode<T> *lastNode; // pointer to last node in chain
    chainNode<T> *firstNode;
    int listSize;
};

template <class T>
void extendedChain<T>::push_back(const T &theElement)
{ //后插节点方法
    chainNode<T> *newNode = new chainNode<T>(theElement, NULL);
    if (firstNode == NULL)
    { //链表非空
        firstNode = lastNode = newNode;
    }
    else
    {
        lastNode->next = newNode;
        lastNode = newNode;
    }
    listSize++;
}


//加法实现meld
template <class T>
void meld(extendedChain<T> &a, extendedChain<T> &b, extendedChain<T> &c)
{ 
    int i;
    int j = 0;
    for (i = 0; i < a.size() + b.size(); i++)
    { //将a，b的元素依次放入c的尾部
        if (i < a.size())
        {
            c.insert(j, a.get(i));
            j++;
        }
        if (i < b.size())
        {
            c.insert(j, b.get(i));
            j++;
        }
    }
}

int main()
{
    chain<int> l;
    for (int i = 0; i < 5; i++)
    {
        l.insert(i, 2 * i + 1);
    }
    cout << l << endl; //验证insert
    l.set(3, 2);
    l.set(2, 2); //验证set
    cout << l << endl;
    cout << l.lastIndexof(2) << endl; //验证lastIndexof
    l.reverse();
    cout << l << endl; //验证倒转
    extendedChain<int> l1, l2, l3;
    for (int i = 0; i < 3; i++)
        l1.insert(i, 2 * i + 1);

    for (int i = 0; i < 5; i++)
        l2.insert(i, 2 * i);

    cout << l1 << endl
         << l2 << endl;
    meld(l1, l2, l3); //验证meld
    cout << l3 << endl;

    l3.insertSort(); //验证插入排序
    cout << l3 << endl;
}
