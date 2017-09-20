//Authors: David Vega Ramirez / Rohin Mohanadas
//Implementation of Fenwick tree

#include <bits/stdc++.h>
using namespace std;

struct FenTree {
    //Vector for representing the tree as an array
    vector<long long int> tree;
    FenTree(int n) : tree(n + 1) {}
    
    void Insert(long long int i, long long int v) {
        while (i < tree.size()) {
            tree[i] += v;
            i += i & -i;
        }
    }
    
    long long int Query(long long int i) {
         long long int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= i & -i;
        }
        return sum;
    }
    //We can obtain the sum of a range by using inclusion/exclusion
    long long int Range(long long int i, long long int j) {
        return Query(j) -
               Query(i - 1);
    }
};


int main()
{
    int n,m;
    cin>>n>>m;
    FenTree Ftree(n);
    for(int i = 0 ; i < m ; i++)
    {
        char op;
        cin>>op;
        if(op == '+')
        {
            long long int a,b;
            cin>>a>>b;
            Ftree.Insert(a+1,b);
        }
        else
        {
            long long int a;
            cin>>a;
            if(a == 0)
            {
                cout<<'0'<<'\n';
            }
            else cout<<Ftree.Query(a)<<'\n';
        }
    }
    return 0;

}