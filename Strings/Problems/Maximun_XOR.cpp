#include <bits/stdc++.h>
using namespace std;

struct Trie_Node
{
	Trie_Node *ABC[27]; 	//Standard ABC of numbers.
	bool Is_Leaf;

	Trie_Node()
	{
		Is_Leaf = false;
		for(int i = 0 ; i < 27 ; i++) ABC[i] = NULL;
	}


							// 
	void insert(string key) // change '0' for sentinel of ABC
	{
		Trie_Node *Crawler = this;
		for(int i = 0 ; i < key.size(); i++)
		{
			if(Crawler -> ABC[key[i] - '0'] == NULL) Crawler -> ABC[key[i] -'0'] = new Trie_Node();
			Crawler = Crawler -> ABC[key[i] - '0'];
		}

		Crawler -> Is_Leaf = true;
		
	}

	bool search(string key)
	{
		Trie_Node *Crawler = this;
		for(int i = 0 ; i < key.size(); i++)
		{
			if(Crawler -> ABC[key[i] - '0'] == NULL) return false;
			Crawler = Crawler -> ABC[key[i] - '0'];
		}
		return Crawler -> Is_Leaf;	

	}

	string Max_XOR(string value)
	{

	}


};



int main()
{
	Trie_Node *head = new Trie_Node();
	int N,Y;
	cin>>N>>Y;
	int maxi = 0;
	vector<int> num(N);
	for(int i = 0 ; i < N; i++)
	{
		cin>>num[i];
		maxi = max(maxi, num[i] );
	}
	maxi = max(maxi,Y);

	maxi =  (log2(maxi) + 1);
	//cout<<maxi<<endl;

	for(int i = 0 ; i < N; i++)
	{
		string aux = "";
		for(int j = 0; j < maxi; j++)
		{
			if(num[i] & (1<<j)) aux+='1';
			else aux+='0';
		}
		//cout<<aux<<endl;
		head -> insert(aux);
	}

	int res = 0;


	return 0;

}