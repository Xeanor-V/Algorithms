#include <bits/stdc++.h>
using namespace std;

vector <int> Build_Failure(vector<char> pattern)
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

int KMP(vector<char> text, vector<char> patttern) // only counts matches
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
	int n,m;
	cin>>n>>m;
	vector<char> Ht,Hp;
	string aux;
	for(int i = 0 ; i < n ; i++)
	{
		cin>>aux;
		long long num = 0;
		for(int  j = 0 ; j < aux.size() - 2; j++) num= num*10 + (aux[j]-'0');

		//cout<<num<<endl;

		for(int j = 0 ; j < num ;j++) Ht.push_back(aux[ aux.size() -1]);

		
	}

	for(int i = 0; i < m; i++)
	{
		cin>>aux;
		long long num = 0;
		for(int  j = 0 ; j < aux.size() - 2; j++) num = num*10 + (aux[j]-'0');

		for(int j = 0 ; j < num ;j++) Hp.push_back(aux[ aux.size() -1]);
	}


	cout<<KMP(Ht,Hp)<<'\n';


}

