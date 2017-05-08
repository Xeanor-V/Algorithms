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
	stack<int> estados;
	estados.push(0);
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
			estados.push(state);
			if(state == patttern.size()) // need to change if unique ocurrences
			{
				count++;
				for(int i = 0 ; i < patttern.size() ;i++) estados.pop();
				if(estados.size() == 0) estados.push(0);
				state = estados.top();
			}
		}

		else if( state > 0) state = F[state];

		else index++;
	}
	return count;
}



int main()
{

	string a,b;
	while(cin>>a>>b)
	{
		cout<<KMP(b,a)<<'\n';
	}
	
}