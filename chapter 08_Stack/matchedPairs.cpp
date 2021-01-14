#include <iostream>
#include <string>
#include <sstream>
#include "myExceptions.h"
using namespace std;

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
class Stack
{
public:
    Stack(int initialCapacity = 10);
    ~Stack() { delete[] stack; }
    bool empty() const { return stackTop == -1; }
    int size() const
    {
        return stackTop + 1;
    }
    T &top()
    {
        return stack[stackTop];
    }
    void pop()
    {
        if (stackTop == -1)
            throw stackEmpty();
        stack[stackTop--].~T(); // destructor for T
    }
    void push(const T &theElement);
    void input();
    void printMatchedPairs();

private:
    int stackTop;    // current top of stack
    int arrayLength; // stack capacity
    T *stack;        // element array
};

template <class T>
Stack<T>::Stack(int initialCapacity)
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
void Stack<T>::push(const T &theElement)
{ // Add theElement to stack.
    if (stackTop == arrayLength - 1)
    { // no space, double capacity
        changeLength1D(stack, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    // add at stack top
    stack[++stackTop] = theElement;
}

template <class T>
void Stack<T>::printMatchedPairs()
{
    Stack<T> c;
    int a[100], b[100], k = 0, n = 0, d[100],  m = -1;
    int length = size();
    for (int i = 0; i < length; i++)
    {
        if (stack[i] == '(' || (stack[i] == '[' && c.top() != '('))
        { //‘(’内嵌‘[’不符合要求
            c.push(stack[i]);
    
        }
        else if (stack[i] == ')' && c.top() == '(')
        {
            a[k] = c.stackTop; //存储左'('的位置
            b[k] = i; //存储右‘）’的位置
            k++;        
            c.pop(); //删除，令c.top()为存储的下一个左括弧
        }
        else if (stack[i] == ']' && c.top() == '[')
        {
            a[k] = c.stackTop;
            b[k] = i;
            k++;
            c.pop();
        }
        else if ((stack[i] == ']' && c.top() == '(') || (stack[i] == ')'
         && c.top() == '[') || (stack[i] == '[' && c.top() == '('))
        {
            n = 1;
            break;
        }
    }
    while (!c.empty())
    {
        n = 1;
        c.pop();
    }
    if (n == 0)
    {
        for (int i = 0; i < k; i++)
        {
            cout << "(" << a[i] << "," << b[i] << ")" << endl;
        }
    }
    else
    {
        cout << "错误" << endl;
    }
}

template <class T>
void Stack<T>::input()
{
    T x;
    for (int i = 0; i < arrayLength; i++)
    {
        cin >> x;
        stack[++stackTop] = x;
    }
}

int main()
{
    Stack<char> x(10);
    x.input();
    x.printMatchedPairs();
}