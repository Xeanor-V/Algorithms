#include <bits/stdc++.h>
using namespace std;

long long B = 31; // Size of Alphabet
long long M = 123891739; //A  big prime

long long int_mod(long long a, long long b) 
{
	return ( a % b + b) % b;
}

vector <long long int> prefix_hashes(string s)
{
	vector <long long int> res;
	long long int Hp = 0;
	for(int i = 0 ; i < s.size() ; i++) 
	{
		Hp = int_mod(Hp * B +  s[i], M);
		res.push_back(Hp);
	}
	return res;
} 


vector <long long int> substring_hashes(vector< pair<int,int> > ranges, string s)
{
	vector <long long int> p_hashes = prefix_hashes(s);
	vector <long long int> B_powers;
	vector <long long int> res;
	B_powers.push_back(1);
	for(int i = 1 ; i < s.size(); i++)
	{
		B_powers.push_back( int_mod(B * B_powers[i-1],M) ) ;
	}
	for(int i = 0 ; i < ranges.size(); i++)
	{
		int left_hash = 0, right_hash = p_hashes[ranges[i].second];
		if(ranges[i].first-1 >= 0)
			left_hash = p_hashes[ranges[i].first-1];
		res.push_back( int_mod( right_hash - left_hash * B_powers[ranges[i].second - ranges[i].first + 1], M )  );
	}
	return res;
}

int main()
{
	string s;
	cin>>s;
	int n;
	cin>>n;
	vector <pair <int,int> > ranges;
	for(int i = 0 ; i < n; i++)
	{
		int a,b;
		cin>>a>>b;
		ranges.push_back(make_pair(a,b-1));
	}
	vector<long long int> res = substring_hashes(ranges, s);
	for(int i = 0; i < res.size(); i++)
	cout<<res[i]<<'\n';
	return 0;
}