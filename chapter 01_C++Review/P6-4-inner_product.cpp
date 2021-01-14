#include <iostream>
using namespace std;

template <class T>
int inner_product(T &a, T &b)
{
    int a_size = sizeof(a) / sizeof(*a); //判断数组元素个数
    int sum = 0;                         //定义sum,储存结果
    for (int i = 0; i < a_size; i++)
    {
        sum += a[i] * b[i];
    }
    return sum;
}

int main()
{
    int array1[] = {1, 2, 3, 4};
    int array2[] = {2, 3, 4, 5};
    cout << "The result of multiplying two arrays is " << inner_product(array1, array2) << endl;
}