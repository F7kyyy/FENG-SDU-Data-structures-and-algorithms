#include <iostream>
using namespace std;

template <class T>
void subset(T *array, int *mark, int n, int i) //array为集合元素，mark为01数组，n为起点，i为元素个数
{
    if (n == i)
    {
        cout << "{";
        int flag = 0;                       //To judge whether it is necessary to add ",", when flag is equal to 1,
        for (int k = 0; k < i; k++)         // output the first element, without adding "," 
        {
            if (mark[k] == 1)
            {
                flag++;
                if (flag == 1)
                    cout << array[k];
                else
                    cout << "," << array[k];
            }
        }
        cout << "}";
        cout << endl;
        return;
    }
    mark[n] = 0;
    subset(array, mark, n + 1, i);
    mark[n] = 1;
    subset(array, mark, n + 1, i);
}

int main()
{
    char array[5] = {'A', 'B', 'C', 'D', 'E'};
    int mark[5];
    subset(array, mark, 0, 5);
}
