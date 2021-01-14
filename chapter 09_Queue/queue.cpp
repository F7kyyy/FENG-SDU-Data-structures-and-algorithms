#include <iostream>
using namespace std;

template <class T>
struct chainNode
{
    T element;
    chainNode<T> *next;
    chainNode() {}
    chainNode(const T &theElement)
    {
        this->element = theElement;
    }
    chainNode(const T &theElement, chainNode<T> *next)
    {
        this->element = theElement;
        this->next = next;
    }
};

template <class T>
class queue
{
public:
    virtual ~queue() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T &front() = 0;
    virtual T &back() = 0;
    virtual void pop() = 0;
    virtual void push(const T &theElement) = 0;
    virtual void input() = 0;
    virtual void output() = 0;
    //   virtual void split() = 0;
    //   virtual void melt() = 0;
};

template <class T>
class arrayQueue : public queue<T>
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
    void input();
    void output();
    void split(arrayQueue<T> &x, arrayQueue<T> &y);
    void melt(arrayQueue<T> &x, arrayQueue<T> &y);

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
    if ((theBack + 1) % arrayLength == theFront) //长度翻倍并且复制
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

template <class T>
void arrayQueue<T>::input()
{
    int n;
    T theElement;
    cout << "输入要输入的元素个数" << endl;
    cin >> n;
    cout << "输入元素" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> theElement;
        push(theElement);
    }
}

template <class T>
void arrayQueue<T>::output()
{
    cout << "由队首至队尾输出元素" << endl;
    for (int i = (theFront + 1) % arrayLength; i < (theFront + 1) % arrayLength + size(); i++)
    {
        cout << queue[i] << " ";
    }
    cout << endl;
}

template <class T>
void arrayQueue<T>::split(arrayQueue<T> &x, arrayQueue<T> &y) //分裂
{
    while (!x.empty()) //清空x
    {
        x.pop();
    }
    while (!y.empty()) //清空y
    {
        y.pop();
    }
    int i = 3;
    while (!empty())
    {
        if (i % 2 == 1)
        {
            x.push(front());
            pop();
            i++;
        }
        if (i % 2 == 0)
        {
            y.push(front());
            pop();
            i++;
        }
    }
}

template <class T>
void arrayQueue<T>::melt(arrayQueue<T> &x, arrayQueue<T> &y) //合并
{
    int i = 3;
    while (!empty())
    {
        pop();
    }
    while (!x.empty() && !y.empty())
    {
        if (i % 2 == 1)
        {
            push(x.front());
            x.pop();
            i++;
        }
        if (i % 2 == 0)
        {
            push(y.front());
            y.pop();
            i++;
        }
    }
    if (!y.empty())
    {
        while (!y.empty())
        {
            push(y.front());
            y.pop();
        }
    }
    if (!x.empty())
    {
        while (!x.empty())
        {
            push(x.front());
            x.pop();
        }
    }
}

template <class T>
class linkedQueue : public queue<T>
{
public:
    linkedQueue(int initialCapacity = 10)
    {
        queueFront = NULL;
        queueSize = 0;
    }
    ~linkedQueue();
    bool empty() const
    {
        return queueSize == 0;
    }
    int size() const
    {
        return queueSize;
    }
    T &front()
    {
        return queueFront->element;
    }
    T &back()
    {
        return queueBack->element;
    }
    void pop();
    void push(const T &);
    void input();
    void output();
    void split(linkedQueue<T> &x, linkedQueue<T> &y);
    void melt(linkedQueue<T> &x, linkedQueue<T> &y);

private:
    chainNode<T> *queueFront;
    chainNode<T> *queueBack;
    int queueSize;
};

template <class T>
linkedQueue<T>::~linkedQueue()
{
    while (queueFront != NULL)
    {
        chainNode<T> *nextNode = queueFront->next;
        delete queueFront;
        queueFront = nextNode;
    }
}

template <class T>
void linkedQueue<T>::input()
{
    int n;
    T theElement;
    cout << "输入要输入的元素个数" << endl;
    cin >> n;
    cout << "输入元素" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> theElement;
        push(theElement);
    }
}

template <class T>
void linkedQueue<T>::output()
{
    chainNode<T> *q;
    int i = 0;
    for (q = queueFront; i == 0; q = q->next)
    {
        cout << q->element << " ";
        if (q == queueBack)
            i++;
    }
    cout << endl;
}

template <class T>
void linkedQueue<T>::pop()
{
    chainNode<T> *nextNode = queueFront->next;
    delete queueFront;
    queueFront = nextNode;
    queueSize--;
}

template <class T>
void linkedQueue<T>::push(const T &theElement)
{
    chainNode<T> *newNode = new chainNode<T>(theElement, NULL);

    if (queueSize == 0)
        queueFront = newNode;
    else
        queueBack->next = newNode;
    queueBack = newNode;

    queueSize++;
}

template <class T>
void linkedQueue<T>::melt(linkedQueue<T> &x, linkedQueue<T> &y)
{
    int i = 3;
    while (!empty())
    {
        pop();
    }
    while (!x.empty() && !y.empty())
    {
        if (i % 2 == 1)
        {
            push(x.front());
            x.pop();
            i++;
        }
        else if (i % 2 == 0)
        {
            push(y.front());
            y.pop();
            i++;
        }
    }
    if (!y.empty())
    {
        while (!y.empty())
        {
            push(y.front());
            y.pop();
        }
    }
    if (!x.empty())
    {
        while (!x.empty())
        {
            push(x.front());
            x.pop();
        }
    }
}

template <class T>
void linkedQueue<T>::split(linkedQueue<T> &x, linkedQueue<T> &y)
{
    while (!x.empty())
    {
        x.pop();
    }
    while (!y.empty())
    {
        y.pop();
    }
    int i = 3;
    while (!empty())
    {
        if (i % 2 == 1)
        {
            x.push(front());
            pop();
            i++;
        }
        if (i % 2 == 0)
        {
            y.push(front());
            pop();
            i++;
        }
    }
}

int main()
{
    arrayQueue<int> A, B, C;
    B.input();
    C.input();
    A.melt(B, C);
    A.output();
    linkedQueue<int> a, b, c;
    a.input();
    a.split(b, c);
    b.output();
    c.output();
}