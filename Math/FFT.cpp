//Authors: David Vega Ramirez / Rohin Mohanadas
//Implementation of Polynoms multiplication.

//Note while printing, do not cast to int.
//Using valarray instead of vector due to operations
#include <bits/stdc++.h>
using namespace std;
const double PI = 3.141592653589793238460;
typedef complex<double> Complex;
typedef valarray<Complex> CArray;
 
// Cooley–Tukey FFT (in-place, divide-and-conquer)
void fft(CArray& x)
{
    int  N = x.size();
    if (N <= 1) return;
    // divide
    CArray even = x[slice(0, N/2, 2)];
    CArray  odd = x[slice(1, N/2, 2)];
    // conquer
    fft(even);
    fft(odd);
    // combine
    for (int k = 0; k < N/2; ++k)
    {
        Complex t = polar(1.0, -2 * PI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}

// Inverse FFT
void ifft(CArray& x)
{
    // conjugate the complex numbers
    x = x.apply(conj);
    // forward fft
    fft(x);
    // conjugate the complex numbers again
    x = x.apply(conj);
    // scale the numbers
    x /= x.size();
}

// Implementation of discrete convolution for polynom multiplication
CArray Convolution(vector<double> a,vector<double> b) {

    int n = a.size() + b.size() - 1;
    // Since FFT works better with pots of 2
    // we find the closes potence of 2 and we fill with 0's to match the sizes.
    int p = 1; while (p < n) p <<= 1;
    CArray A(p), B(p), C(p);
    for (int i = 0; i < a.size(); ++i)
        A[i] = a[i];
    for (int i = 0; i < b.size(); ++i)
        B[i] = b[i];

    fft(A);
    fft(B);
    for (int i = 0; i < p; ++i)
        C[i] = A[i] * B[i];
    ifft(C);

    return C;
}

int main() {
    // Due to huge amount of input/output we can sync cin/cout 
    cin.tie(0);
    ios_base::sync_with_stdio(0);
     int t;
     cin>>t;
     while(t--)
     {
         int n;
         cin>>n;
         vector<double> a(n+1);
         for(int i = 0 ; i < n+1; i++ ) cin>>a[i];
         int m;
         cin>>m;
         vector<double> b(m+1);
         for(int i = 0; i < m+1; i++) cin>>b[i];
 
         CArray res = Convolution(a,b);
         //Finding the actual degree of the resulting polynom 
        int last = 0;
         for(int i = 0; i < res.size(); i++)
         {
             int num = real(res[i]);
             if(num != 0) last = i;
         }
         cout<<last<<endl;
         for(int i = 0; i < last+1; i++)
         {
			 if(i) cout<<' ';
			 //Problem when converting the real part to int, so this acts as a 'Floor' function to trim the decimals.
             cout<<fixed<<setprecision(0)<<real(res[i]);
         }
         cout<<'\n';
     }
     return 0;
 }
