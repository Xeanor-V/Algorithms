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

    /**
     * 
     * Accepts the graph in adjacency list format.
     * start denotes the start index of the node. Index starts from 0
     * dist_path is used to return distance to node or path conditionally.
     * 
     * */
    vector<int> djiktra_path(vector<vector<pair<int, int> > > graph, int start, char dist_path = 'D')
    {

        vector<int> Q;
        vector<int> distance(graph.size());
        vector<int> prev(graph.size(), -1);
        for (int i = 0; i < graph.size(); i++)
        {
            distance[i] = 9999999;
            Q.push_back(i);
        }
        distance[start] = 0;

        while (!Q.empty())
        {
            int min = 9999999, idx = 0, node;
            for (int i = 0; i < Q.size(); i++)
            {
                if (distance[Q[i]] < min)
                {
                    min = distance[Q[i]];
                    idx = i;
                    node = Q[i];
                }
            }

            int minNode = idx;
            int minDist = min;

            // for each neighbour of node that still exists in Q (the unprocessed list of nodes)
            for (int j = 0; j < graph[node].size(); j++)
            {
                if (find(Q.begin(), Q.end(), graph[node][j].first) != Q.end())
                {
                    int alt;
                    alt = min + graph[node][j].second;
                    if (alt < distance[graph[node][j].first])
                    {
                        distance[graph[node][j].first] = alt;
                        prev[graph[node][j].first] = node;
                    }
                }
            }
            Q.erase(Q.begin() + idx);
        }

        if (dist_path == 'P')
            return prev;
        else
            return distance;
    }

    /**
     * 
     * Api to return a vector of shortest path from the start node to the destination node if one exists
     * 
     * */
    vector<int> constructed_path(vector<int> parent, int start, int dest)
    {
        bool breakout = false;
        vector<int> res;
        if (start == dest)
        {
            res.push_back(start);
            return res;
        }
        res.push_back(dest);
        int prev = parent[dest];
        while (prev != start)
        {
            if (prev == -1)
            {
                breakout = true;
                break;
            }
            res.push_back(prev);
            prev = parent[prev];
        }
        if (!breakout)
        {
            res.push_back(start);
            reverse(res.begin(), res.end());
        }
        else
        {
            res.clear();
        }
        return res;
    }

    /**
     * 
     * Helper function to help with the time factor during distance/cost computation in dijkstra
     * 
     * */
    int finder(int timer, int strtT, int stpT, int dist)
    {

        if (stpT == 0)
        {
            if (strtT >= timer)
                return strtT - timer;
            else
                return MAX;
        }
        if (strtT >= timer)
            return strtT - timer;
        int t = (timer - strtT + stpT - 1) / stpT;
        return strtT + t * stpT - timer;
    }
    /**
     * 
     * Dijkstra shortest path augmented with edge timings. Each element in graph is a pair of pairs
     * first.first : to_node
     * first.second : distance to to_node
     * second.first : t0
     * second.secon : P
     * 
     * Stored as adjacency lists for easy neighbour info collection.
     * */
    vector<int> djiktra_time_path(vector<vector<pair<pair<int, int>, pair<int, int> > > > graph, int start, char dist_path = 'D')
    {
        vector<int> Q;
        vector<int> distance(graph.size());
        vector<int> prev(graph.size(), -1);
        for (int i = 0; i < graph.size(); i++)
        {
            distance[i] = 9999999;
            Q.push_back(i);
        }
        distance[start] = 0;

        while (!Q.empty())
        {
            int min = 9999999, idx = 0, node;
            for (int i = 0; i < Q.size(); i++)
            {
                if (distance[Q[i]] < min)
                {
                    min = distance[Q[i]];
                    idx = i;
                    node = Q[i];
                }
            }

            int minNode = idx;
            int minDist = min;
            int timer = 0;
            timer = min;
            // for each neighbour of node that still exists in Q (the unprocessed list of nodes)
            for (int j = 0; j < graph[node].size(); j++)
            {

                if (find(Q.begin(), Q.end(), graph[node][j].first.first) != Q.end())
                {
                    int t0, P, dist;

                    t0 = graph[node][j].second.first;
                    P = graph[node][j].second.second;
                    dist = graph[node][j].first.second;
                    int extra = finder(timer, t0, P, dist);

                    int alt;
                    alt = min + graph[node][j].first.second + extra;
                    if (alt < distance[graph[node][j].first.first])
                    {
                        distance[graph[node][j].first.first] = alt;
                        prev[graph[node][j].first.first] = node;
                    }
                }
            }
            Q.erase(Q.begin() + idx);
        }

        if (dist_path == 'P')
            return prev;
        else
            return distance;
    }  
    
    /**
     *  Accepts the adjacency list and the start node for the eulerian walk
     *  Returns the eulerian path if one exists, else returns empty vector.
     * 
     *  NOTE: start has to be either:
     *  1) a random node if all the nodes have even degree or
     *  2) out of the two odd degree nodes, the one with out degree one greater than in degree
     * 
     * */
    vector <int> eulerian (vector<vector <int> > graph, int start){
        stack <int> nodestack;
        vector <int> path;
        int current = start;

        while(graph[current].size()!=0 || nodestack.size()!=0)
            if(graph[current].size()==0){
                path.push_back(current);
                current = nodestack.top();
                nodestack.pop();
            }else{
                nodestack.push(current);
                int temp = graph[current][0];
                graph[current].erase(graph[current].begin()+0);
                current = temp;
            }
        path.push_back(current);        
    
        for(int i = 0;i<graph.size();i++){
            if(graph[i].size()!=0)
            {
                path.clear();
            }
        }
        reverse(path.begin(),path.end());
        cout<<"\n";
        return path;
    }