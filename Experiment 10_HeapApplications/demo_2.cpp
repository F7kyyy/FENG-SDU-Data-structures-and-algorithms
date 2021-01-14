#include<iostream>
#include<string>
using namespace std;
struct HuffmanNode//定义霍夫曼节点 
{
   int element;
   HuffmanNode *leftChild,   //左子树
                     *rightChild;  // 右子树
   int weight;
   HuffmanNode(){}
};
template <class T>//链表结构 
struct chainNode 
{
   // data members
   T element;
   chainNode<T> *next;

   // methods
   chainNode() {}
   chainNode(const T& element)
      {this->element = element;}
   chainNode(const T& element, chainNode<T>* next)
      {this->element = element;
       this->next = next;}
};
template<class T>
class linkedQueue 
{
   public:
      linkedQueue(int initialCapacity = 10)
            {queueFront = NULL; queueSize = 0;}//初始化队列 
      ~linkedQueue();//析构函数 
      bool empty() const 
           {return queueSize == 0;}
      int size() const
          {return queueSize;}
      T& front()//队首 
         {
            if (queueSize == 0)
              exit(1);
            return queueFront->element;
         }
      T& back()//队尾 
         {
            if (queueSize == 0)
               exit(1);
            return queueBack->element;
         }
      void pop();//删除队首 
      void push(const T&);//插入到队尾 
   private:
      chainNode<T>* queueFront;  
      chainNode<T>* queueBack;   
      int queueSize;         
};
//析构函数 
template<class T>
linkedQueue<T>::~linkedQueue()
{
   while (queueFront != NULL)
   {
      chainNode<T>* nextNode = queueFront->next;
      delete queueFront;
      queueFront = nextNode;
   }
}
//删除队首 
template<class T>
void linkedQueue<T>::pop()
{
   if (queueFront == NULL)
      exit(1);
   chainNode<T>* nextNode = queueFront->next;
   delete queueFront;
   queueFront = nextNode;
   queueSize--;
}
template<class T>
void linkedQueue<T>::push(const T& theElement)
{
   chainNode<T>* newNode = new chainNode<T>(theElement, NULL);
   if (queueSize == 0)
      queueFront = newNode;      
   else 
      queueBack->next = newNode;  
   queueBack = newNode;

   queueSize++;
}
class minHeap{
	public:
	minHeap() { length = 0; p = new HuffmanNode*[26]; }
	//因为字母表中有26个单词
	~minHeap() { delete[]p; }
	void initialize(HuffmanNode** a, int n);
	void insert(HuffmanNode* num);
	void pop();
	HuffmanNode* top() { return p[1];}
	private:
		int length;
		HuffmanNode **p;
};
void minHeap::initialize(HuffmanNode **a, int n)//初始化
{
	length = n;
	for (int i = 0; i < n; i++)
		p[i + 1] = a[i];
	for (int root = length / 2; root >= 1; root--)
	{
		HuffmanNode* rootelement = p[root];
		int child = 2 * root;
		while (child <= length)
		{
			if (child<length&&p[child]->element>p[child + 1]->element)
			{
				child++;
			}
			if (rootelement->element <= p[child]->element)
				break;
			else
			{
				p[child / 2] = p[child];
				child = child * 2;
			}
		}
		p[child / 2] = rootelement;
	}
}
void minHeap::insert(HuffmanNode* num)//插入函数
{
	int current = length + 1;//元素将要插入的位置
	length++;
	while (current > 1 && p[current / 2]->element > num->element)
	{
		p[current] = p[current / 2];
		current = current / 2;
	}
	p[current] = num;
}
void minHeap::pop()//删除函数 
{
	HuffmanNode* lastelement = p[length];
	int root = 1;
	int child = 2;
	length--;
	while (child <= length)
	{
		if (child<length&&p[child]->element>p[child + 1]->element)
		{
			child++;
		}
		if (lastelement->element <= p[child]->element)
			break;
		p[root] = p[child];
		root = child;
		child = child * 2;
	}
	p[root] = lastelement;
}
class Huffmantree
{
	public:
		HuffmanNode *root;//定义根
		Huffmantree() {}//构造函数 
		~Huffmantree();//析构函数 
		void maketree(int *a,int n);//n为字符串的size
		void length();//霍夫曼编码长度
	private:
		int size; 
};
//析构函数 
Huffmantree::~Huffmantree(){
	linkedQueue<HuffmanNode*> q;
	q.push(root);
	for (int i = 0; i < size; i++)
	{
		HuffmanNode* currentNode = q.front();
		q.pop();
		if (currentNode->leftChild != NULL)
		{
			q.push(currentNode->leftChild);
		}
		if (currentNode->rightChild != NULL)
		{
			q.push(currentNode->rightChild);
		}
		delete currentNode;
	}
}
//建立一棵霍夫曼树 
void Huffmantree::maketree(int *a, int n)
{
	HuffmanNode **hufnode = new HuffmanNode*[n];
	for (int i = 0; i < n; i++)//置空 
	{
		hufnode[i] = new HuffmanNode();
		hufnode[i]->element = a[i];
		hufnode[i]->leftChild = hufnode[i]->rightChild = NULL;
	}
	minHeap h;
	h.initialize(hufnode, n);
	HuffmanNode *w, *x, *y;
	for (int i = 1; i < n; i++)//建立一棵霍夫曼树 
	{
		x = h.top(); h.pop();
		y = h.top(); h.pop();
		w = new HuffmanNode();
		w->leftChild = x;
		w->rightChild = y;
		w->element = x->element + y->element;
		x = NULL;
		y = NULL;
		h.insert(w);
	}
	size = n;
	root = h.top();
	h.pop();
}
//计算霍夫曼编码的长度
void Huffmantree::length()
{
	int result = 0;
	linkedQueue<HuffmanNode*> que;
	HuffmanNode *currentNode;
	que.push(root);
	root->weight = 0;
	while (!que.empty())
	{
		currentNode = que.front();
		que.pop();
		if (currentNode->leftChild != NULL)
		{
			que.push(currentNode->leftChild);
			currentNode->leftChild->weight = currentNode->weight + 1;
		}
		if (currentNode->rightChild != NULL)
		{
			que.push(currentNode->rightChild);
			currentNode->rightChild->weight = currentNode->weight + 1;
		}
		if (currentNode->leftChild == NULL && currentNode->rightChild == NULL)
		{
			result = result + currentNode->weight*currentNode->element;
		}
	}
	cout << result;
}
int main()
{
	string str;int index = 0,n= 0;
	cin>>str;
	int *a = new int[26];//统计各个字母出现频率 
	for (int i = 0; i < 26; i++)
		a[i] = 0;
	for (int j = 0; j < str.size(); j++)
	{
		a[(int)str[j] - 97]++;
		if (a[(int)str[j] - 97] == 1)
			n++;
	}
	int *b = new int[n];
	for (int k = 0;k < 26; k++)
	{
		if (a[k] != 0)
		{
			b[index]=a[k];
			index++;
		}
	}
	Huffmantree Huff;
	Huff.maketree(b,n);
	Huff.length();
	return 0;
}