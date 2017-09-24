#include <iostream>
#include <cmath>
#include <sstream>
#include <algorithm> 
using namespace std;


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

    fact operator=(const fact &f)
    {
        // long long gcd_ = __gcd(deno, f.deno);
        this->deno = f.deno;
        this->num = f.num;
        return fact(num,deno);
    }    
};

void print(fact a)
{
    if (a.deno < 0)
        {
            a.num = -a.num; 
            a.deno = -a.deno;
        }
    long long gcd_ = __gcd(abs(a.num), abs(a.deno));
    cout << a.num/gcd_ << "/" << a.deno/gcd_<<endl;
}

int main(){
    string line;
    bool flag = false;
    double debug;
    int power;
    if(flag){
        cin>>debug>>power;
        cout<<debug<<" "<<pow(10,power)<<" "<<(int)(debug*pow(10,power))<<debug*1000<<endl;
        return 0;
    }
    while(getline(cin,line)){
        if(line.compare("0")==0){
            break;
        }
        double value;
        string doubleStr;
        int length = line.find("...");
        int decimalLength = length - 2;
        int pow1;
        int pow2;
        doubleStr = line.substr(2,length);
        fact min(1,999999999999999999LL);
        long long int num1 = 0;
        long long int num2 = 0;
        for(int i=1;i<=length - 2;i++){
            num1 = 0;
            num2 = 0;
            for(int k=0;k<(length-2-i);k++)
                num1 = num1*10 + (doubleStr[k]-'0');
            
            for(int k=0;k<(length-2);k++)
                num2 = num2*10 + (doubleStr[k]-'0');

            pow1 = length-2-i;
            pow2 = length-2;

            fact num(abs((num2 - num1)), abs((pow(10,pow2) - pow(10,pow1))));
            // print(num);
            if(min.deno > num.deno){
                min=num;
            }
            
                      
        }
        print(min);  
    }
    
}