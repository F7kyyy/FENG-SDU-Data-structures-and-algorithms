#include <iostream>
using namespace std;

template <class T>
void subset(T *a, int n)
{
    if (n == 0)
    {
        for (int i = 0; i < 5; i++)
            cout << a[i];
        cout << endl;
    }
    else
    {
        a[n - 1] = 0;
        subset(a, n - 1);
        a[n - 1] = 1;
        subset(a, n - 1);
    }
}
    
int main()
{
    int a[5];
    for (int i = 0; i < 5; i++)
    {
        a[i] = i;
    }
    subset(a, 5);
    return 0;
}
