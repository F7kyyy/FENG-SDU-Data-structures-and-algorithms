#include <iostream>
using namespace std;

template <class T>
void Swap(T &a, T &b)                          //定义交换函数
{
    int temp = b;
    b = a;
    a = temp;
}

template <class T>
void Premutations(T *list, int k, int m, int &result)    //递归部分
{
    if (k == m)
    {
        int value = 0;
        for (int i = 1; i <= m; i++)
        {
            value += i ^ list[i];              //计算排列的价值
        }
        result = result | value;               //价值的或
    }
    else
        for (int i = k; i <= m; i++)
        {
            Swap(list[k], list[i]);
            Premutations(list, k + 1, m, result);    //递归核心部分
            Swap(list[k], list[i]);
        }
}

int main()
{

    int length;
    cin >> length;
    int array[length];
    int result = 0;
    for (int i = 1; i <= length; i++)
    {
        cin >> array[i];
    }
    Premutations(array, 1, length, result);
    cout << result << endl;
    return 0;
}
