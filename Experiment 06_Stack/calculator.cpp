#include <iostream>
#include <iomanip>
using namespace std;

template <class T>
void changeLength1D(T *&a, int oldLength, int newLength)
{
    T *temp = new T[newLength];             
    int number = min(oldLength, newLength); 
    copy(a, a + number, temp);
    delete[] a;
    a = temp;
}

template <class T>
class arraystack
{
public:
    arraystack(int initialCapacity = 10);
    ~arraystack() { delete[] stack; }
    bool empty() const { return stackTop == -1; }
    int size() const { return stackTop + 1; }
    void push(const T &theElement);
    T &top()
    {
        return stack[stackTop];
    }
    void pop()
    {
        stack[stackTop--].~T();
    }
    void calculate(arraystack<double> &x, arraystack<char> &y);
    void caculator(string s, int length);

private:
    int stackTop;
    int stackLength;
    T *stack;
};

template <class T>
arraystack<T>::arraystack(int initialCapacity)
{
    stackLength = initialCapacity;
    stack = new T[stackLength];
    stackTop = -1;
}

template <class T>
void arraystack<T>::push(const T &theElement)
{
    if (stackTop == stackLength - 1)
    {
        changeLength1D(stack, stackLength, 2 * stackLength);
        stackLength *= 2;
    }
    stack[++stackTop] = theElement;
}

template <class T>
void arraystack<T>::calculate(arraystack<double> &x, arraystack<char> &y)
{
    if (y.top() == '(')
        return;
    double m, n; //栈中两个相邻的数
    m = x.top(); //m为后输入的的数，为乘数或者除数
    x.pop();     //弹出栈顶元素
    n = x.top();
    x.pop();         //弹出栈顶元素
    switch (y.top()) //选择不同的运算
    {
    case '+':
        x.push(n + m);
        break;
    case '-':
        x.push(n - m);
        break;
    case '*':
        x.push(n * m);
        break;
    case '/':
        x.push(n / m);
        break;
    }
    y.pop(); //将运算完的符号弹出栈
}

template <class T>
void arraystack<T>::caculator(string s, int length)
{
    arraystack<double> a(length); //存储数字
    arraystack<char> b(length);   //存储运算符
    for (int i = 0; i < length; i++)
    {

        if (s[i] >= '0' && s[i] <= '9')
        {
            double m = s[i] - '0';                     //将字符型数字转化为double型数字
            while (s[i + 1] >= '0' && s[i + 1] <= '9') //连续两个数字相邻
            {                                          //第一个为十位，第二个为个位
                m = 10 * m + (s[i + 1] - '0');
                i++;
            }
            a.push(m);
        }
        else
        {
            switch (s[i])
            {
            case '+':
                if (b.empty() || b.top() == '(')
                    b.push(s[i]);
                else
                {
                    calculate(a, b);
                    if (!b.empty() && b.top() != '(')
                        calculate(a, b);
                    b.push(s[i]);
                }
                break;
            case '-':
                if (b.empty() || b.top() == '(')
                    b.push(s[i]);
                else
                {
                    calculate(a, b);
                    if (!b.empty() && b.top() != '(')
                        calculate(a, b);
                    b.push(s[i]);
                }
                break;
            case '*':
                if (b.empty() || b.top() == '(')
                    b.push(s[i]);
                else if (b.top() == '+' || b.top() == '-')
                    b.push(s[i]);
                else if (b.top() == '*' || b.top() == '/')
                {
                    calculate(a, b);
                    b.push(s[i]);
                }
                break;
            case '/':
                if (b.empty() || b.top() == '(')
                    b.push(s[i]);
                else if (b.top() == '+' || b.top() == '-')
                    b.push(s[i]);
                else if (b.top() == '*' || b.top() == '/')
                {
                    calculate(a, b);
                    b.push(s[i]);
                }
                break;
            case '(': //左括号直接入栈
                b.push(s[i]);
                break;
            case ')': //遇到右括号 ，对括号内运算直至运算到左括号
                while (b.top() != '(')
                {
                    calculate(a, b);
                }
                b.pop(); //将左括号弹出栈
                break;
            }
        }
    }
    while (!b.empty())
        calculate(a, b);
    cout << setprecision(2) << fixed << a.top() << endl;
}

int main()
{
    arraystack<double> x;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        int length;
        cin >> s;
        length = s.size();
        x.caculator(s, length);
    }
}