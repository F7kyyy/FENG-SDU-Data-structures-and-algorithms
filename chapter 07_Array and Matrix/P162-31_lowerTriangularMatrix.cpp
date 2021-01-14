#include <iostream>
#include "myExceptions.h"
using namespace std;

template <class T>
void output(T theElement[100], int n)
{   
    int i = 0, j = 0, l = 0;
    T p[100][100];
    for (i; i < n; i++)
    {    
        for (j; j <= i; j++)
        {
            p[i][j] = theElement[i * (i + 1) / 2 + j];
        }
        for (l = j + 1; l < n; l++)
        {
            p[i][l] = 0;
        }
        j = 0;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << p[i][j] << " ";
        }
        cout << endl;
    }
}
template <class T>
class lowerTriangularMatrix
{
public:
    lowerTriangularMatrix(int theN = 10);
    ~lowerTriangularMatrix() { delete[] element; }
    void input();
    void Mutiply(lowerTriangularMatrix<T> &x1, lowerTriangularMatrix<T> &x2);
private:
    int n;      // matrix dimension
    T *element; // 1D array for lower triangle
};

template <class T>
lowerTriangularMatrix<T>::lowerTriangularMatrix(int theN)
{ // Constructor.
    // validate theN
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");

    n = theN;
    element = new T[n * (n + 1) / 2];
}

template <class T>
void lowerTriangularMatrix<T>::input()
{
    cin >> n;
    for (int i = 0; i < n * (n + 1) / 2; i++)
        cin >> element[i];
}
template <class T>
istream &operator>>(istream &in, lowerTriangularMatrix<T> &x)
{
    x.input();
    return in;
}

template <class T>
void lowerTriangularMatrix<T>::Mutiply(lowerTriangularMatrix<T> &x1, lowerTriangularMatrix<T> &x2)
{
    cout << "x : " << endl;
    output(x1.element, x1.n);
    cout << "y : " << endl;
    output(x2.element, x2.n);
    cout << "x*y : " << endl;
    lowerTriangularMatrix<T> w(x1.n);
    int i, j, k = 0, l = 0, sum = 0;
    for (i = 0; i < x1.n; i++)			//从 0 到 n 按行扫描
    {
        for (j = 0; j <= i; j++)	//从 0 到 i 按列扫描
        {
            for (k = j; k <= i; k++)//从 j 到 i 将矩阵 a 与矩阵 b 相乘
            {
                sum += x1.element[i * (i + 1) / 2 + k] * x2.element[k * (k + 1) / 2 + j];
                w.element[l] = sum;
            }
            sum = 0;
            l++;
        }
    }
    output(w.element, x1.n); 
}
int main()
{
    lowerTriangularMatrix<int> x, y, z;
    cin >> x >> y;
    z.Mutiply(x, y);
}