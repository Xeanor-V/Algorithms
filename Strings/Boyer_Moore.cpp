#include <bits/stdc++.h>
using namespace std;

// No_Chars = size of ABC
// Whole ascii this time for fun
int No_Chars = 256;

vector <int> BadChar(string pattern)
{
	vector <int> BC(No_Chars,-1);
	for(int i = 0 ; i < pattern.size() ;i++) BC[ pattern[i] ] = i;
	return BC;
}


int Bo_Mo(string text, string pattern)
{
	vector <int> BC = BadChar(pattern);

	int m = pattern.size();
	int index = 0;
	int count = 0;

	while(index <= text.size() - m)
	{
		int state = m-1;
		while(state >= 0 && pattern[state] == text[index + state]) state--;

		if(state < 0)
		{
			count++;

			index += (index + m < text.size())? m - BC[ text[index + m]] : 1;
		}
		else
		{
			index+= max(1, state - BC[text[state + index]]);
		}
	}

	return count;
}


int main()
{
	string text,pattern;
	cin>>text>>pattern;
	cout<< Bo_Mo(text,pattern) << endl;
	
}