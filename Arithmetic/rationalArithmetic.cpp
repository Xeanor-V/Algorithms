//Authors : David Vega and Rohin Mohanadas
//Rational arithmetic implementation.

#include <iostream>
#include <cmath>
#include <algorithm> 

using namespace std;

// The struct in charge of holding the rational number.
struct fact
{
    long long int num;
    long long int deno;

    // empty constructor.
    fact()
    {
        num = 0;
        deno = 1;
    }

    // main constructor (takes out gcd from num and deno and moves negatives)
    fact(long long int n, long long int d)
    {
        if (d < 0)
            n = -n, d = -d;
        long long gcd_ = __gcd(abs(n), abs(d));
        num = n / gcd_, deno = d / gcd_;
    }

    // negation operator.
    fact operator-()  const {
        return fact(-num, deno);
    }

    // rational sum
    fact operator+(const fact &f)
    {
        long long gcd_ = __gcd(deno, f.deno);
        return fact(num * (f.deno / gcd_) +
                        f.num * (deno / gcd_),
                    deno * (f.deno / gcd_));
    }

    // rational subtraction ( uses sum ^^)
    fact operator-(const fact &f)
    {
        return *this + -f;
    }

    // rational multiplication 
    fact operator*(const fact &f)
    {
        return fact(num * f.num, deno * f.deno);
    }

    // rational division 
    fact operator/(const fact &f)
    {
        return fact(num * f.deno, deno * f.num);
    }

    // comparator
    bool operator<(const fact &cmp)
    {
        long long gcd_ = __gcd(deno, cmp.deno);
        return num * (cmp.deno / gcd_) <
               cmp.num * (deno / gcd_);
    }

    // equality checker.
    bool operator==(const fact &cmp)
    {
        long long gcd_ = __gcd(deno, cmp.deno);
        return num * (cmp.deno / gcd_) ==
               cmp.num * (deno / gcd_);
    }
};

// rational printer. Again fixes negatives and gcd divisions.
void print(fact a)
{
    if (a.deno < 0)
        {
            a.num = -a.num; 
            a.deno = -a.deno;
        }
    long long gcd_ = __gcd(abs(a.num), abs(a.deno));
    cout << a.num/gcd_ << " / " << a.deno/gcd_<<endl;
}


int main()
{
    int noOp;
    cin>>noOp;

    long long int num1,num2,deno1,deno2;
    char space;
    char op;
    while(noOp--){
        cin>>num1>>deno1>>op>>num2>>deno2;
        fact op1 = fact(num1,deno1);
        fact op2 = fact(num2,deno2);
        switch(op){
            case '+':{
                print(op1+op2);
            }
            break;
            case '-':{
                print(op1-op2);
            }
            break;
            case '*':{
                print(op1*op2);
            }
            break;
            case '/':{
                print(op1/op2);
            }
            break;
        }
    }
}