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

int KMP(string text, string patttern) // only counts ocurrrences, modify to obtain locations (easy come on)
{
	vector <int> F = Build_Failure(patttern);

	int count = 0;
	int state = 0;
	int index = 0;
	int res = 0;
	int pos = 0;
	bool flag = false;
	while(index < text.size())
	{

		if(text[index] == patttern[state] )
		{
			state++;
			index++;
			if(res < state)
			{
				res = state;
				pos = index-state;
				//cout<<res<<' '<<pos<<endl;
			}	
			if(state == patttern.size()) count++;
		}

		else if( state > 0) state = F[state];

		else index++;
	}
	return pos;
}

int main()
{
	int n;
	cin>>n;
	string a,b;
	cin>>a>>b;
	b = b+b;
	cout<<KMP(b,a)<<endl;
	return 0;
}