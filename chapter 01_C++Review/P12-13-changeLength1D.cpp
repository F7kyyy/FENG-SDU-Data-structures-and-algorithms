#include <iostream>
using namespace std;

template <class T>
void changeLength1D(T *array, int a, int b)
{
    T *newarray = new int(b);   //new新数组
    int c = (a < b) ? a : b;    //比较oldLength与newLength大小
    for (int i = 0; i < c; i++) //赋值给新数组
        newarray[i] = array[i];
    delete[] array; //释放空间
    cout << "The new array is :" << endl;
    for (int i = 0; i < c; i++) //输出新数组
        cout << newarray[i] << " ";
}

int main()
{
    int oldLength;
    cout << "Please enter the old length :" << endl;
    cin >> oldLength;
    int *array = new int[oldLength]; //new oldLength的数组
    cout << "Please enter an array element ：" << endl;
    for (int i = 0; i < oldLength; i++) //输入数组长度
    {
        int n;
        cin >> n;
        array[i] = n;
    }
    int newLength;
    cout << "Please enter a new length:" << endl;
    cin >> newLength;
    changeLength1D(array, oldLength, newLength);
    return 0;
}
