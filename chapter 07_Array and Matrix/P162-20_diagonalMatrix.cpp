
#include <iostream>
#include "myExceptions.h"
using namespace std;

template <class T>
class diagonalMatrix
{
public:
    diagonalMatrix(int theN = 10);
    ~diagonalMatrix() { delete[] element; }
    T get(int, int) const;
    void set(int, int, const T &);
    diagonalMatrix<T> &operator+(const diagonalMatrix<T> &x);
    diagonalMatrix<T> operator-(const diagonalMatrix<T> &x);
    diagonalMatrix<T> operator*(const diagonalMatrix<T> &x);
    void transpose();
    void input();
    void output();

private:
    int n;      //矩阵尺寸
    T *element; //一维数组用于对角线元素
};

template <class T>
diagonalMatrix<T>::diagonalMatrix(int theN)
{ // 构造函数
    // 验证 theN
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");
    n = theN;
    element = new T[n];
}

template <class T>
T diagonalMatrix<T>::get(int i, int j) const
{ // 返回矩阵的第（i，j）个元素.
    // 验证 i and j
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();

    if (i == j)
        return element[i - 1]; // 对角线元素
    else
        return 0; // 非对角元素
}

template <class T>
void diagonalMatrix<T>::set(int i, int j, const T &newValue)
{ // 将newValue存储为第（i，j）个元素
    // 验证i和j
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();

    if (i == j)
        // save the diagonal value
        element[i - 1] = newValue;
    else
        // 非对角线值，newValue必须为零
        if (newValue != 0)
        throw illegalParameterValue("nondiagonal elements must be zero");
}

template <class T>
diagonalMatrix<T> &diagonalMatrix<T>::operator+(const diagonalMatrix<T> &x)
{
    if (x.n != n)
    {
        throw illegalParameterValue("two diagonalMatrix'n is different");
    }
    for (int i = 0; i < n; i++)
        this->element[i] += x.element[i];
    return *this;
}

template <class T>
diagonalMatrix<T> diagonalMatrix<T>::operator-(const diagonalMatrix<T> &x)
{
    if (x.n != n)
    {
        throw illegalParameterValue("two diagonalMatrix'n is different");
    }

    diagonalMatrix<T> w(x.n);
    for (int i = 0; i < n; i++)
        w.element[i] = element[i] - x.element[i];
    return w;
}
template <class T>
diagonalMatrix<T> diagonalMatrix<T>::operator*(const diagonalMatrix<T> &x)
{
    if (x.n != n)
    {
        throw illegalParameterValue("two diagonalMatrix'n is different");
    }

    diagonalMatrix<T> w(x.n);
    for (int i = 0; i < n; i++)
        w.element[i] = element[i] * x.element[i];
    return w;
}

template <class T>
void diagonalMatrix<T>::transpose()
{
    return;
}

template <class T>
void diagonalMatrix<T>::input()
{
    cout << "please input n" << endl;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> element[i];
    }
}
template <class T>
void diagonalMatrix<T>::output()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                cout << element[i] << " ";
            else
                cout << 0 << " ";
        }
        cout << endl;
    }
}

template <class T>
istream &operator>>(istream &in, diagonalMatrix<T> &x)
{
    x.input();
    return in;
}

template <class T>
ostream &operator<<(ostream &out, diagonalMatrix<T> &x)
{
    x.output();
    return out;
}

int main()
{
    diagonalMatrix<int> x, y;
    cin >> x >> y;
    x.transpose();
    cout << "x.transpose()" << endl
         << x << endl;
    diagonalMatrix<int> z;
    z = x + y;
    cout << "x+y:" << endl
         << z << endl;
    z = x - y;
    cout << "x-y:" << endl
         << z << endl;
    z = x * y;
    cout << "x*y:" << endl
         << z << endl;
    return 0;
}