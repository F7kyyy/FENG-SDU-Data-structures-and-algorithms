#include <iostream>
using namespace std;
const int maxsize = 9999999;
struct array
{
    int row, col, value;
    array &operator=(array &x)
    {
        row = x.row;
        col = x.col;
        value = x.value;
        return *this;
    }
};

class sparseMatrix
{
public:
    sparseMatrix(int &m, int &n);
    ~sparseMatrix() { delete[] element; }
    sparseMatrix &operator=(sparseMatrix &a);
    void again(int &m, int &n);
    void copy1(sparseMatrix &a);
    void input(int &m);
    int multiply(sparseMatrix &a);
    int add(sparseMatrix &a);
    void output();
    void tranpose();

private:
    int Rows, Cols, Terms; //行数，列数，非零元素的个数
    array *element;        //存非零元素的三元数组
    int maxSize;           //数组容量
};

sparseMatrix::sparseMatrix(int &m, int &n)
{
    element = new array[maxsize];
    Rows = m;
    Cols = n;
    Terms = 0;
}

void sparseMatrix::again(int &m, int &n)
{
    Rows = m;
    Cols = n;
}

void sparseMatrix::copy1(sparseMatrix &a)
{
    Cols = a.Cols;
    Rows = a.Rows;
    Terms = a.Terms;
    for (int i = 0; i < Terms; i++)
    {
        element[i].value = a.element[i].value;
        element[i].col = a.element[i].col;
        element[i].row = a.element[i].row;
    }
}

void sparseMatrix::input(int &m)
{
    if (m == 1)
    {
        int a;
        Terms = 0;
        for (int i = 0; i < Rows; i++)
        {
            for (int j = 0; j < Cols; j++)
            {
                cin >> a;
                if (a != 0)
                {
                    element[Terms].value = a;
                    element[Terms].row = i + 1;
                    element[Terms].col = j + 1;
                    Terms++;
                }
            }
        }
    }
    else
    {
        int a, lie, hang, val;
        cin >> a;
        for (int i = 0; i < a; i++)
        {
            cin >> hang >> lie >> val;
            element[Terms].value = val;
            element[Terms].row = hang;
            element[Terms].col = lie;
            Terms++;
        }
    }
}

int sparseMatrix::multiply(sparseMatrix &a)
{
    if (Cols != a.Rows)
    {
        copy1(a);
        return -1;
    }
    if (Terms * a.Terms == 0)
    {
        if (a.Terms == 0)
            copy1(a);
        return 0;
    }
    else
    {
        sparseMatrix b(Rows, a.Cols);
        int rowSize[10000]; //rowSize为a中每一行非零元素的个数
        int rowNext[10000]; //rowNext为a中每一行首个非零元素在element中的位置(索引)
        int answer[10000];  //存放结果矩阵中每行的结果
        for (int i = 1; i <= a.Rows; i++)
            rowSize[i] = 0;
        for (int i = 0; i < a.Terms; i++)
        {
            if (a.element[i].value != 0)
            {
                rowSize[a.element[i].row]++; //每行的非零元素个数
            }
        }
        rowNext[1] = 0;
        for (int i = 2; i <= a.Terms; i++) //每行第一个非零元素的位置
            rowNext[i] = rowNext[i - 1] + rowSize[i - 1];
        int p = 0;
        for (int i = 1; i <= Rows && p < Terms; i++) //核心
        {
            for (int j = 1; j <= a.Cols; j++)
                answer[j] = 0; //结果存储数组的初始化
            while (p < Terms && element[p].row == i)
            {
                int t = element[p].col; //第p个非零元素的列数
                if (rowSize[t] != 0)    //a的第t行非零元素个数不为0
                {
                    for (int q = rowNext[t]; q < rowNext[t] + rowSize[t]; q++)
                    {
                        answer[a.element[q].col] += element[p].value * a.element[q].value;
                    }
                }
                p++;
            }
            for (int k = 1; k <= a.Cols; k++)
            {
                if (answer[k] != 0)
                {
                    b.element[b.Terms].value = answer[k];
                    b.element[b.Terms].row = i;
                    b.element[b.Terms].col = k;
                    b.Terms++;
                }
            }
        }
        copy1(b);
        return 0;
    }
}

