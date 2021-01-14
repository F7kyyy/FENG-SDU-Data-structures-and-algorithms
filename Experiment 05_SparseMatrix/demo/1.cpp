#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

class MatrixTerms
{
public:
	int row;
	int col;
	int value;
public:
	MatrixTerms(int _row = 0, int _col = 0, int _value = -1) :row(_row), col(_col), value(_value) {}
	MatrixTerms& operator=(const MatrixTerms& m)
	{
		this->col = m.col;
		this->row = m.row;
		this->value = m.value;
		return *this;
	}
	friend ostream& operator<<(ostream& out, MatrixTerms& m)
	{
		out << m.row << "  " << m.col << "  " << m.value << endl;
		return out;
	}
};
class sparseMatrix
{
public:
	int rows;//总行数
	int cols;//总列数
	MatrixTerms* terms;
	int size;
public:
	sparseMatrix(int len = 1)
	{
		rows = 0;
		cols = 0;
		this->terms = new MatrixTerms[len];
		size = 0;
	}

	void getValue_cin()
	{
		delete[]this->terms;
		cin >> this->rows >> this->cols;
		cin >> this->size;
		this->terms = new MatrixTerms[this->size];
		MatrixTerms m;
		for (int i = 0; i < this->size; ++i)
		{
			cin >> m.row >> m.col >> m.value;
			this->terms[i] = m;
		}
	}
	sparseMatrix& operator=(const sparseMatrix& m)
	{
		delete[]this->terms;
		this->rows = m.rows;
		this->cols = m.cols;
		this->size = m.size;
		int len = m.size;
		this->terms = new MatrixTerms[len];
		for (int i = 0; i < len; ++i)
		{
			this->terms[i] = m.terms[i];
		}
		return *this;
	}
	void transpose(sparseMatrix& b);
	friend ostream& operator<<(ostream& out, sparseMatrix& m)
	{
		out << m.rows << "  " << m.cols << endl;
		int count = 0;
		for (int i = 1; i <= m.rows; ++i)
		{
			for (int j = 1; j <= m.cols; ++j)
			{
				if (count < m.size && m.terms[count].row == i && m.terms[count].col == j)
					out << m.terms[count++].value << "  ";
				else
					out << "0  ";
			}
			out << endl;
		}
		return out;
	}
	void resize(int newlen)
	{
		MatrixTerms* p = new MatrixTerms[newlen];
		int minsize = (this->size > newlen ? newlen : this->size);
		for (int i = 0; i < minsize; ++i)
		{
			p[i] = this->terms[i];
		}
		delete[]this->terms;
		this->terms = p;
		this->size = newlen;
	}
	friend istream& operator>>(istream& in, sparseMatrix& m)
	{
		delete[]m.terms;
		in >> m.rows >> m.cols;
		MatrixTerms t;
		m.terms = new MatrixTerms[m.rows * m.cols];
		int count = 0;
		for (int i = 1; i <= m.rows; ++i)
		{
			for (int j = 1; j <= m.cols; ++j)
			{
				in >> t.value;
				if (t.value != 0)
				{
					t.row = i;
					t.col = j;
					m.terms[count++] = t;
				}
			}
		}
		m.size = count;
		m.resize(count);
		return in;
	}
	~sparseMatrix()
	{
		delete[]this->terms;
	}
	void add(sparseMatrix& b2);
	void multi(sparseMatrix& b);
};

