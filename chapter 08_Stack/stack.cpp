#include <iostream>
#include <sstream>
#include "myExceptions.h"
using namespace std;

// template <class T>
// class extendedStack
// {
// public:
//     virtual ~extendedStack() {}
//     virtual bool empty() const = 0;             // return true iff stack is empty
//     virtual int size() const = 0;               // return number of elements in stack
//     virtual T &top() = 0;                       // return reference to the top element
//     virtual void pop() = 0;                     // remove the top element
//     virtual void push(const T &theElement) = 0; // insert theElement at the top of the stack
//     virtual void input() = 0;                   //input stack
//     virtual void output() = 0;                  //output stack;
//     virtual void combine() = 0;                 //combine stack
//     virtual void separate() = 0;                //separate stack
// };

template <class T>
class extendedArrayStack// : public extendedStack<T>
{
public:
    extendedArrayStack(int initialCapacity = 10);
    ~extendedArrayStack() { delete[] stack; }
    bool empty() const { return stackTop == -1; }
    int size() const { return stackTop + 1; }
    T &top()
    {
        if (stackTop == -1)
            throw stackEmpty();
        return stack[stackTop];
    }
    void pop()
    {
        if (stackTop == -1)
            throw stackEmpty();
        stack[stackTop--].~T();
    }
    void push(const T &theElement);
    void input();
    void output();
    void combine(extendedArrayStack<T> &x);
    void separate(extendedArrayStack<T> &y);

private:
    int stackTop;
    int arrayLength;
    T *stack;
};
template <class T>
extendedArrayStack<T>::extendedArrayStack(int initialCapacity)
{ // Constructor.
    if (initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    stack = new T[arrayLength];
    stackTop = -1;
}

template <class T>
void changeLength1D(T *&a, int oldLength, int newLength)
{
    if (newLength < 0)
        throw illegalParameterValue("new length must be >= 0");

    T *temp = new T[newLength];             // new array
    int number = min(oldLength, newLength); // number to copy
    copy(a, a + number, temp);
    delete[] a; // deallocate old memory
    a = temp;
}

template <class T>
void extendedArrayStack<T>::push(const T &theElement)
{
    if (stackTop == arrayLength - 1)
    {
        changeLength1D(stack, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }
    stack[++stackTop] = theElement;
}

template <class T>
void extendedArrayStack<T>::input()
{
    T x;
    for (int i = 0; i < arrayLength; i++)
    {
        cin >> x;
        stack[++stackTop] = x;
    }
}

template <class T>
void extendedArrayStack<T>::output()
{
    int k = stackTop;
    while (k != -1)
    {
        cout << stack[k--] << " ";
    }
    cout << endl;
}

template <class T>
void extendedArrayStack<T>::separate(extendedArrayStack<T> &y)
{
    extendedArrayStack<T> x;
    int n = stackTop / 2;
    while (stackTop > n)
    {
        x.push(top());
        pop();
    }
    while (!x.empty())
    {
        y.push(x.top());
        x.pop();
    }
}

template <class T>
void extendedArrayStack<T>::combine(extendedArrayStack<T> &x)
{
    extendedArrayStack y;
    while (!x.empty())
    {
        y.push(x.top());
        x.pop();
    }
    while (!y.empty())
    {
        push(y.top());
        y.pop();
    }
}

int main()
{
    extendedArrayStack<int> m(8),n;
    m.input();
    m.separate(n);
    n.output();
    m.output();
    m.combine(n);
    m.output();
}
