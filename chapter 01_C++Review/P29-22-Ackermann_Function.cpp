#include <iostream>
#include <cmath>
using namespace std;

int Ackermann(int i, int j)
{
    if (i == 1 && j >= 1)
        return pow(2, j); //递归基础部分
    else if (i >= 2 && j == 1)
        return Ackermann(i - 1, 2);                   //
    else                                              //递归部分
        return Ackermann(i - 1, Ackermann(i, j - 1)); //
}

int main()
{
    int i, j;
    cout << "please input i and j: ";
    cin >> i >> j;
    cout << "the result of Ackermann's Function is "
         << Ackermann(i, j) << endl;
}   