#include <iostream>
using namespace std;

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
    void input();
    void output();

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
    int number; //扑克牌数目
    T theElement;
    cin >> number;
    for (int i = 0; i < number; i++) //为扑克牌从1到n赋值
    {
        push(i + 1);
    }
}

template <class T>
void arrayQueue<T>::output()
{
    for (int i = (theFront + 1) % arrayLength; i < (theFront + 1) % arrayLength + size(); i++)
    {
        cout << queue[i] << " ";
    }
    cout << endl;
}

int main()
{
    arrayQueue<int> x;
    x.input();
    while (x.size() > 2)
    {
        x.pop();           //扔掉最上面一张
        x.push(x.front()); //将下一张放在牌堆最后
        x.pop();           //删除放在排堆最后的牌
    }
    x.pop(); //最后扔掉剩余两张牌的上边那一张
    x.output();
}