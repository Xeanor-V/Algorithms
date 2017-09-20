//Authors: David Vega Ramirez / Rohin Mohanadas
//Implementation of Disjoint set

#include <bits/stdc++.h>
using namespace std;

struct DJSet {

    int n; vector<int> root, size;

    DJSet(int N) : n(N),
        size(N, 1), root(N) {
        while (--N) root[N] = N;
    }
    //Find root of set by backtracking
    int findRoot(int u) {
        if (root[u] == u) return u;
        return root[u] = findRoot(root[u]);
    }

    bool isConnected(int u, int v) {
        return findRoot(u) == findRoot(v);
    }
    
    void Join(int u, int v) {
        int Ru = findRoot(u);
        int Rv = findRoot(v);
        if (Ru == Rv) return;
        --n, root[Ru] = Rv;
        size[Rv] += size[Ru];
    }

    int Size(int u) {
        return size[findRoot(u)];
    }
};


int main()
{
    int n,m;
    cin>>n>>m;
    DJSet dj(n);
    for(int i = 0; i < m;i++)
    {
        char op;
        int a,b;
        cin>>op;
        cin>>a>>b;
        if(op == '=') dj.Join(a,b);
        else cout<< (dj.isConnected(a,b)==1?"Yes":"No")<<'\n';
    }
    return 0;
}