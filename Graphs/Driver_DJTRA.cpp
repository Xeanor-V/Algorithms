//Authors: David Vega Ramirez / Rohin Mohanadas
//Implementation of Dijkstra's algorithm

#include "Graphs.hpp"

#define MAX 9999999

using namespace std;

int main(){
    int n, m, q, start;
    cin >> n >> m >> q >> start;
    vector<vector<pair<int, int> > > graph(n);
    vector<int> distance;
    while (!(n == 0 && m == 0 && q == 0 && start == 0))
    {
        while (m--)
        {
            int n1, n2, w;
            cin >> n1 >> n2 >> w;
            graph[n1].push_back(make_pair(n2, w));
        }
        distance = djiktra_path(graph, start, 'D');

        while (q--)
        {
            int query;
            cin >> query;
            if (distance[query] >= 9999999)
            {
                cout << "Impossible\n";
            }
            else
            {
                cout << distance[query] << "\n";
            }
        }
        cout << "\n";
        cin >> n >> m >> q >> start;
        vector<vector<pair<int, int> > > graph2(n);
        graph = graph2;
    }
}