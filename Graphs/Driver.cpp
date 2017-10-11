#include "Graphs.hpp"
using namespace std;

int main()
{
    int a = 600000000;
    cout<<a<<endl;
    int n,m;
    while(cin>>n>>m)
    {
        if(n == 0 && m == 0) break;

        vector<w_edge> graph;
        for(int i = 0 ; i < m; i++)
        {
            int a,b,c;
            cin>>a>>b>>c;
            graph.push_back(make_pair(make_pair(a,b),c));
        }
        pair<vector<edge>,int> res = Kruskal(graph,n);
        if(res.first.size() == 0)
        {
            cout<<"Impossible\n";
            continue;
        }
        cout<<res.second<<'\n';
        vector<edge> mst = res.first;
        for(int i = 0 ; i < mst.size(); i++)
        {
            cout<<mst[i].first<<' '<<mst[i].second<<endl;
        }

    }
}