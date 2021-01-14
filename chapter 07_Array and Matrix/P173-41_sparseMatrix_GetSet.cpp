#include <iostream>
#include "myExceptions.h"
using namespace std;

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
    friend ostream &operator<<(ostream &out, sparseMatrix &a);
    friend istream &operator>>(istream &in, sparseMatrix &a);

public:
    sparseMatrix(int maxsize = 100);
    ~sparseMatrix() { delete[] element; }
    sparseMatrix(const sparseMatrix &a);
    sparseMatrix &operator=(sparseMatrix &a);
    void get(int theRow, int theColumn);
    void set(int theRow, int theColumn, int theValue);
    sparseMatrix Multiply(const sparseMatrix &b);

private:
    int Rows, Cols, Terms; //行数，列数，非零元素的个数
    array *element;        //存非零元素的三元数组
    int maxSize;           //数组容量
};

sparseMatrix::sparseMatrix(int maxsize)
{
    maxSize = maxsize;
    element = new array[maxsize];
    Rows = Cols = Terms = 0;
}

sparseMatrix::sparseMatrix(const sparseMatrix &a)
{
    this->Cols = a.Cols;
    this->Rows = a.Rows;
    this->maxSize = a.maxSize;
    this->Terms = a.Terms;
    this->element = new array[a.maxSize];
    for (int i = 0; i < Terms; i++)
    {
        this->element[i] = a.element[i];
    }
}
sparseMatrix &sparseMatrix::operator=(sparseMatrix &a)
{
    if (this->element != NULL)
    {
        delete[] this->element;
        this->element = NULL;
        this->Cols = 0;
        this->Rows = 0;
        this->Terms = 0;
    }
    this->Cols = a.Cols;
    this->Rows = a.Rows;
    this->maxSize = a.maxSize;
    this->Terms = a.Terms;
    this->element = new array[a.maxSize];
    for (int i = 0; i < Terms; i++)
    {
        this->element[i] = a.element[i];
    }
    return *this;
}

istream &operator>>(istream &in, sparseMatrix &a)
{
    cout << "输入行数，列数，非零元素个数：" << endl;
    cin >> a.Rows >> a.Cols >> a.Terms;
    if (a.Terms > a.maxSize)
    {
        cout << "数据溢出！" << endl;
        exit(1);
    }
    for (int i = 0; i < a.Terms; i++)
    {
        cout << "第" << i + 1 << "个:" << endl;
        cin >> a.element[i].row >> a.element[i].col >> a.element[i].value;
    }
    return in;
}

ostream &operator<<(ostream &out, sparseMatrix &a)
{
    cout << "行数：" << a.Rows << endl;
    cout << "列数：" << a.Cols << endl;
    cout << "非零元素个数" << a.Terms << endl;
    for (int i = 0; i < a.Terms; i++)
        out << i + 1 << ":(" << a.element[i].row << "," << a.element[i].col << ")=" << a.element[i].value << endl;
    return out;
}

void sparseMatrix::get(int theRow, int theColumn)
{
    int flag = 0;
    for (int i = 0; i < Terms; i++)
    {
        if (theRow == element[i].row && theColumn == element[i].col)
        {
            flag = element[i].value;
            break;
        }
    }
    cout << flag << endl;
}

void sparseMatrix::set(int theRow, int theColumn, int theValue)
{
    bool check = true;
    int i = 0;
    for (i = 0; i < Terms; i++)
    {
        if (theRow == element[i].row && theColumn == element[i].col)
        {
            element[i].value = theValue;
            check = false;
            break;
        }
    }
    if (check)
    {
        element[i].row = theRow;
        element[i].col = theColumn;
        element[i].value = theValue;
        Terms++;
    }
}
sparseMatrix sparseMatrix::Multiply(const sparseMatrix &b)
{                                       //矩阵的乘法
    sparseMatrix Result(Rows * b.Cols); //存放矩阵相乘的结果
    if (Cols != b.Rows)
    { //两个矩阵能相乘的先决条件：第一个的列数等于第二个的行数
        throw illegalParameterValue("two diagonalMatrix'n is different");
    }
    int *rowSize = new int[b.Rows];                 //b矩阵每行的非零元素个数
    int *rowStart = new int[b.Rows + 1];            //b矩阵每行第一个非零元素在b中的下标；为何加一？
    int *temp = new int[b.Cols];                    // 暂时存放Result每一行每个元素的运算结果
    int i, Current, lastInResult, RowA, ColA, ColB; //Current：a的指针； lastInResult：Result的指针
    for (i = 0; i < b.Rows; i++)                    //对roeSize数组赋值
        rowSize[i] = 0;
    for (i = 0; i < b.Terms; i++)
        rowSize[b.element[i].row]++;
    rowStart[0] = 0; //对rowStart数组赋值
    for (i = 1; i < b.Rows; i++)
        rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
    Current = 0;       //从下标0开始遍历a
    lastInResult = -1; //赋初值-1是为了计算方便，看完代码即可了解
    while (Current < Terms)
    {                                //遍历三元组a的每一个元素
        RowA = element[Current].row; //取得第一个元素的所在行
        for (i = 0; i < b.Cols; i++) //把temp数组赋初值为0；
            temp[i] = 0;
        while (Current < Terms && element[Current].row == RowA)
        {                                //对该行的所有元素进行操作
            ColA = element[Current].col; //该元素所在的列ColA就是该元素对应相乘的b中元素的行数
            for (i = rowStart[ColA]; i < rowStart[ColA + 1]; i++)
            {                            //遍历b中该行的所有元素
                ColB = b.element[i].col; //a的该元素与b中对应行第ColB列的元素相乘的结果应该被放到temp[ColB]中；
                temp[ColB] += element[Current].value * b.element[i].value;
            }
            Current++; //a中该元素的已经完成使命，指向a中下一个元素
        }
        for (i = 0; i < b.Cols; i++)
        { //把该行的运算结果存入Result里面
            if (temp[i] != 0)
            {
                lastInResult++;
                Result.element[lastInResult].row = element[Current].row;
                Result.element[lastInResult].col = i;
                Result.element[lastInResult].value = temp[i];
            }
        }
    }
    Result.Rows = Rows; //对Result的性质进行赋值操作
    Result.Cols = b.Cols;
    Result.Terms = lastInResult + 1;
    delete[] rowSize; //释放new创建的存储空间
    delete[] rowStart;
    delete[] temp;
    return Result;
}

int main()
{
    sparseMatrix x, y, z;
    cin >> x >> y;
    int x_row, x_cols,X_value;
    cin >> x_row >> x_cols;
    x.get(x_row, x_cols);
    cin >> x_row >> x_cols >> X_value;
    x.set(x_row, x_cols, X_value);
    cout << x << endl;
    //  z = x.Multiply(y);
    //  cout << z << endl;
}