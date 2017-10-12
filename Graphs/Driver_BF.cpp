#include "Graphs.hpp"
using namespace std;

int main()
{
    int n,m,q,s;
    while(cin>>n>>m>>q>>s)
    {
        if(n == 0 && m == 0 && q == 0 && s == 0) break;
        vector< w_edge > graph(n);
        for(int i = 0; i < m; i++)
        {
            int a,b,c;
            cin>>a>>b>>c;
            graph.push_back( make_pair(make_pair(a,b),c ));
        }

        vector<vector<int> >  res = BellmanFerrari(s,n,graph);

        /*for(int i = 0 ; i < res.size(); i++)
        {
            for(int j = 0 ; j < res[i].size(); j++)
            cout<<res[i][j]<<" ";
            cout<<'\n';
        }*/

        for(int i = 0 ; i < q; i++)
        {
            int a;
            cin>>a;
            int dis = res[res.size()-1][a];
            if(dis == INF)
            cout<<"Impossible\n";
            else if(dis <= -INF)
            cout<<"-Infinity\n";
            else
            cout<<dis<<'\n';
        }
        cout<<"\n";

    }
    return 0;
}