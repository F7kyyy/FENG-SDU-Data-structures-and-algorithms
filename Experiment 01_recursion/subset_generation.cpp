#include <iostream>
using namespace std;

template <class T>
void subset(T *array, int *mark, int i, int n, int &result) //array为集合元素，mark为01数组，i为起点，n为元素个数
{
    if (i == n)
    {
        int value = 0, j = 0;
        for (int k = 0; k < n; k++)
        {
            if (mark[k] == 1)                           //mark[k]=1时，array[k]在子集中存在
                value = value + (k + 1 - j) * array[k]; //计算子集价值
            else
                j++;
        }
        result = result ^ value; //进行异或和操作
        return;
    }

    mark[i] = 0;
    subset(array, mark, i + 1, n, result);
    mark[i] = 1;
    subset(array, mark, i + 1, n, result);
}

int main()
{
    int result = 0;
    int length;
    cin >> length;
    int array[length];
    for (int i = 0; i < length; i++)
    {
        cin >> array[i];
    }
    int mark[length];
    subset(array, mark, 0, length, result);
    cout << result << endl;
}
