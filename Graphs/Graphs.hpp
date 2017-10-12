// Grahps library by David Vega Ramirez and Rohin Mohanadas
// October 2017

#include <bits/stdc++.h>
using namespace std;

typedef pair<pair<int,int>, int> w_edge;
typedef pair<int,int> edge;
typedef long long int LL;
       
int INF = 1e9;
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

    //Custom comparator for edges with weights used by Kruskal aglo
    struct cost_comparator {
        bool operator() (const w_edge& l, const w_edge& r) const {
            return l.second < r.second;
        }
    };
    // Obtaining the Minimum spanning tree, for Maximun spanning tree uncomment the reverse
    // The graph is represented as a vector of w_edges
    // w_edge acts as {u,v,weight} 
    // returns the mst and the associated cost
    pair<vector<edge>,LL> Kruskal(vector<w_edge>graph, int nodes) 
    {
        // Sorting the edges by cost
        sort(graph.begin(), graph.end(),cost_comparator());
        // reverse(todas.begin(), todas.end());
        vector<edge> mst;
        // using a Disjoint set to check if node it's already in the component
        // in order to avoid cycles
        DJSet components(nodes);
        LL maxi = 0;
        for(int i = 0 ; i < graph.size(); i++)
        {
            int u = graph[i].first.first;
            int v = graph[i].first.second;
            if(!components.isConnected(u,v))
            {
                // ordering by u < v
                components.Join(u,v);
                if(u > v)
                swap(u,v);
                mst.push_back(make_pair(u,v));
                maxi+= graph[i].second;
            }
        }
        sort(mst.begin(), mst.end());
        return make_pair(mst,maxi);
    }

    // Obtaining distance between all pairs of nodes in a directed graph
    // The graph is given as an adjacency matrix of n x n 
    // returns distance matrix 
    vector< vector<int> > floydWarshall(vector< vector<int> > graph )
    {
        // Case where there's an edge from a node to himself
        for(int i = 0 ; i < graph.size(); i++) graph[i][i] = 0;

        for(int i = 0 ; i < graph.size(); i++)
        {
            for(int j = 0; j < graph.size(); j++)
            {
                for(int k = 0; k < graph.size(); k++)
                {
                    if(graph[j][i] + graph[i][k] < graph[j][k] and graph[j][i] != INF and graph[i][k] != INF)
                        graph[j][k] = graph[j][i] + graph[i][k];            
                }
            }
        }
        // Detecting negative cycles and marking them as -INF
        for(int i = 0; i < graph.size(); i++)
            for(int j = 0; j < graph.size(); j++)    // Go through all possible sources and targets
                for(int k = 0; graph[i][j] != -INF && k < graph.size(); k++) // Checking if there's a negative in the path
                    if( graph[i][k] != INF && graph[k][j] != INF && graph[k][k] < 0)     
                        graph[i][j] = -INF;   
                                         
        return graph;
    }