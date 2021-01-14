#include <iostream>
using namespace std;

template <class T>
bool search(T a[], T length, T x)         //遍历法
{
    if (length < 0)
        return false;
    if (a[length] == x)
        return true;
    else
        return search(a, length - 1, x);
}
void test01()
{
    int a[] = {1, 2, 3, 5, 6};
    int x;
    cin >> x;
    if (search(a, 4, x) == 1)
        cout << "Found!" << endl;
    else
        cout << "Not Fund!" << endl;
}
int main()
{
    test01();
    return 0;
}