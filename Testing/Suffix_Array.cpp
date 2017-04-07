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

int Suffix_Array(string s)
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
	return step;

}

int main()
{
	string a;
	cin>>a;
	int step = Suffix_Array(a);

	for(int i = 0 ; i < step; i++)
	{
		for(int j = 0 ; j < a.size(); j++)
			cout<<sortIndex[i][j]<<' ';
		cout<<'\n';
	}
	return 0;
}