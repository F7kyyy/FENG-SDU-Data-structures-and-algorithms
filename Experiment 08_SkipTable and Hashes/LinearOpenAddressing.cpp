#include <iostream>
using namespace std;

template <class K>
class Hash;
template <>
class Hash<int>
{
public:
    size_t operator()(const int theKey) const
    {
        return size_t(theKey);
    }
};

template <class K, class E>
class hashTable
{
public:
    hashTable(int theDivisor = 11);
    ~hashTable() { delete[] table; }
    bool empty() const { return dSize == 0; }
    void find(const K &) const;
    void insert(const pair<const K, E> &);
    void erase(const pair<const K, E> &);

protected:
    int search(const K &) const;
    pair<const K, E> **table; //散列表
    Hash<K> hash;             //把类型K映射到一个非整数
    int dSize;                //字典中数对个数
    int divisor;              //散列函数除数
};

template <class K, class E>
hashTable<K, E>::hashTable(int theDivisor)
{
    divisor = theDivisor;
    dSize = 0;

    table = new pair<const K, E> *[divisor];
    for (int i = 0; i < divisor; i++)
        table[i] = NULL;
}

template <class K, class E>
int hashTable<K, E>::search(const K &theKey) const
{
    int i = (int)hash(theKey) % divisor; //找到theKey对应散列表的位置
    int j = i;
    do
    {
        if (table[j] == NULL || table[j]->first == theKey) //为空或者是找到theKey，返回位置
            return j;
        j = (j + 1) % divisor;
    } while (j != i); //遍历一圈停止
    return j;         // 表满
}

template <class K, class E>
void hashTable<K, E>::find(const K &theKey) const
{
    int b = search(theKey);

    if (table[b] == NULL || table[b]->first != theKey)
        cout << -1 << endl;
    else
        cout << b << endl;
}

template <class K, class E>
void hashTable<K, E>::insert(const pair<const K, E> &thePair)
{
    int b = search(thePair.first);

    if (table[b] == NULL)
    {
        table[b] = new pair<const K, E>(thePair);
        dSize++;
        cout << b << endl;
    }
    else
    {
        //if (table[b]->first == thePair.first)
            cout << "Existed" << endl;
    }
}

template <class K, class E>
void hashTable<K, E>::erase(const pair<const K, E> &thePair)
{
    int b = search(thePair.first); //找到thePair的位置
    int count = 0;
    if (table[b] == NULL || table[b]->first != thePair.first)
        cout << "Not Found" << endl; //找不到时输出Not Found
    else
    {
        table[b] = NULL; //删除输入元素
        int i = b, j = b;
        int x;
        do
        {
            i = (i + 1) % divisor; //向后寻找桶
            if (table[i] == NULL)  //如果下一个桶是空的，那么不需要再移动元素，跳出循环
                break;
            x = table[i]->first % divisor;                                  //元素应该在的位置
            if ((x <= j && j < i) || (i < x && x <= j) || (i < x && j < i)) //三种情况
            {
                table[j] = table[i];                                        //table[i]放入前边的空格
                table[i] = NULL;                                            //发生循环的两种情况
                j = i;                                               
                count++;
            }
        } while (table[(i + 1) % divisor] != NULL && i != b);
        cout << count << endl;
    }
}

int main()
{
    int n, dvisor, numble;
    cin >> dvisor >> n;
    hashTable<int, int> h(dvisor);
    for (int i = 0; i < n; i++)
    {
        pair<int, int> x;
        cin >> numble;
        switch (numble)
        {
        case 0:
            cin >> x.first;
            x.second = x.first;
            h.insert(x);
            break;
        case 1:
            cin >> x.first;
            h.find(x.first);
            break;
        case 2:
            cin >> x.first;
            x.second = x.first;
            h.erase(x);
            break;
        }
    }
    return 0;
} 