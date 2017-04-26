#include <bits/stdc++.h>
using namespace std;

vector <int> Build_Failure(string pattern)
{
	vector <int> F(pattern.size()+1);
	F[0] = F[1] = 0; // Empty string and first preffix are always 0

	for(int i = 2 ; i <= pattern.size(); i++)
	{
		int j = F[i - 1]; // lets check if we can expand from the previous index of the partial match

		while(true)
		{
			if(pattern[j] == pattern[i -1]) // if our next character to match matches the first character of the suffix
			{								// then we haven found another common prefix/suffix
				F[i] = j + 1;
				break;
			}
			if(j == 0)		//if j still 0 that means that there wasn't a match at all
			{
				F[i] = 0;
				break;
			}
			j = F[i]; // lets check the next possible partial match to see if we can expand that one
		}
	}
	return F;
}

int KMP(string text, string patttern) // only counts matches
{
	vector <int> F = Build_Failure(patttern);

	int count = 0;
	int state = 0;
	int index = 0;
	while(true)
	{
		if(index == text.size()) break;

		if(text[index] == patttern[state] )
		{
			state++;
			index++;
			if(state == patttern.size()) count++;
		}

		else if( state > 0) state = F[state];

		else index++;
	}
	return count;
}



int main()
{
	//cin.tie(0);
	//ios_base::sync_with_stdio(0);
	string s;
	while(cin>>s)
	{
		if(s == ".") break;
		
		vector<int> factor;
		for(int i = 1 ; i <= ( sqrt(s.size()) ); i++) 
		{
			if( s.size() % i ==0 ) 
			{
					factor.push_back(i);
					if( s.size() / i != i) factor.push_back(s.size()/i);
			}
		}

		sort(factor.begin(), factor.end());
		//for(int i = 0 ; i < factor.size() ;i++) cout<<factor[i]<<'\n';

		int maxi = 0;
		for(int i = factor.size() - 1; i >=0 ;i--)
		{
			string aux = s.substr(0,factor[i]);
			int count = KMP(s,aux);
			//cout<<factor[i]<<endl;
			if(count == s.size()/factor[i])
			{
					int n = s.size()/factor[i];
					maxi = max(maxi,n);
			}
		}		
		cout<<maxi<<'\n';
	}
	return 0;
	
}