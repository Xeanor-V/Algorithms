#include <bits/stdc++.h>
using namespace std;

long long B = 33; // Size of Alphabet
long long M = 512927377; //A  big prime

long long int_mod(long long a, long long b) // Calculates mod even if a < 0
{
	return ( a % b + b) % b;
}




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
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	string a;
	cin>>a;
	long long Hp = 0,Hs = 0;
	string aux = "";
	for(int i = 0 ; i < a.size() ; i++)
	{
		Hp = int_mod(Hp*B + a[i],M );
		Hs = int_mod(Hp*B + a[a.size()  - 1 - i],M );
		if(Hp != Hs) break;

		aux = aux + a[i];
		
	}
	

	sort(res.begin(), res.end());
	cout<<res.size()<<'\n';
	for(auto v : res) cout<<v.first<<' '<<v.second<<'\n';

	return 0;
}