#include <bits/stdc++.h>
using namespace std;

// No_Chars = size of ABC
// Whole ascii this time for fun
int No_Chars = 256;

vector <int> BadChar(string pattern) // Bad Char Heuristic / find the last ocurrence of character
{
	vector <int> BC(No_Chars,-1);
	for(int i = 0 ; i < pattern.size() ;i++) BC[ pattern[i] ] = i;
	return BC;
}


int Bo_Mo(string text, string pattern) // Heuristic search O(n/m)
{
	vector <int> BC = BadChar(pattern); // pre - pro

	int m = pattern.size();
	int index = 0;
	int count = 0;

	while(index <= text.size() - m)
	{
		int state = m-1;
		while(state >= 0 && pattern[state] == text[index + state]) state--; // matching 

		if(state < 0) // if we get a full match on the substr
		{
			count++; // Shift the string till the best ocurrence of the next char if not existing
			index += (index + m < text.size())? m - BC[ text[index + m]] : 1; // -1 we skip that char
		}																	  // also cool!	
		else
		{ // if failed then we shift the pattern till the next ocurrence in the pattern of the
			index+= max(1, state - BC[text[state + index]]); // char that failed and try again
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