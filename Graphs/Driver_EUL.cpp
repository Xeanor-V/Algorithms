
//Authors: David Vega Ramirez / Rohin Mohanadas
//Implementation of Dijkstra's algorithm

#include "Graphs.hpp"

using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    while(n!=0 && m!=0){
        vector<int> inout(n,0);
        vector<vector <int> > adjlist(n);
        int i = 0;
        while(i<m){
            int from,to;
            cin>>from>>to;
            adjlist[from].push_back(to);
            inout[from]++;
            inout[to]--;
            i++;
        }
        int countE=0,countG=0,countL=0;
        int indLess, indMore;
        for(int i=0;i<n;i++){
            if(inout[i]==0)
                countE++;
            else if(inout[i]<0){
                countL++;
                indLess = i;
            }
            else{
                countG++;
                indMore = i;
            }
        }
        vector <int> path;
        // cout<<countE<<" "<<countL<<" "<<countG<<"\n";
        if(countE!=n){
            if(countL!=countG || (countL == countG && countL > 1)){
                // cout<<"Impossible\n";
            }else{
                path = eulerian(adjlist,indMore);
            }
        }else{
            path = eulerian(adjlist,rand()%n);
        }
        if(path.size()==0){
            cout<<"Impossible\n";
        }else{
            for(int i=0;i<path.size();i++){
                cout<<path[i]<<" ";
            }
            cout<<"\n";
        }
        cin>>n>>m;
    }

}