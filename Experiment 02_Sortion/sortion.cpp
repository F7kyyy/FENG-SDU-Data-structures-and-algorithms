#include <iostream>
using namespace std;

template <class T> //定义模板类
class sortion
{
public:
    sortion(T m_length) //构造函数
    {
        this->length = m_length;
        this->array = new T[this->length]; //开辟动态数组
        for (int i = 0; i < length; i++)
        {
            cin >> array[i]; //在动态数组中储存数据
        }
    }

    void SelectionSort() //及时终止的选择排序
    {
        bool sorted = false;                                   //sorted标记，当不在发生交换时，停止外层循环
        for (int size = length; !sorted && (size > 1); size--) //不发生交换停止，循环停止
        {
            int indexofMax = 0;
            sorted = true;
            for (int i = 1; i < size; i++) //内层循环将前size-1个数中，
            {                              //最大的数放在array[size-1]中
                if (array[indexofMax] <= array[i])
                    indexofMax = i;
                else
                    sorted = false; //恢复sorted为false
            }
            swap(array[indexofMax], array[size - 1]);
        }

        for (int i = 0; i < length; i++)
        {
            cout << array[i] << " ";
        }
    }
    void insertionsort() //插入排序
    {
        for (int i = 1; i < length; i++) //从第2个元素开始执行循环
        {
            T t = array[i]; //假设前i个元素之前的元素都已被排序
            int j;
            for (j = i - 1; j >= 0 && t < array[j]; j--) //从后向前扫描，元素后移
                array[j + 1] = array[j];
            array[j + 1] = t; //直到找到第一个小于该元素的数，在其后插入该元素
        }

        for (int i = 0; i < length; i++)
        {
            cout << array[i] << " ";
        }
    }

    bool bubble(T *arr, int len)
    {
        bool swapped = false; //标记是否进行交换，作为排序是否停止的标记

        for (int i = 0; i < len - 1; i++) //比较第i个和第i+1个和大小，并交换元素，
            if (arr[i] > arr[i + 1])      //使最大的元素在最右侧

            {
                swap(arr[i], arr[i + 1]);
                swapped = true; //发生交换
            }

        return swapped;
    }

    void bubbleSort() //及时终止的冒泡排序
    {
        for (int i = length; i > 1 && bubble(array, i); i--) //对前i-1个数据进行两两比较，
            ;                                                //不发生交换则排序完成

        for (int i = 0; i < length; i++)
        {
            cout << array[i] << " ";
        }
    }

    void rearrange() //名次排序
    {
        T *u = new T[length];
        T *r = new T[length];
        for (int i = 0; i < length; i++)
            r[i] = 0;
        for (int i = 0; i < length; i++)
            for (int j = 0; j < i; j++) //85-94为计算名次
                if (array[j] <= array[i])
                    r[i]++;
                else
                    r[j]++;
        for (int i = 0; i < length; i++) //将array中元素放在u[]中，位置为它对应的名次
            u[r[i]] = array[i];
        for (int i = 1; i < length; i++) //再将u[i]值赋给array[i]
            array[i] = u[i]; 
        for (int i = 0; i < length; i++)
            cout << array[i] << " ";
        delete[] u;
        delete[] r;
    }

    ~sortion() //析构函数
    {
        length = 0;
        delete[] array; //删除动态数组
    }

private:
    int length;
    T *array;
};

int main()
{
    int m_length;
    cin >> m_length;
    sortion<int> a(m_length);

    //a.bubbleSort();
    a.insertionsort();
    //a.SelectionSort();
    // a.rearrange();
}