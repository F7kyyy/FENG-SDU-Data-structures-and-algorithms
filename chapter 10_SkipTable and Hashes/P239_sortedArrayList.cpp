#include <iostream>
using namespace std;

template <class K, class E>
class dictionary
{
public:
    virtual ~dictionary() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual void erase(const K &) = 0;
};

template <class K, class E>
class sortedArrayList : public dictionary<K, E>
{
public:
    sortedArrayList()
    {
        theArray = new pair<K, E>[100];
        dSize = 0;
    }
    ~sortedArrayList();

    bool empty() const { return dSize == 0; }
    int size() const { return dSize; }
    pair<K, E> *find(const K &);
    void erase(const K &);
    void insert(const pair<const K, E> &);
    void output(ostream &out) const;

protected:
    pair<K, E> *theArray;
    int dSize;
};

template <class K, class E>
sortedArrayList<K, E>::~sortedArrayList()
{
    delete[] theArray;
}

template <class K, class E>
pair<K, E> *sortedArrayList<K, E>::find(const K &theKey)
{
    for (int i = 0; i < dSize; i++)
    {
        if (theArray[i].first == theKey)
            return &theArray[i];
    }
    return NULL;
}

template <class K, class E>
void sortedArrayList<K, E>::insert(const pair<const K, E> &thePair)
{
    if (thePair.first < theArray[0].first || dSize == 0)
    {
        copy_backward(theArray + 0, theArray + dSize, theArray + dSize + 1);
        theArray[0] = thePair;
        dSize++;
        return;
    }
    for (int i = 0; i < dSize; i++)
    {
        if (thePair.first <= theArray[i].first)
        {
            copy_backward(theArray + i, theArray + dSize, theArray + dSize + 1);
            theArray[i] = thePair;
            dSize++;
            return;
        }
    }
    copy_backward(theArray + dSize, theArray + dSize, theArray + dSize + 1);
    theArray[dSize] = thePair;
    dSize++;
    return;
}

template <class K, class E>
void sortedArrayList<K, E>::erase(const K &theKey)
{
    for (int i = 0; i < dSize; i++)
    {
        if (theArray[i].first == theKey)
        {
            copy(theArray + i + 1, theArray + dSize, theArray + i);
            theArray[--dSize].~pair();
        }
    }
}

template<class K, class E>
void sortedArrayList<K, E>::output(ostream& out) const
{
    for (int i = 0; i < dSize; i++) {
        out << theArray[i].first << " " << theArray[i].second << "    ";
    }
    out << endl;
}

template <class K, class E>
ostream& operator<<(ostream& out, const sortedArrayList<K, E>& x)
{
    x.output(out); return out;
}

int main()
{
    sortedArrayList<int, int> z;
    pair<int, int> p;

    p.first = 2; p.second = 10;
    z.insert(p);
    p.first = 10; p.second = 50;
    z.insert(p);
    p.first = 6; p.second = 30;
    z.insert(p);
    p.first = 8; p.second = 40;
    z.insert(p);
    p.first = 1; p.second = 5;
    z.insert(p);
    p.first = 12; p.second = 60;
    z.insert(p);
    cout << "数组为 " << z << endl;
    cout << "数组大小 " << z.size() << endl;

    cout << "Element associated with 1 is " << z.find(1)->second << endl;
    cout << "Element associated with 6 is " << z.find(6)->second << endl;
    cout << "Element associated with 12 is " << z.find(12)->second << endl;

    z.erase(1);
    z.erase(2);
    z.erase(6);
    z.erase(12);
    cout << "删除 1, 2, 6, 12" << endl;
    cout << "数组为 " << z << endl;
    cout << "数组大小 " << z.size() << endl;
}
