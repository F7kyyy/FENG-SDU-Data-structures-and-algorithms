#include<iostream>
#include<sstream>
using namespace std;
ostringstream o;
template<class T>
//使用结构体存储每一个非零元素，以及其所在行和列 
struct matrixTerm{
	int row;
	int col;
	T value;
};
//稀疏矩阵类 
template<class T>
class sparseMatrix
{
	public:
		//构造函数 
		sparseMatrix(int row=0,int col=0){
			rows=row;
			cols=col;
			size=0;
			length=row*col;
			terms=new matrixTerm<T>[length];
		}
		//析构函数 
		~sparseMatrix(){
			delete []terms;
		}
		//返回行数的函数 
		int showrow(){
			return rows;
		}
		//返回列数的函数 
		int showcol(){
			return cols;
		}
		//重载()，使得稀疏矩阵可以二次 
		void operator ()(int row,int col){
			delete terms;
			rows=row;
			cols=col;
			size=0;
			length=row*col;
			terms=new matrixTerm<T>[length];
		}
		sparseMatrix<T>& operator =(const sparseMatrix<T>& m){
			delete []terms;
			rows=m.rows;
			cols=m.cols;
			size=m.size;
			length=m.length;
			terms=new matrixTerm<T>[length];
			copy(m.terms,m.terms+size,terms);
			return *this;
		}
		//快速排序（从小到大）
		void quickSort(int left, int right)
		{
			if(left >= right)
				return;
			int i, j, base1,base2;
			i = left, j = right;
			base1 = terms[left].row;  //取最左边的数为基准数
			base2 = terms[left].col;
			while (i < j)
			{
				while ( ((terms[j].row==base1&&terms[j].col>base2)||terms[j].row>base1)&& i < j)j--;
				while ( ((terms[j].row==base1&&terms[j].col<base2)||terms[j].row<base1)&& i < j)i++;
				if(i < j)swap(terms[i],terms[j]);
			}
			//基准数归位
			swap(terms[left],terms[i]);
			quickSort(left, i - 1);//递归左边
			quickSort(i + 1, right);//递归右边
		}
		sparseMatrix<T> operator +(sparseMatrix<T>& m){
			int x;
			if(rows!=m.rows||cols!=m.cols)throw x;
			sparseMatrix<T> w(rows,cols);
			int x1=0,x2=0;
			while(x1!=size&&x2!=m.size)
			{
				if(terms[x1].row==m.terms[x2].row&&terms[x1].col==m.terms[x2].col)
				{
					if(terms[x1].value+m.terms[x2].value!=0)
					{
						w.terms[w.size].row=terms[x1].row;
						w.terms[w.size].col=terms[x1].col;
						w.terms[w.size].value=terms[x1].value+m.terms[x2].value;
						w.size++;
					}
					if(x1!=size)x1++;
					if(x2!=m.size)x2++;
				}
				else if((terms[x1].row==m.terms[x2].row&&terms[x1].col<m.terms[x2].col)||terms[x1].row<m.terms[x2].row)
				{
					w.terms[w.size].row=terms[x1].row;
					w.terms[w.size].col=terms[x1].col;
					w.terms[w.size].value=terms[x1].value;
					w.size++;
					if(x1!=size)x1++;
				}
				else{
					w.terms[w.size].row=m.terms[x2].row;
					w.terms[w.size].col=m.terms[x2].col;
					w.terms[w.size].value=m.terms[x2].value;
					w.size++;
					if(x2!=m.size)x2++;
				}
			}
			while(x1!=size)
			{
				w.terms[w.size].row=terms[x1].row;
				w.terms[w.size].col=terms[x1].col;
				w.terms[w.size].value=terms[x1].value;
				w.size++;
				if(x1!=size)x1++;
			}
			while(x2!=m.size)
			{
				w.terms[w.size].row=m.terms[x2].row;
				w.terms[w.size].col=m.terms[x2].col;
				w.terms[w.size].value=m.terms[x2].value;
				w.size++;
				if(x2!=m.size)x2++;
			}
			return w;
		}
		sparseMatrix<T> operator *(sparseMatrix<T>& m){
			int x;
			if(cols!=m.rows)throw x;
			sparseMatrix<T> w(rows,m.cols);
			int x1=0,x2=0,sum=0;
			for(int i=1;i<=rows;i++)
			{
				int z[m.cols+1]={0},x2=0;
				while(terms[x1].row==i)
				{
					while(m.terms[x2].row<terms[x1].col&&x2<m.size-1)
					{
						if(x2!=m.size-1)x2++;
					}
					while(m.terms[x2].row==terms[x1].col)
					{
						z[m.terms[x2].col]+=terms[x1].value*m.terms[x2].value;
						x2++;
						if(x2==m.size)break;
					}
					x1++;
					if(x1==size)break;
				}
				for(int j=1;j<=m.cols;j++)
				{
					if(z[j]!=0){
						w.terms[w.size].row=i;
						w.terms[w.size].col=j;
						w.terms[w.size].value=z[j];
						w.size++;
					}
				}
			}
//			m.transpose();
//			int x1=0,x2=0,sum=0;
//			for(int i=1;i<=rows;i++)
//			{
//				x2=0;
//				for(int j=1;j<=m.rows;j++)
//				{
//					sum=0;
//					int zz=x1;
//					for(int k=1;k<=cols;k++)
//					{
//						if(terms[x1].row==i&&terms[x1].col==k)
//						{
//							if(m.terms[x2].row==j&&m.terms[x2].col==k)
//							{
//								sum+=terms[x1].value*m.terms[x2].value;
//								if(x2!=m.size-1)x2++;
//							}
//							if(x1!=size-1)x1++;
//						}
//						else if(m.terms[x2].row==j&&m.terms[x2].col==k)
//						{
//							if(x2!=m.size-1)x2++;
//						}
//					}
//					if(j!=m.cols)x1=zz;
//					if(sum!=0)
//					{
//						w.terms[w.size].row=i;
//						w.terms[w.size].col=j;
//						w.terms[w.size].value=sum;
//						w.size++;
//					}
//				}
//			}

//			for(int i=m.size-1;i>0;i--)
//			{
//				bool swapped=false;
//				for(int j=0;j<i;j++)
//				{
//					if(m.terms[j].col>m.terms[j+1].col)swap(m.terms[j],m.terms[j+1]),swapped=true;
//					else if(m.terms[j].col==m.terms[j+1].col&&m.terms[j].row>m.terms[j+1].row)swap(m.terms[j],m.terms[j+1]),swapped=true;
//				}
//				if(swapped==false)break;
//			}
//			int x1=0,x2=0,sum=0;
//			for(int i=1;i<=rows;i++)
//			{
//				x2=0;
//				for(int j=1;j<=m.cols;j++)
//				{
//					sum=0;
//					int zz=x1;
//					for(int k=1;k<=cols;k++)
//					{
//						if(terms[x1].row==i&&terms[x1].col==k)
//						{
//							if(m.terms[x2].row==k&&m.terms[x2].col==j)
//							{
//								sum+=terms[x1].value*m.terms[x2].value;
//								if(x2!=m.size-1)x2++;
//							}
//							if(x1!=size-1)x1++;
//						}
//						else if(m.terms[x2].row==k&&m.terms[x2].col==j)
//						{
//							if(x2!=m.size-1)x2++;
//						}
//					}
//					if(j!=m.cols)x1=zz;
//					if(sum!=0)
//					{
//						w.terms[w.size].row=i;
//						w.terms[w.size].col=j;
//						w.terms[w.size].value=sum;
//						w.size++;
//					}
//				}
//			}
			return w;
		}
		void transpose()
		{
			sparseMatrix<T> w(cols,rows);
			w.size=size; 
			if(size>0)
			{
				int num[cols]={0},pos[cols]={0};
				for(int i=0;i<size;i++)num[terms[i].col]++;
				pos[1]=0;
				for(int i=2;i<=cols;i++)pos[i]=pos[i-1]+num[i-1];
				for(int i=0;i<size;i++)
				{
					int j=terms[i].col;
					int q=pos[j];
					w.terms[q].row=terms[i].col;
					w.terms[q].col=terms[i].row;
					w.terms[q].value=terms[i].value;
					pos[j]++;
				}
			} 
			*this=w;
		} 
		void reset()
		{
			int x;
			for(int i=0;i<rows;i++)
			{
				for(int j=0;j<cols;j++){
					cin>>x;
					if(x!=0)
					{
						terms[size].row=i+1;
						terms[size].col=j+1;
						terms[size].value=x;
						size++;
						if(size==length){
							length=2*length;
							matrixTerm<T> *newterms=new matrixTerm<T>[length];
							copy(terms,terms+size,newterms);
							delete []terms;
							terms=newterms;
						}
					}
				}
			}
		}
		void input()
		{
			int t;
			cin>>t;
			size=t;
			for(int i=0;i<size;i++)
			{
				int x,y,z;
				cin>>x>>y>>z;
				terms[i].row=x;
				terms[i].col=y;
				terms[i].value=z;
			}
		}
		void output()
		{
			int x=0;
			for(int i=1;i<=rows;i++)
			{
				for(int j=1;j<=cols;j++){
					if(i==terms[x].row&&j==terms[x].col)
					{
						o<<terms[x].value<<" ";
						if(x!=size-1)x++;
					}
					else o<<0<<" ";
				}
				o<<endl;
			}
		}
	private:	
		int rows,cols;
		int length;
		int size;
		matrixTerm<T> *terms;
 };
int main()
{
	int n;
	cin>>n;
	sparseMatrix<int> p;
	sparseMatrix<int> q;
	sparseMatrix<int> m;
	for(int i=0;i<n;i++)
	{
		int n1,row,col;
		cin>>n1;
		switch(n1){
			case 1:
				cin>>row>>col;
				p(row,col);
				p.reset();
				break;
			case 2:
				cin>>row>>col;
				q(row,col);
				q.input();
				try{
					p=p*q;
				}catch(int x){
					p=q;
					o<<-1<<endl;
				}
				break;
			case 3:
				cin>>row>>col;
				q(row,col);
				q.input();
				try{
					p=p+q;
				}catch(int x){
					p=q;
					o<<-1<<endl;
				}
				break;
			case 4:
				o<<p.showrow()<<" "<<p.showcol()<<" "<<endl;
				p.output();
				break;
			case 5:
				p.transpose();
				break;
		}
	}
	cout<<o.str();
}