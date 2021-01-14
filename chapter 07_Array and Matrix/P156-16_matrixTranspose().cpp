#include <iostream>
using namespace std;

template <class T>
class matrix
{
public:
    matrix(int theRows = 0, int theColumns = 0);
    ~matrix() { delete[] element; }
    void tranpose();
    void output();

private:
    int theRows, theColumns; // 矩阵维数
    T *element;              // 元素数组
};

template <class T>
matrix<T>::matrix(int theRows, int theColumns)
{
    this->theRows = theRows;
    this->theColumns = theColumns;
    element = new T[theRows * theColumns];
    for (int i = 0; i < theRows; i++)
    {
        for (int j = 0; j < theColumns; j++)
        {
            cin >> element[i * theColumns + j];
        }
    }
}

template <class T>
void matrix<T>::tranpose()
{
    T *p = new T[theRows * theColumns];
    for (int i = 0; i < theRows; i++)
    {
        for (int j = 0; j < theColumns; j++)
        {
            p[j*theRows+i]=element[i * theColumns + j];
        }
    }
    swap(theRows, theColumns);
    delete[] element;
    element = p;
}

template <class T>
void matrix<T>::output()
{
    for (int i = 0; i < theRows; i++)
    {
        for (int j = 0; j < theColumns; j++)
        {
            cout << element[i * theColumns + j] << " ";
        }
        cout << endl;
    }
}

template <class T>
ostream &operator<<(ostream &out, matrix<T> &x)
{
    x.output();
    return out;
}

int main()
{
    int therows, thecolumns;
    cin >> therows >> thecolumns;
    matrix<int> m(therows, thecolumns);
    m.tranpose();
    cout << m;
}