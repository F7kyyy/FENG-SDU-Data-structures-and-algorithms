#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node *next;
    Node *prev;
    Node(T x)
    {
        data = x;
        next = NULL;
        prev = NULL;
    }
};

template <class T>
class DoublyLinkedList
{
public:
    DoublyLinkedList();
    DoublyLinkedList(T x);
    ~DoublyLinkedList();                      //析构函数
    int getSize();                            //获取链表的元素个数
    bool isEmpty() { return listSize == 0; }  //判断链表是否为空
    void clear();                             //清空链表
    void insert(int index, const T &theData); //添加元素到指定位置
    T get(int index);                         //获取指定元素
    T remove(int index);                      //删除指定元素
    T set(int index, T theData);              //修改指定元素
    void output(ostream &out) const;          //输出链表
private:
    Node<T> *firstNode;
    Node<T> *lastNode;
    int listSize;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
    firstNode = NULL;
    lastNode = NULL;
    listSize = 0;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(T x)
{
    firstNode = new Node<T>(x);
    lastNode = firstNode;
    listSize = 1;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    if (listSize == 0)
        return;
    else
    {
        Node<T> *p;
        Node<T> *q;
        p = firstNode;
        q = lastNode;
        while (p->next != q && p != q)
        {
            p = p->next;
            delete firstNode;
            firstNode = p;
            q = q->prev;
            delete lastNode;
            lastNode = q;
        }
        if (p == q || p->next == q)
        {
            delete p;
            p = NULL;
            q = NULL;
        }
    }
}

template <typename T>
int DoublyLinkedList<T>::getSize()
{
    return listSize;
}

template <typename T>
void DoublyLinkedList<T>::clear()
{
    if (listSize == 0)
        cout << "链表为空";
    else
    {
        Node<T> *p;
        Node<T> *q;
        p = firstNode;
        q = lastNode;
        while (p->next != q && p != q)
        {
            p = p->next;
            delete firstNode;
            firstNode = p;
            q = q->prev;
            delete lastNode;
            lastNode = q;
        }
        if (p == q || p->next == q)
        {
            delete p;
            p = NULL;
            q = NULL;
        }
        firstNode = NULL;
        lastNode = NULL;
        listSize = 0;
    }
}

template <typename T>
void DoublyLinkedList<T>::insert(int index, const T &theData)
{

    if (index < 0 || index > listSize)
        cout << "error" << endl;
    else if (index == 0)
    {
        if (listSize != 0)
        {
            Node<T> *cur;
            cur = new Node<T>(theData);
            cur->next = firstNode;
            firstNode->prev = cur;
            cur->prev = NULL;
            firstNode = cur;
            listSize++;
        }
        else
        {
            firstNode = new Node<T>(theData);
            lastNode = firstNode;
            listSize = 1;
        }
    }
    else if (index == listSize)
    {
        if (listSize != 0)
        {
            Node<T> *cur;
            cur = new Node<T>(theData);
            cur->prev = lastNode;
            lastNode->next = cur;
            cur->next = NULL;
            lastNode = cur;
            listSize++;
        }
        else
        {
            lastNode = new Node<T>(theData);
            firstNode = lastNode;
            listSize = 1;
        }
    }

    else
    {
        if (index < (listSize / 2))
        {
            Node<T> *p = firstNode;
            Node<T> *temp;
            temp = new Node<T>(theData);
            for (int i = 0; i < index - 1; i++)
            {
                p = p->next;
            }
            temp->next = p->next;
            p->next->prev = temp;
            p->next = temp;
            temp->prev = p;
            listSize++;
        }
        else
        {
            Node<T> *p = lastNode;
            Node<T> *temp;
            temp = new Node<T>(theData);
            for (int i = listSize - 1; i < index - 1; i++)
            {
                p = p->prev;
            }
            temp->prev = p->prev;
            p->prev->next = temp;
            p->prev = temp;
            temp->next = p;
            listSize++;
        }
    }
}

template <typename T>
T DoublyLinkedList<T>::get(int index)
{
    if (index < 0 || index >= listSize)
    {
        cout << "get函数错误,错误原因:index的值不符合规范" << endl;
        return -1;
    }
    else if (index < (listSize / 2))
    {
        Node<T> *temp;
        temp = firstNode;
        for (int i = 0; i < index; i++)
            temp = temp->next;
        return temp->data;
    }
    else
    {
        Node<T> *temp;
        temp = lastNode;
        for (int i = listSize - 1; i > index; i--)
            temp = temp->prev;
        return temp->data;
    }
}

template <typename T>
T DoublyLinkedList<T>::remove(int index)
{
    if (index < 0 || index >= listSize)
    {
        cout << "remove函数错误,错误原因:index的值不符合规范" << endl;
        return -1;
    }
    else if (index == 0)
    {
        Node<T> *temp;
        Node<T> *removed;
        temp = firstNode->next;
        removed = firstNode;
        temp->prev = NULL;
        firstNode->next = NULL;
        firstNode = temp;
        listSize--;
        T _data = removed->data;
        delete removed;
        removed = NULL;
        return _data;
    }

    else if (index == listSize - 1)
    {

        Node<T> *temp;
        Node<T> *removed;
        temp = lastNode->prev;
        removed = lastNode;
        temp->next = NULL;
        lastNode->prev = NULL;
        lastNode = temp;
        listSize--;
        T _data = removed->data;
        delete removed;
        removed = NULL;
        return _data;
    }

    else if (index < (listSize / 2))
    {
        Node<T> *temp;
        temp = firstNode;
        for (int i = 0; i < index - 1; i++)
            temp = temp->next;
        Node<T> *removed;
        removed = temp->next;
        temp->next = removed->next;
        removed->next->prev = temp;
        listSize--;
        T _data = removed->data;
        delete removed;
        removed = NULL;
        return _data;
    }
    else
    {
        Node<T> *temp;
        temp = lastNode;
        for (int i = listSize - 1; i > index + 1; i--)
            temp = temp->prev;
        Node<T> *removed;
        removed = temp->prev;
        temp->prev = removed->prev;
        removed->prev->next = temp;
        listSize--;
        T _data = removed->data;
        delete removed;
        removed = NULL;
        return _data;
    }
}

template <typename T>
T DoublyLinkedList<T>::set(int index, T theData)
{
    if (index < 0 || index >= listSize)
    {
        cout << "set函数错误,错误原因:index的值不符合规范" << endl;
        return -1;
    }
    else if (index < (listSize / 2))
    {
        Node<T> *temp;
        temp = firstNode;
        for (int i = 0; i < index; i++)
            temp = temp->next;
        T _data = temp->data;
        temp->data = theData;
        return _data;
    }
    else
    {
        Node<T> *temp;
        temp = lastNode;
        for (int i = listSize - 1; i > index; i--)
            temp = temp->prev;
        T _data = temp->data;
        temp->data = theData;
        return _data;
    }
}

//定义输出函数
template <class T>
void DoublyLinkedList<T>::output(ostream &out) const
{
    for (Node<T> *currentNode = firstNode;
         currentNode != NULL;
         currentNode = currentNode->next)
        out << currentNode->data << "  ";
}

//重载运算符
template <class T>
ostream &operator<<(ostream &out, const DoublyLinkedList<T> &x)
{
    x.output(out);
    return out;
}

int main()
{
    DoublyLinkedList<int> l;
    for (int i = 0; i < 5; i++)
    {
        l.insert(i, 2 * i + 1); //验证insert
    }
    cout << l << endl;
    cout << l.getSize() << endl; //验证getSizze()
    l.insert(0, 10);
    l.insert(2, 15);
    cout << l << endl;
    cout << l.get(5) << endl; //验证get
    l.remove(0);
    l.remove(1);
    cout << l << endl; //验证remove
    l.set(3, 66);      //验证set
    cout << l << endl;
    cout << l.isEmpty() << endl; //验证isEmpty
    l.clear(); //验证clear
    cout << l.isEmpty() << endl;
}