#include <bits/stdc++.h>
using namespace std;


 int CIndex(int l, int r, int k, vector <int> &Tail)
 {
    int m;
    while(r - l > 1)
    {
        m = l + (r - l)/2;
        if( m>= 0)
        (Tail[m] >= k ? r : l) = m;
    }
    return r;
 }

vector<int> LIS(vector<int> Num)
{
    int len = 1;
    vector <int> tailTable(Num.size(),0);
    tailTable[0] = Num[0];
    for(int i = 1; i < Num.size(); i++)
    {
        if(Num[i] < tailTable[0]) tailTable[0] = Num[i];
        else if(Num[i] > tailTable[len-1] && len-1>=0) tailTable[len++] = Num[i];
        else
        {
            int res = CIndex(-1, len-1, Num[i],tailTable);
            if(res >= 0) tailTable[res] = Num[i];
        }
    }
    return tailTable;
}


int main()
{
    int n;
    cin>>n;
    vector<int>Num(n);
    for(int i = 0 ; i < n; i++) cin>>Num[i];
    Num = LIS(Num);
    for(int i = 0; i < Num.size();i++) cout<<Num[i]<<' ';
    cout<<'\n';
    return 0;
}

/*
int A[1005];
int tailTable[1005];
int CeilIndex(int l, int r, int key) {
 int m;
 while( r - l > 1 ) {
 m = l + (r - l)/2;
 if(m>=0)
 (tailTable[m] >= key ? r : l) = m;
 }return r;}
int LIS(int n) {
 int len;memset(tailTable, 0, sizeof tailTable);
 tailTable[0]=A[0];len = 1;
 for(int i=1;i<n;i++) {
 if( A[i] < tailTable[0] )
 tailTable[0] = A[i];
 else if( A[i] > tailTable[len-1] && len-1>=0)
 tailTable[len++]=A[i];
 else{
 int res=CeilIndex(-1, len-1, A[i]);
 if(res>=0)
 tailTable[res] = A[i];
 }
 }return len;}


*/