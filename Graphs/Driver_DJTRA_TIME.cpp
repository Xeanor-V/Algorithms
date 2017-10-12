//Authors: David Vega Ramirez / Rohin Mohanadas
//Implementation of Dijkstra's algorithm

#include "Graphs.hpp"

#define MAX 9999999

using namespace std;

int main(){
    int n, m, q, start;
    cin >> n >> m >> q >> start;
    vector<vector<pair<pair<int, int>, pair<int, int> > > > graph(n);
    vector<int> path, full_path;
    while (!(n == 0 && m == 0 && q == 0 && start == 0))
    {
        while (m--)
        {
            int n1, n2, t_0, P, d;
            cin >> n1 >> n2 >> t_0 >> P >> d;
            graph[n1].push_back(make_pair(make_pair(n2, d), make_pair(t_0, P)));
        }
        full_path = djiktra_time_path(graph, start, 'D');

        while (q--)
        {
            int query;
            cin >> query;
            {
                if (full_path[query] >= 9999999)
                    cout << "Impossible\n";
                else
                    cout << full_path[query] << "\n";
            }
        }
        cout << "\n";
        cin >> n >> m >> q >> start;
        vector<vector<pair<pair<int, int>, pair<int, int> > > > graph2(n);
        graph = graph2;
    }
}