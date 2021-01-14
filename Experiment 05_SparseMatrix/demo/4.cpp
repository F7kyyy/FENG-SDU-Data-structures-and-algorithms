#include <iostream>
using namespace std;

struct element {
	int row;
	int col;
	int value;
	element(int _row = 0, int _col = 0, int _value = 0) :row(_row), col(_col), value(_value) {}
};
class sparseMatrix {
public:
	sparseMatrix() {
		rows = 0;
		cols = 0;
		num = 0;
		terms = new element[300000];
	}
	sparseMatrix(const sparseMatrix& q) {
		rows = q.rows;
		cols = q.cols;
		num = q.num;
		terms = new element[300000];
		copy(q.terms, q.terms + num, terms);
	}
	~sparseMatrix() {
		delete terms;
	}
	void reset();
	void resetNoZero();
	void multiply(const sparseMatrix& q);
	void add(const sparseMatrix& q);
	void show();
	void debug() {
		cout << "__________________num:" << num << endl;
	}
	void transpose();
private:
	int rows;
	int cols;
	int num; //记录非零元素个数
	element* terms;
};

void sparseMatrix::reset() {
	int n, m;
	cin >> n >> m;

	rows = n;
	cols = m;
	num = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int input;
			cin >> input;
			if (input != 0) {
				terms[num++] = element(i, j, input);
			}
		}
	}
}
void sparseMatrix::resetNoZero() {
	cin >> rows >> cols;
	cin >> num;
	for (int i = 0; i < num; i++) {
		int x, y, v;
		cin >> x >> y >> v;
		terms[i].row = x - 1;
		terms[i].col = y - 1;
		terms[i].value = v;
	}
}
void sparseMatrix::show() {
	//牺牲空间来换取时间, 先把稀疏矩阵转化为二维矩阵
	//再输出, 总时间复杂度是O(rows*cols)
	//如果再写一个get函数来获取值, 
	//即使用每行首元素下标记录来优化
	//最坏情况也可能达到O(rows*cols*rows)


	cout << rows << " " << cols << endl;
	//还原为二维数组
	int** tempMatrix = new int* [rows];
	for (int i = 0; i < rows; i++) {
		tempMatrix[i] = new int[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			tempMatrix[i][j] = 0;
		}
	}
	for (int i = 0; i < num; i++) {
		int r = terms[i].row;
		int c = terms[i].col;
		tempMatrix[r][c] = terms[i].value;
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << tempMatrix[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < rows; i++) {
		delete[] tempMatrix[i];
	}
	delete[] tempMatrix;

}

void sparseMatrix::add(const sparseMatrix& q) {
	//若不合法, 则将q赋给(*this), 同时输出 - 1
	if (q.cols != cols || q.rows != rows) {
		cout << -1 << endl;
		num = q.num;
		rows = q.rows;
		cols = q.cols;
		copy(q.terms, q.terms + q.num, terms);
		return;
	}

	sparseMatrix result;
	result.num = 0;

	element* p1 = terms;
	element* p2 = q.terms;

	//利用行主序的特性, 进行非零元素的加法
	while (p1 != terms + num && p2 != q.terms + q.num) {
		int index1 = p1->row * cols + p1->col;
		int index2 = p2->row * cols + p2->col;

		if (index1 < index2) {
			result.terms[result.num++] = *p1;
			p1++;
		}
		else if (index1 > index2) {
			result.terms[result.num++] = *p2;
			p2++;
		}
		else if (index2 == index1) {
			result.terms[result.num++] = element(p1->row, p1->col, p1->value + p2->value);
			p1++;
			p2++;
		}
	}

	for (; p1 != terms + num; p1++) {
		result.terms[result.num++] = *p1;
	}
	for (; p2 != q.terms + q.num; p2++) {
		result.terms[result.num++] = *p2;
	}

	this->num = result.num;
	copy(result.terms, result.terms + result.num, terms);
}
void sparseMatrix::multiply(const sparseMatrix& q) {
	//这里的乘法过程中虽然出现了二维矩阵
	//但这是用类似散列的方法, 牺牲空间来换取时间
	//核心乘法计算过程并未违背稀疏矩阵想要的原则
	//本方法的总时间复杂度保持在O(rows*q.cols)


	//若不合法, 则将q赋给(*this), 同时输出 - 1
	if (q.rows != cols) {
		cout << -1 << endl;
		num = q.num;
		rows = q.rows;
		cols = q.cols;
		copy(q.terms, q.terms + q.num, terms);
		return;
	}

	sparseMatrix result;
	result.num = 0;
	result.rows = rows;
	result.cols = q.cols;



	//qRowsNum用来储存q矩阵中每行的非零元素个数
	int qRowsNum[700] = { 0 };
	//int* qRowsNum = new int[q.rows]{ 0 };

	int currentRow = 0;
	for (int i = 0; i < q.num; i++) {
		if (currentRow != q.terms[i].row) {
			currentRow = q.terms[i].row;
		}
		qRowsNum[currentRow]++;
	}

	//临时矩阵, 用于类似散列的方式保存临时值
	int tempMatrix[700][700] = {0};

	//核心
	//这里时间复杂度为O(rows*q.cols)
	//直接检查非0元素并通过它创建或修改最终矩阵的非0元素
	for (element* p1 = terms; p1 != terms + num; p1++) {
		for (element* p2 = q.terms; p2 != q.terms + q.num; p2++) {
			if (p1->col == p2->row) {
				tempMatrix[p1->row][p2->col] += p1->value * p2->value;//经过多次此步, 就可以做到"左行乘右列"的效果
			}
			else {
				p2 += qRowsNum[p2->row]-1;
			}
		}
	}

	//遍历二维数组, 把结果存为三元表起来
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			if (tempMatrix[i][j] != 0) {
				result.terms[result.num++] = element(i, j, tempMatrix[i][j]);
			}
		}
	}

	num = result.num;
	rows = result.rows;
	cols = result.cols;
	copy(result.terms, result.terms + result.num, terms);
}
void sparseMatrix::transpose() {
	//因为add()中利用了行主序,
	//所以这里进行转置不能只是单纯地改变横纵坐标
	//需要同时保持行主序状态

	//还原为二维数组
	int** tempmatrix = new int* [rows];
	for (int i = 0; i < rows; i++) {
		tempmatrix[i] = new int[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			tempmatrix[i][j] = 0;
		}
	}
	for (int i = 0; i < num; i++) {
		int r = terms[i].row;
		int c = terms[i].col;
		tempmatrix[r][c] = terms[i].value;
	}

	//重新用三元表读入, 保持行主序
	num = 0;
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			if (tempmatrix[j][i] != 0)
				terms[num++] = element(i, j, tempmatrix[j][i]);
		}
	}
	//交换稀疏矩阵的行和列
	int temp = rows;
	rows = cols;
	cols = temp;
	//释放临时表
	for (int i = 0; i < cols; i++) {
		delete[] tempmatrix[i];
	}
	delete[] tempmatrix;

}
int main() {
	sparseMatrix test;
	sparseMatrix test2;
	int cnt;
	cin >> cnt;
	while (cnt--) {
		//test.debug();
		//cout << "********************" << endl;
		int input;
		cin >> input;
		if (input == 1) {
			test.reset();
		}
		else if (input == 2) {
			test2.resetNoZero();
			test.multiply(test2);
		}
		else if (input == 3) {
			test2.resetNoZero();
			test.add(test2);
		}
		else if (input == 4) {
			test.show();
		}
		else if (input == 5) {
			test.transpose();
		}
	}

	return 0;
}