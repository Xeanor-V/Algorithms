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

int KMP(string text, string patttern) // only counts ocurrrences, modify to obtain locations (easy come on)
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

int memo[100][100];

int dp(int pos1, int pos2, string a, string b)
{
	if(pos1 == a.size() || pos2 == b.size()) return 0;
	if(memo[pos1][pos2]) return memo[pos1][pos2];
	int res1 = 0;

	if(a[pos1] == b[pos2]) return memo[pos1][pos2] = dp(pos1+1,pos2+1,a,b) +1;


	return memo[pos1][pos2] = max( dp(pos1+1,pos2,a,b) , dp(pos1,pos2+1,a,b));

}




int main()
{
	//cout<<KMP("ABBA","ABA")<<endl;
	cout<<dp(0,0,"ABCD","ZBCDZ")<<endl;
	return 0;
	
}