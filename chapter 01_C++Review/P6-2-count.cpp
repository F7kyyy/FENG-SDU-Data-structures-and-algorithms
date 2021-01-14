#include <iostream>
using namespace std;

template <class T>
int count(const T *arry_begin, const T *arry_end) //Pointer as formal parameter
{
    int num = 0;
    while (arry_begin != arry_end)
    {
        num++;
        arry_begin++; //Point to the next element 
    }
    return num;
}

int main()
{
    int arry[] = {1, 2, 3, 4, 5, 6};
    int number = count(begin(arry), end(arry)); //begin(array)指向第一个元素，end(array)指向最后一个元素之后的一个元素
    cout << "Count: " << number << endl;
    return 0;
}