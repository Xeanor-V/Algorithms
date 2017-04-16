#include <bits/stdc++.h>
using namespace std;

vector <int> build_Z(string text)
{
	int l,r;
	vector <int> Z(text.size());
	Z[0] = 0;
	l = r = 0;
	for(int i = 1; i < text.size(); i++)
	{
		if(i > r)
		{
			l = r = i;

			while( r < text.size() && text[r - l] == text[r] ) r++;
			Z[i] = (r - l);
			r--;
		}
		else
		{	
			int k = i - l;

			if(Z[k] < (r - i + 1)) Z[i] = Z[k];
			else
			{
				l = i;
				while( r < text.size() && text[r - l] == text[r] ) r++;
				Z[i] = (r - l);
				r--;
			}
		}

	}
	return Z;
}

vector <int> search(string text, string pattern)
{
	text = pattern + '&' + text; // change sentinel if is included in dictionary;
	vector<int> Z = build_Z(text);
	vector<int> res;
	for(int i = 0 ; i < Z.size();i++) 
		if(Z[i] == pattern.size()) 
			res.push_back(i - pattern.size() -1); 	// This can be optimized by putting this inside build_Z
		return res;										// but i decided to leave build_Z as vanilla 
}

int main()
{
	string a,b;
	cin>>a>>b;
	vector<int> res = search(a,b);
	
	cout<<"Matches: "<<res.size()<<'\n';
	cout<<"Positions: ";
	for(int i = 0 ; i < res.size(); i++) cout<<res[i]<<' ';
	cout<<'\n';
	return 0;
}