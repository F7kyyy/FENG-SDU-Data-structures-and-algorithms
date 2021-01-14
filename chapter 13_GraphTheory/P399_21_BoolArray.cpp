#include<iostream>
using namespace std;

template<class T>
class Graph
{
    public:
        Graph(int initialCapacity=10)
        {
            arrayLength = initialCapacity;
            element =new T[arrayLength * (arrayLength + 1) / 2];
            //填入false说明没有边
            // fill(element, element + arrayLength * (arrayLength + 1) / 2, false);
            for (int i = 0; i < arrayLength * (arrayLength + 1) / 2;i++)
            {
                element[i] =0;
            }
        }
        ~Graph() { delete[] element; }
        void set(int i,int j,bool theElement);
        bool get(int i,int j);
    private:
        int arrayLength;
        T *element;
};

template<class T>
void Graph<T>::set(int i,int j,bool theElement)
{
    element[(i - 1) * i / 2 + j] = theElement;
}

template<class T>
bool Graph<T>::get(int i,int j)
{
    return element[(i - 1) * i / 2 + j];
}

int main()



{
    Graph<bool> v(5);
    v.set(2, 1, true);
    cout << v.get(2, 1) << endl;
    cout << v.get(3, 1) << endl;
}
