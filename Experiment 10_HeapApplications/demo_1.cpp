#include <iostream>
#include <iterator>
using namespace std;

template <class T>
void changeLength1D(T *&a, int oldLength, int newLength)
{
    T *temp = new T[newLength];             // new array
    int number = min(oldLength, newLength); // number to copy
    copy(a, a + number, temp);
    delete[] a; // deallocate old memory
    a = temp;
}

template <class T>
class minHeap
{
public:
    minHeap(int initialCapacity = 10);
    ~minHeap() { delete[] heap; }
    bool empty() const { return heapSize == 0; }
    int size() const
    {
        return heapSize;
    }
    const T &top()
    { // return min element
        return heap[1];
    }
    void pop();
    void push(const T &);
    void initialize(T *, int);
    void deactivateArray()
    {
        heap = NULL;
        arrayLength = heapSize = 0;
    }
    void output(ostream &out) const;

private:
    int heapSize;    // number of elements in queue
    int arrayLength; // queue capacity + 1
    T *heap;         // element array
};

template <class T>
minHeap<T>::minHeap(int initialCapacity)
{
    arrayLength = initialCapacity + 1;
    heap = new T[arrayLength];
    heapSize = 0;
}

template <class T>
void minHeap<T>::push(const T &theElement)
{ //将theElement添加到堆中
    //必要时增加数组长度
    if (heapSize == arrayLength - 1)
    { //加倍数组长度
        changeLength1D(heap, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    // 找到theElement的地方
    // currentNode从新叶子开始并向上移动树
    int currentNode = ++heapSize;
    while (currentNode != 1 && heap[currentNode / 2] > theElement)
    {
        // 无法将元素放入堆[currentNode]
        heap[currentNode] = heap[currentNode / 2]; // 下移元素
        currentNode /= 2;                          // 移交给父母
    }

    heap[currentNode] = theElement;
}

template <class T>
void minHeap<T>::pop()
{ // 删除最小元素.

    // if (heapSize == 0) // 空堆
    //     cout << -1 << endl;

    // Delete min element
    heap[1].~T();

    // 删除最后一个元素并重新定义
    T lastElement = heap[heapSize--];

    // 查找从根开始的lastElement的位置
    int currentNode = 1,
        child = 2; //currentNode的子节点
    while (child <= heapSize)
    {
        // heap[child]应该是currentNode的较小子节点
        if (child < heapSize && heap[child] > heap[child + 1])
            child++;

        // 是否可以将lastElement放入heap [currentNode]
        if (lastElement <= heap[child])
            break;
        heap[currentNode] = heap[child]; //使孩子上移
        currentNode = child;             //向下移动
        child *= 2;
    }
    heap[currentNode] = lastElement;
}

template <class T>
void minHeap<T>::initialize(T *theHeap, int theSize)
{
    delete[] heap;
    heap = theHeap;
    heapSize = theSize;
    // 堆化
    for (int root = heapSize / 2; root >= 1; root--)
    {
        T rootElement = heap[root];
        // 找到放置rootElement的地方
        int child = 2 * root;
        while (child <= heapSize)
        {
            if (child < heapSize && heap[child] > heap[child + 1])
                child++;
            if (rootElement <= heap[child])
                break;

            heap[child / 2] = heap[child];
            child *= 2;
        }
        heap[child / 2] = rootElement;
    }
}

template <class T>
void minHeap<T>::output(ostream &out) const
{ //输出流
    copy(heap + 1, heap + heapSize + 1, ostream_iterator<T>(cout, " "));
}

//重载 <<
template <class T>
ostream &operator<<(ostream &out, const minHeap<T> &x)
{
    x.output(out);
    return out;
}

int main()
{
    int n;
    cin >> n;
    minHeap<int> mheap;
    int array[10000];
    for (int i = 1; i <= n; i++)
    {
        cin >> array[i];
        // mheap.push(array[i]);
    }
    mheap.initialize(array, n);
    cout << mheap.top() << endl;

    int numble, option, theElement; //执行numble次操作，每次选择option操作，插入theElement
    cin >> numble;

    for (int i = 0; i < numble; i++)
    {
        cin >> option;
        if (option == 1)
        {
            cin >> theElement;
            mheap.push(theElement);
            cout << mheap.top() << endl;
        }
        else if (option == 2)
        {
            mheap.pop();
            cout << mheap.top() << endl;
        }
        else if (option == 3)
        {
            int nn;
            minHeap<int> nheap; //option=3,排序操作
            cin >> nn;
            int array2[10000];
            for (int i = 1; i <= nn; i++)
            {
                cin >> array2[i];
                nheap.push(array2[i]);
            }
            for (int i = 1; i <= nn; i++)
            {
                cout << nheap.top() << " ";
                nheap.pop();
            }
            // nheap.initialize(array2, nn);
            // for (int i = nn - 1; i >= 1; i--)
            // {
            //     int x = nheap.top();
            //     nheap.pop();
            //     array2[i + 1] = x;
            // }

            // for (int i = nn; i >= 1; i--)
            // {
            //     cout << array2[i] << " ";
            // }
        }
    }
}