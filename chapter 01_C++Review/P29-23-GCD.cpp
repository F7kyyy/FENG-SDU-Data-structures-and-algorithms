#include <iostream>
using namespace std;

int gcd(int x, int y)
{
    if (y == 0)
        return x;
    else
        return gcd(y, x % y);
}

int main()
{
    cout << "please input x and y: ";
    int x, y;
    cin >> x >> y;
    cout << "the result is : " << gcd(x, y);
}