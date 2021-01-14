#include <iostream>
using namespace std;

struct matrixTerm
{
    int row,
        col;
    int value;
    operator int() const { return value; }
    //type conversion from matrixTerm to int
};

class sparseMatrix
{
    friend ostream &operator<<(ostream &out, sparseMatrix &x);

public:
    sparseMatrix(int maxsize = 1000000);
    ~sparseMatrix() { delete[] element; }
    void input(int &m);
    void output();
    void Multiply(const sparseMatrix &x);
    void Add(const sparseMatrix &x);
    void Copy(const sparseMatrix &x);
    void assignment(matrixTerm &x, matrixTerm &y);
    void transpose();

private:
    int Rows, Cols, Terms; //行数，列数，非零元素的个数
    matrixTerm *element;   //存非零元素的三元数组
    int maxSize;           //数组容量
};

sparseMatrix::sparseMatrix(int maxsize)
{
    maxSize = maxsize;
    element = new matrixTerm[maxSize];
    Rows = Cols = Terms = 0;
}

void sparseMatrix::input(int &m)
{
    //重置矩阵
    Rows = 0;
    Cols = 0;
    Terms = 0;
    delete[] element;
    cin >> Rows >> Cols;
    //element = new matrixTerm[Rows*Cols];
    //会在最后几个显示run time error
    element = new matrixTerm[maxSize];

    //输入完整矩阵，将非零元素存储在一维数组
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
    //只输入非零元素
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
ostream &operator<<(ostream &out, sparseMatrix &x)
{
    x.output();
    return out;
}

void sparseMatrix::Copy(const sparseMatrix &x)
{
    Cols = x.Cols;
    Rows = x.Rows;
    Terms = x.Terms;
    // delete[] element;
    // element = x.element;
    //直接赋值会出错
    for (int i = 0; i < Terms; i++)
    {
        element[i].value = x.element[i].value;
        element[i].col = x.element[i].col;
        element[i].row = x.element[i].row;
    }
}

void sparseMatrix::assignment(matrixTerm &x, matrixTerm &y)
{
    x.row = y.row;
    x.col = y.col;
    x.value = y.value;
}

void sparseMatrix::Add(const sparseMatrix &x)
{
    if (Rows != x.Rows || x.Cols != Cols)
    {
        Copy(x);
        cout << -1 << endl;
        return;
    }
    else
    {
        sparseMatrix res(Rows * Cols);
        res.Rows = Rows;
        res.Cols = Cols;
        int it = 0, ib = 0;

        while (it != Terms && ib != x.Terms)
        {
            int tIndex = element[it].row * Cols + element[it].col;
            int xIndex = x.element[ib].row * Cols + x.element[ib].col;
            if (tIndex < xIndex)
            {
                assignment(res.element[res.Terms], element[it]);
                it++;
                res.Terms++;
            }
            else if (tIndex == xIndex)
            {
                if ((element[it].value + x.element[ib].value) != 0)
                {
                    res.element[res.Terms].row = element[it].row;
                    res.element[res.Terms].col = element[it].col;
                    res.element[res.Terms].value = element[it].value + x.element[ib].value;
                    res.Terms++;
                }
                it++;
                ib++;
            }
            else
            {
                assignment(res.element[res.Terms], x.element[ib]);
                ib++;
                res.Terms++;
            }
        }
        // 复制剩余项
        for (; it != Terms; it++)
        {
            assignment(res.element[res.Terms], element[it]);
            res.Terms++;
        }
        for (; ib != x.Terms; ib++)
        {
            assignment(res.element[res.Terms], x.element[ib]);
            res.Terms++;
        }
        Copy(res);
    }
}

void sparseMatrix::transpose()
{
    sparseMatrix res(Rows * Cols); //声明结果矩阵
    res.Rows = Cols;
    res.Cols = Rows;
    res.Terms = Terms;

    int *colSize = new int[Cols + 1];
    int *rowNext = new int[Cols + 1];

    for (int i = 1; i <= Cols; i++)
        colSize[i] = 0;
    for (int i = 0; i < Terms; i++) //寻找原矩阵每一列非零元素的数目
        colSize[element[i].col]++;

    rowNext[1] = 0;
    for (int i = 2; i <= Cols; i++) //转置后矩阵每行首元素所在的位置
        rowNext[i] = rowNext[i - 1] + colSize[i - 1];

    for (int i = 0; i < Terms; i++) //实施从*this到res的转置
    {
        int j = rowNext[element[i].col]++; //根据原矩阵所处的列数计算转置后元素在res的位置
        res.element[j].row = element[i].col;
        res.element[j].col = element[i].row;
        res.element[j].value = element[i].value;
    }
    Copy(res);
}

void sparseMatrix::Multiply(const sparseMatrix &x)
{
    if (Cols != x.Rows)
    {
        Copy(x);
        cout << -1 << endl;
        return;
    }   
    if (Terms * x.Terms == 0)
    {
        if (x.Terms == 0)
            Copy(x);
        return;
    }
    else
    {
        sparseMatrix b(Rows * x.Cols); //声明结果矩阵
        b.Rows = Rows;
        b.Cols = x.Cols;

        int rowSize[10000]; //rowSize为x中每一行非零元素的个数
        int rowNext[10000]; //rowNext为x中每一行首个非零元素在element中的位置(索引)
        int answer[10000];  //存放结果矩阵中每行的结果

        for (int i = 1; i <= x.Rows; i++)
            rowSize[i] = 0;
        for (int i = 0; i < x.Terms; i++)
        {
            if (x.element[i].value != 0)
            {
                rowSize[x.element[i].row]++; //被乘矩阵每行的非零元素个数
            }
        }

        rowNext[1] = 0;
        for (int i = 2; i <= x.Terms; i++) //每行第一个非零元素的位置
            rowNext[i] = rowNext[i - 1] + rowSize[i - 1];

        int p = 0;
        for (int i = 1; i <= Rows && p < Terms; i++) //乘法的核心过程
        {
            for (int j = 1; j <= x.Cols; j++)
                answer[j] = 0; //结果存储数组的初始化
            while (p < Terms && element[p].row == i)
            {
                int t = element[p].col; //第p个非零元素的列数
                if (rowSize[t] != 0)    //乘数矩阵的第t行非零元素个数不为0
                {
                    for (int q = rowNext[t]; q < rowNext[t] + rowSize[t]; q++)
                    {
                        answer[x.element[q].col] += element[p].value * x.element[q].value;
                    }
                }
                p++;
            }
            
            for (int k = 1; k <= x.Cols; k++)
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
        Copy(b);
    }
}

int main()
{
    sparseMatrix x, y;
    int l, flag;//l为运算数目，flag控制稀疏矩阵的两种的输入方式
    cin >> l;
    for (int i = 0; i < l; i++)
    {
        cin >> flag;
        switch (flag)
        {
        case 1:
            x.input(flag);
            break;
        case 2:
            y.input(flag);
            x.Multiply(y);
            break;
        case 3:
            y.input(flag);
            x.Add(y);
            break;
        case 4:
            cout << x;
            break;
        case 5:
            x.transpose();
            break;
        }
    }
}
