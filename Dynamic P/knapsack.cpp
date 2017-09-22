// Authors: David Vega and Rohin Mohanadas
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;


// Constructs the knapsack and returns the array indices as a vector of ints
vector<int> knapsack(int capacity, int n, int val[], int weight[]){
    vector<int> ret;

    int best[n+1][capacity+1] ={0};

    // build the selection option matrix with item options as rows and weights (upto capacity) as columns
    for(int i=0;i<=n;i++){
        for(int j=0;j<=capacity;j++){
            if (i==0 || j==0)
                best[i][j] = 0;
            else if(weight[i-1] <=j){
                best[i][j] = max(val[i-1] + best[i-1][j-weight[i-1]],  best[i-1][j]);
            }else{
                best[i][j] = best[i-1][j];
            }
        }
    }

    // back track through the matrix from the max value to identify the weights added.
    int i = n, k = capacity;
    while(i > 0 && k > 0){
        if(best[i][k] != best[i-1][k]){
            ret.push_back(i-1);
            i--;
            k = k - weight[i];
        }else{
            i--;
        }
    }

    return ret;
}

int main(){

    vector<int> result;
    double capacity;
    int n;
    string line1;
    while(cin>>capacity>>n) {
    int cpt = floor(capacity);

    int ctr = n;
    int val[n],weight[n];
    int i = 0;
    while(i<n){
        cin>>val[i]>>weight[i];
        i++;
    }

    result = knapsack(cpt,n,val,weight);

    cout<<result.size()<<endl;
    for (vector<int>::iterator it = result.begin(); it != result.end(); it++)
        cout<<*it<<" "; 
    cout<<endl;
    }
}