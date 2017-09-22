/*
 
 P = array of length N
 M = array of length N + 1

 L = 0
 for i in range 0 to N-1:
   // Binary search for the largest positive j ≤ L
   // such that X[M[j]] < X[i]
   lo = 1
   hi = L
   while lo ≤ hi:
     mid = ceil((lo+hi)/2)
     if X[M[mid]] < X[i]:
       lo = mid+1
     else:
       hi = mid-1

   // After searching, lo is 1 greater than the
   // length of the longest prefix of X[i]
   newL = lo

   // The predecessor of X[i] is the last index of 
   // the subsequence of length newL-1
   P[i] = M[newL-1]
   M[newL] = i

   if newL > L:
     // If we found a subsequence longer than any we've
     // found yet, update L
     L = newL

 // Reconstruct the longest increasing subsequence
 S = array of length L
 k = M[L]
 for i in range L-1 to 0:
   S[i] = X[k]
   k = P[k]

 return S

 */

#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>

using namespace std;

void lis(vector<long> &X, int N)
{
    map<long, long> val2pos;
    vector<long> res;
    for (int i = 0; i < N; i++)
    {
        val2pos.insert(pair<long, long>(X[i], i));
    }
    long P[N];
    long M[N + 1];
    int L = 0;
  
    for (int i = 0; i < N; i++)
    {
        int lo = 1;
        int hi = L;
        while (lo <= hi)
        {
            int mid = ceil((lo + hi) / 2);
            if (X[M[mid]] < X[i])
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        int newL = lo;
        P[i] = M[newL - 1];
        M[newL] = i;
        if (newL > L)
        {
            // If we found a subsequence longer than any we've
            // found yet, update L
            L = newL;
        }
    }

    cout << L << endl;
    long S[L];
    int k = M[L];
    for (int i = L - 1; i >= 0; i--)
    {
        S[i] = X[k];
        k = P[k];
        res.push_back(val2pos[S[i]]);
    }
    sort(res.begin(),res.end());
     
    for (int i = 0; i < L; i++)
    {
        // cout<<S[i]<<" ";
        cout << res[i] << " ";
    }
    cout << endl;
    // if(N>20000 && N< 100000)
    // while(1){
    //    int k = 1;
    // }     
    // return S;
}
int main()
{
    int N;

    while (cin >> N)
    {

        int counter = N;
        //int X[N];
        vector<long> X;
        int i = 0;
        while (counter--)
        {
            int element = 0;
            cin >> element;
            X.push_back(element);
        }
        cout<<"starting"<<endl;
        lis(X, N);
        cout<<"done"<<endl;
    }
}