void sparseMatrix::multi(sparseMatrix& b)
{
	if (this->cols != b.rows)
	{
		(*this) = b;
		cout << "-1" << endl;
		return;
	}
	sparseMatrix m;
	b.transpose(m);
	int count1 = 0;//计算*this分了几组
	int count2 = 0;//计算b分了几组
	int* r1 = new int[this->rows + 2];
	int* r2 = new int[m.cols + 2];
	for (int i = 0; i < this->rows + 2; ++i)
		r1[i] = -1;//初始化
	for (int i = 0; i < m.cols + 2; ++i)
		r2[i] = -1;//初始化
	r1[0] = 0;
	r2[0] = 0;
	for (int i = 0; i < this->size - 1; ++i)
	{
		if (this->terms[i].row != this->terms[i + 1].row)
		{
			r1[++count1] = i + 1;
		}
	}
	r1[++count1] = this->size;
	for (int i = 0; i < m.size - 1; ++i)
	{
		if (m.terms[i].row != m.terms[i + 1].row)
		{
			r2[++count2] = i + 1;
		}
	}
	r2[++count2] = m.size;
	sparseMatrix r(count1 * count2);//保存结果
	int count = 0; //计算结果中有多少非零元素
	int k1 = 0;//做this的游标
	int k2 = 0;//做m的游标
	for (int i = 0; i < count1; ++i)
	{
		for (int j = 0; j < count2; ++j)
		{
			k1 = r1[i];//给定第i行第一个非零元素的起始位置
			int k1_end = r1[i + 1];
			k2 = r2[j];//给定原矩阵第j列第一个非零元素的起始位置
			int k2_end = r2[j + 1];
			int sum = 0;
			while (k1 != k1_end && k2 != k2_end)
			{
				if (this->terms[k1].col == m.terms[k2].col)
				{
					sum += this->terms[k1++].value * m.terms[k2++].value;
				}
				else
					this->terms[k1].col > m.terms[k2].col ? k2++ : k1++;
			}
			if (sum != 0)
			{
				MatrixTerms t(this->terms[r1[i]].row, m.terms[r2[j]].row, sum);
				r.terms[count++] = t;
			}
		}
	}
	r.rows = this->rows;
	r.cols = m.rows;
	r.size = count;
	(*this) = r;
	(*this).resize(count);
}

void sparseMatrix::add(sparseMatrix& b)
{
	if (rows != b.rows || cols != b.cols)
	{
		(*this) = b;
		cout << "-1" << endl;
		return;
	}
	sparseMatrix s(this->size + b.size + 1);
	s.rows = this->rows;
	s.cols = this->cols;
	int count = 0;
	int k1 = 0;
	int k2 = 0;
	int k1_end = this->size;
	int k2_end = b.size;
	while (k1 != k1_end && k2 != k2_end)
	{
		int tindex = this->terms[k1].row * cols + this->terms[k1].col;
		int bindex = b.terms[k2].row * cols + b.terms[k2].col;
		if (tindex < bindex)
		{
			s.terms[count++] = this->terms[k1++];
		}
		else if (tindex == bindex)
		{
			int sum = this->terms[k1].value + b.terms[k2].value;
			if (sum != 0)
			{
				MatrixTerms m(this->terms[k1].row, this->terms[k1].col, sum);
				s.terms[count++] = m;
			}
			++k1;
			++k2;
		}
		else
		{
			s.terms[count++] = b.terms[k2++];
		}
	}
	for (; k1 < k1_end; ++k1)
		s.terms[count++] = this->terms[k1];
	for (; k2 < k2_end; ++k2)
		s.terms[count++] = b.terms[k2];
	s.size = count;
	(*this) = s;
	this->resize(count);
}


void sparseMatrix::transpose(sparseMatrix& b)
{
	delete[]b.terms;
	b.cols = this->rows;
	b.rows = this->cols;
	b.terms = new MatrixTerms[this->size];
	b.size = this->size;
	int* colSize = new int[this->cols + 1];
	int* rowNext = new int[this->cols + 1];
	for (int i = 1; i <= this->cols; ++i)
		colSize[i] = 0;
	for (int i = 0; i < this->size; ++i)
		colSize[this->terms[i].col]++;

	rowNext[1] = 0;
	for (int i = 2; i <= this->cols; ++i)
	{
		rowNext[i] = rowNext[i - 1] + colSize[i - 1];
	}

	MatrixTerms mTerm;
	for (int i = 0; i < this->size; ++i)
	{
		int j = rowNext[this->terms[i].col]++;
		mTerm.row = this->terms[i].col;
		mTerm.col = this->terms[i].row;
		mTerm.value = this->terms[i].value;
		b.terms[j] = mTerm;
	}
	(*this) = b;
}

void operator_print(sparseMatrix& m)
{
	int count;
	cin >> count;
	int code;//第几种方法
	sparseMatrix temp;
	while (count != 0)
	{
		count--;
		cin >> code;
		if (code == 1)
		{
			cin >> m;
		}
		else if (code == 2)
		{
			temp.getValue_cin();
			m.multi(temp);
		}
		else if (code == 3)
		{
			temp.getValue_cin();
			m.add(temp);
		}
		else if (code == 4)
		{
			cout << m;
		}
		else
		{
			m.transpose(temp);
		}
	}
}

int main()
{
	//freopen("test.txt", "w", stdout);#pragma warning(disable:4996)
	sparseMatrix m;
	operator_print(m);
	return 0;
}


