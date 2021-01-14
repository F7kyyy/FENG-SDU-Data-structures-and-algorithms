#include <iostream>
#include <algorithm> //copy，copy_backward函数
#include <sstream>   //ostringstream
#include <string>    //字符串
#include <exception> //异常处理
#include <iterator>  //ostream_iterator<T>输出流
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
class arrayList
{
public:
    arrayList(int initialCapacity = 10);                         //构造函数
    arrayList(const arrayList<T> &theList);                      //复制构造函数
    void changeLength1D(T *&a, int oldLength, int newLength);    //改变数组长度
    ~arrayList() { delete[] element; }                           //析构函数
    void push_back(const T &theElement);                         //尾插
    void removeRange(const T &beginIndex, const T &endIndex);    //删除
    void reverse();                                              //倒转
    void meld(const arrayList &array1, const arrayList &array2); //相加
    void output(ostream &out) const;                             //输出

private:
    T *element;
    int arrayLength;
    int listSize;
};

template <class T>
arrayList<T>::arrayList(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial capacity=" << initialCapacity << "Must be >0";
        throw illegalParameterValue(s.str()); //s.str(()返回s中储存的string 对象
    }
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
}

template <class T>
arrayList<T>::arrayList(const arrayList<T> &theList)
{
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    copy(theList.element, theList.element + listSize, element);
}
template <class T>
void arrayList<T>::changeLength1D(T *&a, int oldLength, int newLength)
{
    if (newLength < 0)
        throw illegalParameterValue("new lenght must be>=0");
    T *temp = new T[newLength];
    int number = min(oldLength, newLength);
    copy(a, a + number, temp);
    delete[] a;
    a = temp;
}

template <class T>
void arrayList<T>::push_back(const T &theElement)
{
    if (listSize == arrayLength) //倍增
    {
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    element[listSize] = theElement;
    listSize++;
}

template <class T>
void arrayList<T>::removeRange(const T &beginIndex, const T &endIndex)
{
    if (beginIndex < 0 || endIndex > listSize)
    {
        ostringstream s;
        s << "beginIndex=" << beginIndex << "must be >0"
          << "endIndex=" << endIndex << "must be <" << listSize;
        throw illegalIndex(s.str()); //s.str(()返回s中储存的string 对象
    }
    if (beginIndex >= endIndex)
        return;

    copy(element + endIndex, element + listSize, element + beginIndex);

    int newSize = listSize - endIndex + beginIndex;
    for (int i = newSize; i < listSize; i++)
        element[i].~T();

    listSize = newSize;
}
template <class T>
void arrayList<T>::reverse()
{
    T a;
    for (int i = 0; i < listSize / 2; i++) //交换了listsize/2,复杂度O(listsize/2)
    {
        a = element[i];
        element[i] = element[listSize - i - 1];
        element[listSize - i - 1] = a;
    }
}

template <class T>
void arrayList<T>::meld(const arrayList &array1, const arrayList &array2)
{
    int m_arrayLength = array1.listSize + array2.listSize - 1;
    arrayList<T> result(m_arrayLength);
    int a = array1.listSize;
    int b = array2.listSize;
    for (int i = 0; i < a || i < b; i++)
    {
        if (i < a && i < b)
        {
            result.push_back(array1.element[i]);
            result.push_back(array2.element[i]);
        }
        else if (i >= a && i < b)
        {
            result.push_back(array2.element[i]);
        }
        else if (i < a && i >= b)
        {
            result.push_back(array1.element[i]);
        }
    }
    cout << result;
}

template <class T>
void arrayList<T>::output(ostream &cout) const
{
    copy(element, element + listSize, ostream_iterator<T>(cout, " "));
}
template <class T>
ostream &operator<<(ostream &out, const arrayList<T> &x) //重载运算符
{
    x.output(out);
    return out;
}
int main()
{
    arrayList<int> v(5);
    for (int i = 0; i < 5; i++)
    {
        v.push_back(i);
    }
    cout << "test push_back:" << endl;
    cout << v << endl;
    v.reverse();
    cout << "test reverse:" << endl;
    cout << v << endl;
    cout << "test removeRange(0,4):" << endl;
    v.removeRange(1, 4);
    cout << v << endl;
    arrayList<int> v1(5);
    arrayList<int> v2(5);
    for (int i = 0; i < 5; i++)
    {
        v1.push_back(2 * i);
        v2.push_back(2 * i + 1);
    }
    v2.removeRange(1, 4);
    cout << "v1:" << endl;
    cout << v1 << endl;
    cout << "v2:" << endl;
    cout << v2 << endl;
    arrayList<int> v3;
    cout << "test meld v1+v2:" << endl;
    v3.meld(v1, v2);
}
