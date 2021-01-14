#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct Address
{
    string name;      //用户的名字
    string telephone; //用户的电话
    int clas = 0;     //用户的班级
    int dorm = 0;     //宿舍
};

template <class T>
class AddressList
{
public:
    AddressList(int initialCapacity = 10);                    //构造函数
    ~AddressList() { delete[] element; }                      //析构函数
    void changeLength1D(T *&a, int oldLength, int newLength); //倍增
    void push_back(const Address &theElement);                //尾插
    void erase(string theName);                               //依据名字删除
    void checkName(string theName);                           //查找某个用户的名字是否存在
    void changeInformation(string theName);                   //修改某一条信息
    void output(int theClas);                                 //计算异或和

private:
    Address *element;
    int listSize;    //存储数据的多少
    int arrayLength; //线性表的空间大小
};
template <class T>
AddressList<T>::AddressList(int initialCapacity)
{
    arrayLength = initialCapacity;
    element = new Address[arrayLength];
    listSize = 0;
}

template <class T>
void AddressList<T>::changeLength1D(T *&a, int oldLength, int newLength)
{
    T *temp = new T[newLength];
    int number = min(oldLength, newLength);
    copy(a, a + number, temp);
    delete[] a;
    a = temp;
}

template <class T>
void AddressList<T>::push_back(const Address &theElement)
{
    if (listSize == arrayLength) //倍增
    {
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }
    element[listSize].name = theElement.name;
    element[listSize].dorm = theElement.dorm;
    element[listSize].telephone = theElement.telephone;
    element[listSize].clas = theElement.clas;
    listSize++;
}

template <class T>
void AddressList<T>::erase(string theName)
{

    for (int i = 0; i < listSize; i++)
    {
        if (theName == element[i].name)
        {
            copy(element + i + 1, element + listSize, element + i);
        }
    }
    listSize--; //容量减一
}

template <class T>
void AddressList<T>::checkName(string theName)
{
    int flag = 0;
    for (int i = 0; i < listSize; i++)
    {
        if (theName == element[i].name)
        {
            flag = 1;
            break;
        }
    }
    cout << flag << endl;
}

template <class T>
void AddressList<T>::changeInformation(string theName)
{
    for (int i = 0; i < listSize; i++)
    {
        if (theName == element[i].name)
        {
            int number;
            string m_telephone;
            int m_clas;
            int m_dorm;
            cin >> number; //选择修改的信息类型
            switch (number)
            {
            case 1:
                cin >> m_telephone;
                element[i].telephone = m_telephone;
                break;
            case 2:
                cin >> m_clas;
                element[i].clas = m_clas;
                break;
            case 3:
                cin >> m_dorm;
                element[i].dorm = m_dorm;
                break;
            }
        }
    }
}

template <class T>
void AddressList<T>::output(int theClas)
{
    int result = 0;
    for (int i = 0; i < listSize; i++)
    {
        if (element[i].clas == theClas)
            result = result ^ element[i].dorm;
    }
    cout << result << endl;
}

int main()
{
    AddressList<Address> v;
    Address person;
    string Name;
    int Clas;
    int n = 0;
    cin >> n;
    int selection;
    for (int i = 0; i < n; i++)
    {
        cin >> selection;
        switch (selection)
        {
        case 0:
            cin >> person.name >> person.telephone >> person.clas >> person.dorm;
            v.push_back(person);
            break;
        case 1:
            cin >> Name;
            v.erase(Name);
            break;
        case 2:
            cin >> Name;
            v.changeInformation(Name);
            break;
        case 3:
            cin >> Name;
            v.checkName(Name);
            break;
        case 4:
            cin >> Clas;
            v.output(Clas);
            break;
        }
    }
}