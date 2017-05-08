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
			j = F[j]; // lets check the next possible partial match to see if we can expand that one
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
			if(state == patttern.size())
			{
				count++;
				state = 0;
			}
		}

		else if( state > 0) state = F[state];

		else index++;
	}
	return count;
}



int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		string a;
		cin>>a;
		vector<int> factor;
		for(int i = 1 ; i <= ( sqrt(a.size()) ); i++) 
		{
			if( a.size() % i ==0 ) 
			{
					factor.push_back(i);
					if( a.size() / i != i) factor.push_back(a.size()/i);
			}
		}
		int mini = 1<<30;
		for(int i = 0 ; i < factor.size(); i++)
		{
			string aux = a.substr(0,factor[i]);

			int count = KMP(a,aux);
			int n = aux.size();
			int m = a.size();
			if(m / n == count)
			{
				mini = min(mini, n );
			}
		}
		cout<<mini<<'\n';
		if(t>=1) cout<<'\n';
	}
	return 0; 	
	
}