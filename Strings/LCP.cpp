#include <bits/stdc++.h>
using namespace std;


const int maxN = 20;


struct tuple
{
    int indxs[2];
    int pos;
}L[maxN];

int cmp(struct tuple a, struct tuple b) // Check tuples current step and next one to give sorting index.
{
    return (a.indxs[0] == b.indxs[0]) ? (a.indxs[1] < b.indxs[1]?1:0) : (a.indxs[0] < b.indxs[0]?1:0);
}


int sortIndex[5000][maxN];


vector<int> Suffix_Array(string s)
{
    for(int i = 0 ; i < s.size() ; i++) //let's get all suffixes, we only need the first letter later we can form everyone based on this.
        sortIndex[0][i] = s[i] -'a';

    int done_till = 1, step = 1;
    int N = s.size();

    for(;done_till < N; step++, done_till*=2) // 2 step jump and till we have gone through all the string, also keep track of steps.
    {

        for(int i = 0 ; i < N ; i++) //Lets rearm the tuple
        {
            L[i].indxs[0] = sortIndex[step - 1][i]; // last SI is the current one
            L[i].indxs[1] = ( i + done_till ) < N? sortIndex[step-1][i + done_till]:-1; // next one is calculated using another previously                                                                              
            L[i].pos = i; // lets get new position                                         calculated SI of another suffix or if size too big -1
        }

        sort(L, L + N, cmp); // sorting tuples

        for(int i = 0 ; i < N; i++) //Lets calculate the new SI
        {
            sortIndex[ step ][ L[i].pos ] = i > 0 && L[i].indxs[0] == L[i - 1].indxs[0] && L[i].indxs[1] == L[i - 1].indxs[1] ? 
                                    sortIndex[ step ][ L[i-1].pos ] : i;
        }
        // after the sort the first one stays the same, now if it has the same values as i-1 it gets the same SI, if not then i (new SI)
    }
    vector <int> S_Array;
    for(int i = 0; i < s.size(); i++)
    {
        S_Array.push_back(L[i].pos);
    }
    return S_Array;
}
int maxi;
/* To construct and return LCP */
vector<int> kasai(string txt, vector<int> suffixArr)
{
    int n = suffixArr.size();
    map<string,int> ap;
    // To store LCP array
    vector<int> lcp(n, 0);
    maxi = 0;
 
    // An auxiliary array to store inverse of suffix array
    // elements. For example if suffixArr[0] is 5, the
    // invSuff[5] would store 0.  This is used to get next
    // suffix string from suffix array.
    vector<int> invSuff(n, 0);
 
    // Fill values in invSuff[]
    for (int i=0; i < n; i++)
        invSuff[suffixArr[i]] = i;
 
    // Initialize length of previous LCP
    int k = 0;
 
    // Process all suffixes one by one starting from
    // first suffix in txt[]
    for (int i=0; i<n; i++)
    {
        /* If the current suffix is at n-1, then we don’t
           have next substring to consider. So lcp is not
           defined for this substring, we put zero. */
        if (invSuff[i] == n-1)
        {
            k = 0;
            continue;
        }
 
        /* j contains index of the next substring to
           be considered  to compare with the present
           substring, i.e., next string in suffix array */
        int j = suffixArr[invSuff[i]+1];
        string aux = "";
 
        // Directly start matching from k'th index as
        // at-least k-1 characters will match
        while (i+k<n && j+k<n && txt[i+k]==txt[j+k])
        {
            k++;
            aux+=txt[i+k];
        }
        //cout<<aux<<endl;
        ap[aux]++;
        if(k > maxi && ap[aux] >=2) maxi = k;
 
        lcp[invSuff[i]] = k; // lcp for the present suffix.
 
        // Deleting the starting character from the string.
        if (k>0)
            k--;
    }
 
    // return the constructed lcp array
    return lcp;
}
 
// Utility function to print an array
void printArr(vector<int>arr, int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}
 
// Driver program
int main()
{
    string str;
    int c;
    cin>>c;
    cin>>str;
    vector<int>suffixArr = Suffix_Array(str);
    int n = suffixArr.size();
 
    //cout << "Suffix Array : \n";
    //printArr(suffixArr, n); 
    vector<int>lcp = kasai(str, suffixArr);
 
    //cout << "\nLCP Array : \n";
    printArr(lcp, n);

    cout<<maxi<<'\n';
    return 0;
}