int sparseMatrix::add(sparseMatrix &a) //加法
{
    if (Cols != a.Cols || Rows != a.Rows)
    {
        copy1(a);
        return -1;
    }
    else
    {
        sparseMatrix b(Rows, Cols);
        int it = 0, ia = 0;
        while (it != Terms && ia != a.Terms)
        {
            int tIndex = element[it].row * Cols + element[it].col;     //确定位置
            int aIndex = a.element[ia].row * Cols + a.element[ia].col; //确定a的位置
            if (tIndex < aIndex)                                       //若a项在后，则将*this的属性赋值到b
            {
                b.element[b.Terms].col = element[it].col;
                b.element[b.Terms].row = element[it].row;
                b.element[b.Terms].value = element[it].value;
                it++;
                b.Terms++;
            }
            else
            {
                if (tIndex == aIndex) //若a和*this的位置一样，则将*this的属性赋值到b
                {
                    if (element[it].value + a.element[ia].value != 0)
                    {
                        b.element[b.Terms].row = element[it].row;
                        b.element[b.Terms].col = element[it].col;
                        b.element[b.Terms].value = element[it].value + a.element[ia].value;
                        b.Terms++;
                    }
                    it++;
                    ia++;
                }
                else //若不是以上两种情况，则将a的属性赋值到b
                {
                    b.element[b.Terms].col = a.element[ia].col;
                    b.element[b.Terms].row = a.element[ia].row;
                    b.element[b.Terms].value = a.element[ia].value;
                    ia++;
                    b.Terms++;
                }
            }
        }
        //复制剩余项
        for (; it != Terms; it++)
        {
            b.element[b.Terms].value = element[it].value;
            b.element[b.Terms].row = element[it].row;
            b.element[b.Terms].col = element[it].col;
            b.Terms++;
        }
        for (; ia != a.Terms; ia++)
        {
            b.element[b.Terms].value = a.element[ia].value;
            b.element[b.Terms].row = a.element[ia].row;
            b.element[b.Terms].col = a.element[ia].col;
            b.Terms++;
        }
        copy1(b);
        return 0;
    }
}

void sparseMatrix::output()
{
    int i, j, k = 0;
    cout << Rows << " " << Cols << endl;
    for (i = 0; i < Rows; i++)
    {
        for (j = 0; j < Cols; j++)
        {
            if (k < Terms && element[k].row == i + 1 && element[k].col == j + 1)
            {
                cout << element[k].value << " ";
                k++;
            }
            else
            {
                cout << "0"
                     << " ";
            }
        }
        cout << endl;
    }
}

void sparseMatrix::tranpose() //转置
{
    sparseMatrix b(Cols, Rows); //设置矩阵的特征
    b.Terms = Terms;
    b.Cols = Rows;
    b.Rows = Cols;

    int *colSize = new int[Cols + 1];
    int *rowNext = new int[Cols + 1];

    for (int i = 1; i <= Cols; i++)
        colSize[i] = 0;
    for (int i = 0; i < Terms; i++) //寻找*this中每一列非零元素的数目
        colSize[element[i].col]++;

    rowNext[1] = 0;
    for (int i = 2; i <= Cols; i++) //寻找*this中每一行的起始点
        rowNext[i] = rowNext[i - 1] + colSize[i - 1];
    for (int i = 0; i < Terms; i++) //实施从*this到b的转置
    {
        int j = rowNext[element[i].col]++; //b中的位置
        b.element[j].row = element[i].col;
        b.element[j].col = element[i].row;
        b.element[j].value = element[i].value;
    }
    copy1(b);
}

int main()
{
    int m = 0, n = 0, l, w, k;
    sparseMatrix x(m, n);
    cin >> l;
    for (int i = 0; i < l; i++)
    {
        cin >> w;
        if (w == 1)
        {
            cin >> m >> n;
            x.again(m, n);
            x.input(w);
        }
        else if (w == 2)
        {
            cin >> m >> n;
            sparseMatrix a(m, n);
            a.input(w);
            k = x.multiply(a);
            if (k == -1)
                cout << k << endl;
        }
        else if (w == 3)
        {
            cin >> m >> n;
            sparseMatrix a(m, n);
            a.input(w);
            k = x.add(a);
            if (k == -1)
                cout << k << endl;
        }
        else if (w == 4)
            x.output();
        else if (w == 5)
            x.tranpose();
    }

}