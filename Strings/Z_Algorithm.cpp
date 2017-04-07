#include <bits/stdc++.h>
using namespace std;

vector <int> build_Z(string text)
{
	int l,r;
	vector <int> Z(text.size());
	Z[0] = 0;
	for(int i = 1 , l = 0, r = 1; i < text.size(); i++)
	{
		if(text[r] != text[l])
		{
			Z[i] = (r - l + 1) + Z[i-1];
			l = 0;
			r = 0;

		}
		else
		{
			l++;
			r++;
		}

	}
	Z[0] = -1;
	return Z;
}

int main()
{
	string a;
	cin>>a;
	vector<int> Z = build_Z(a);
	cout<<a<<endl;
	for(int i = 0 ; i < Z.size() ; i++)
		cout<<Z[i]<<' ';
	return 0;
}