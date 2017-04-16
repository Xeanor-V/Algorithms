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

int main()
{
	string s;
	cin>>s;
	vector<int> Z = build_Z(s);

	int maxZ = 0, pos = 0;
	for(int i  = 1 ; i < Z.size(); i++)
	{
		if(Z[i] == s.size() - i && maxZ >= s.size()-i)
		{
			pos = i;
			break;	
		}
		maxZ = max(maxZ,Z[i]);
	}
	if(pos == 0)
	{
		cout<<"Just a legend\n";
		return 0;
	}

	for(int i = pos; i < s.size(); i++) cout<<s[i];
	cout<<'\n';
}