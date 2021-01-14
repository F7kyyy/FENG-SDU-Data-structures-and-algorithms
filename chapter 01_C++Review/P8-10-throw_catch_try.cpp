#include <iostream>
using namespace std;

int abc(int a, int b, int c)
{
    if (a < 0 && b < 0 && c < 0)
        throw 1;
    else if (a == 0 && b == 0 && c == 0)
        throw 2;
    else
        return a + b * c;
}

void test()
{   int a, b, c;
    cout << "请输入a,b,c: ";
    cin >> a >> b >> c;
    try
    {
        cout << abc(a, b, c) << endl;
    }
    catch (int const k)
    {
        cout << "The parameters to abc were " << a << "," << b << ","
             << "and" << c << endl;
        cout << "An exception has been thrown" << endl;
        cout << k << endl;
    }
}

int main()
{
    test();
    
} 