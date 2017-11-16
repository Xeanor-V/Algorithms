#include "Strings.hpp"
using namespace std;

// String multi matching
/*
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	while(cin>>n)
	{
		cin.ignore();
		vector<string> words(n);
		for(int i = 0; i < n; i++)
			getline(cin,words[i]);

		
		string text;
		getline(cin,text);
		vector< vector<int> > res = searchWords(words,text);
		for(int i = 0 ; i < res.size(); i++)
		{
			for(int j = 0 ; j < res[i].size(); j++)
			{
				if(j) cout<<' ';
				cout<<res[i][j];
			}
			cout<<'\n';
		}
	}	
}//*/

/*
// String matching
int main()
{
	string text,pattern;
	while(getline(cin,pattern))
	{
		getline(cin,text);
		vector<int> res = KMP(text,pattern);
		for(int i = 0 ; i < res.size(); i++)
		{
			if(i) cout<<' ';
			cout<<res[i];
		}
		cout<<'\n';
	}
	return 0;
	
}
//*/

// Suffix sorting
int main()
{
	string a;
	while(getline(cin,a))
	{
		map<int,int> res = Suffix_Sort(a);
		int n;
		cin>>n;
		for(int i = 0 ; i < n; i++)
		{
			int q;
			cin>>q;
			if(i) cout<<' ';
			cout<<res[q];
		}
		cout<<'\n';
		getchar(); 		
	}
	return 0;
}
//*/