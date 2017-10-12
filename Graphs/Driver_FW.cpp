#include "Graphs.hpp"
using namespace std;

int main()
{
    int n,e,q;
    int INF = 1e9;
    while(cin>>n>>e>>q)
    {
        if(n == 0 && e == 0 && q == 0) break;
        vector< vector<int> > graph(n,(vector<int>(n,INF)));
        for(int i = 0; i < n; i++) graph[i][i] = 0;
        for(int i = 0 ; i < e; i++)
        {
            int a,b,c;
            cin>>a>>b>>c;
            graph[a][b] = min(grap[a][b],c); // can have multiple edges to same, we just care about the one with smaller W
        }
        vector< vector<int> > dist = floydWarshall(graph);
        for(int i = 0; i < q; i++)
        {
            int a,b;
            cin>>a>>b;
            if(dist[a][b] == INF)
            cout<<"Impossible\n";
            else if(dist[a][b] == -INF)
            cout<<"-Infinity\n";
            else
            cout<<dist[a][b]<<'\n';
        }
        cout<<'\n';
        

    }
}