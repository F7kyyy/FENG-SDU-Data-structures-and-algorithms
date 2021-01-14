#include <iostream>
#include <cmath>
using namespace std;

class currency
{

    enum signType
    {
        plus,
        minus
    };

public:
    currency(signType theSign = plus, unsigned long theDollars = 0, unsigned int theCents = 0);
    ~currency() {}
    void setValue(signType, unsigned long, unsigned int);
    void setValue(double);
    void intput();
    currency subtract(const currency &p);
    currency percent(double x);
    currency multiply(double x);
    currency divide(double x);

private:
    signType sign;
    unsigned long dollars;
    unsigned int cents;
};

currency::currency(signType theSign, unsigned long theDollars, unsigned int theCents)
{
    setValue(theSign, theDollars, theCents);
}

void currency::setValue(signType theSign, unsigned long theDollars, unsigned int theCents)
{
    if (theCents > 99)
    {
        cents = theCents % 100;
        dollars = theDollars + theCents / 100;
        sign = theSign;
    }
    else
    {
        sign = theSign;
        dollars = theDollars;
        cents = theCents;
    }
}

void currency::setValue(double theAmount)
{
    if (theAmount < 0)
    {
        sign = minus;
        theAmount = -theAmount;
    }
    else
        sign = plus;
    dollars = (unsigned long)theAmount;
    cents = (unsigned int)((theAmount + 0.001 - dollars) * 100);
}

void currency::intput()
{
}

currency currency::subtract(const currency &p)
{
    int m_cents;
    if (p.sign == minus)
        m_cents = -(p.dollars * 100 + p.cents);
    else
        m_cents = p.dollars * 100 + p.cents;
    cents = dollars * 100 + cents + m_cents;
    if (cents > 0)
    {
        dollars = cents / 100;
        cents = cents % 100;
        sign = plus;
    }
    else
    {
        dollars = -cents / 100;
        cents = -cents % 100;
        sign = minus;
    }
}

currency currency::percent(double x)
{
    currency result;
    int a = result.dollars * 100 + result.cents;
    a = (long)(a * x / 100);
    result.dollars = a / 100;
    result.cents = a % 100;
    return result;
}

currency currency::multiply(double x)
{
    currency result;
    int a = result.dollars * 100 + result.cents;
    a = (long)(a * x);
    result.dollars = a / 100;
    result.cents = a % 100;
    return result;
}

currency currency::divide(double x)
{
    currency result;
    int a = result.dollars * 100 + result.cents;
    a = (long)(a / x);
    result.dollars = a / 100;
    result.cents = a % 100;
    return result;
}
