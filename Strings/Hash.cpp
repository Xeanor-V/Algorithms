#include <bits/stdc++.h>
using namespace std;

long long B = 26; // Size of Alphabet
long long M = 512927377; //A  big prime

long long int_mod(long long a, long long b) // Calculates mod even if a < 0
{
	return ( a % b + b) % b;
}


bool Rolling_Hash(string text, string pattern) // Rabin - Karp Algorithm 
{
	if( text.size() < pattern.size() ) return false;

	long long Hp = 0, Ht = 0, m = pattern.size();
	for(int i = 0 ; i < m ; i++) // Hash of pattern X First Hash of text
	{
		Hp = int_mod(Hp * B +  pattern[i], M);
		Ht = int_mod(Ht * B + text[i], M);
	}

	if(Hp == Ht) return true;

	for(int i = m; i < text.size(); i++) // Rolling hash
	{
		Ht = int_mod( Ht - int_mod(text[i-m] * int_mod( pow(B,m-1), M ), M ), M);
		Ht = int_mod( Ht * B , M);
		Ht = int_mod( Ht + text[i], M);

		if(Ht == Hp) return true;
	}
	return false;
}


int main()
{
	string a,b;
	cin>>a>>b;
	cout<< Rolling_Hash(a,b) << '\n';
	return 0;

}