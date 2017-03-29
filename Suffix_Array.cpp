#include <bits/stdc++.h>
using namespace std;


const int maxN = 20;


struct tuple
{
	int indxs[2];
	int pos;
}L[maxN];

int cmp(struct tuple a, struct tuple b)
{
	return (a.indxs[0] == b.indxs[0]) ? (a.indxs[1] < b.indxs[1]?1:0) : (a.indxs[0] < b.indxs[0]?1:0);
}


int sortIndex[5000][maxN];

int Suffix_Array(string s)
{
	for(int i = 0 ; i < s.size() ; i++)
		sortIndex[0][i] = s[i] -'a';

	int done_till = 1, step = 1;
	int N = s.size();

	for(;done_till < N; step++, done_till*=2)
	{

		for(int i = 0 ; i < N ; i++)
		{
			L[i].indxs[0] = sortIndex[step - 1][i];
			L[i].indxs[1] = ( i + done_till ) < N? sortIndex[step-1][i + done_till]:-1;
			L[i].pos = i;
		}

		sort(L, L + N, cmp);

		for(int i = 0 ; i < N; i++)
		{
			sortIndex[ step ][ L[i].pos ] = i > 0 && L[i].indxs[0] == L[i - 1].indxs[0] && L[i].indxs[1] == L[i - 1].indxs[1] ? 
									sortIndex[ step ][ L[i-1].pos ] : i;
		}

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