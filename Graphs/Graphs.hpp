// Grahps library by David Vega Ramirez and Rohin Mohanadas
// October 2017

#include <bits/stdc++.h>
using namespace std;

typedef pair<pair<int,int>, int> w_edge;
typedef pair<int,int> edge;
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
  
    pair<vector<edge>,int> Kruskal(vector<w_edge>graph, int nodes) 
    {
        sort(graph.begin(), graph.end(),cost_comparator());
        // reverse(todas.begin(), todas.end());
        vector<edge> mst;
        DJSet components(nodes);
        int maxi = 0;
        for(int i = 0 ; i < graph.size(); i++)
        {
            int u = graph[i].first.first;
            int v = graph[i].first.second;
            if(!components.isConnected(u,v))
            {
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