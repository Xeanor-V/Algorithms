#include <bits/stdc++.h>
using namespace std;

struct Trie_Node
{
	Trie_Node *ABC[27]; 	//Standard ABC of lowercase letters.
	bool Is_Leaf;
	int count;

	Trie_Node()
	{
		Is_Leaf = false;
		count = 0;
		for(int i = 0 ; i < 27 ; i++) ABC[i] = NULL;
	}


							// 
	void insert(string key)
	{
		Trie_Node *Crawler = this;
		for(int i = 0 ; i < key.size(); i++)
		{
			if(Crawler -> ABC[key[i] - 'a'] == NULL) 
			{
				Crawler -> count++;
				Crawler -> ABC[key[i] -'a'] = new Trie_Node();
			}
			Crawler = Crawler -> ABC[key[i] - 'a'];
		}
		Crawler -> Is_Leaf = true;
		
	}

	bool search(string key)
	{
		Trie_Node *Crawler = this;
		for(int i = 0 ; i < key.size(); i++)
		{
			if(Crawler -> ABC[key[i] - 'a'] == NULL) return false;
			Crawler = Crawler -> ABC[key[i] - 'a'];
		}
		return Crawler -> Is_Leaf;	

	}

	long long Conex_Search(string key)
	{
		long long count = 0;

		Trie_Node *Crawler = this;

		cout<<key<<endl;
		for(int i = 0 ; i < key.size()-1 ; i++)
		{
			if(Crawler -> count > 1) 
			{	count++;
				cout<<key[i]<<endl;
			}
			else if((Crawler -> Is_Leaf ))//&& i+1 < key.size()))
			{
				count++;
				cout<<"HERE "<<key[i]<<endl;
			}

		//	cout<<key.substr(0,i+1)<<' '<<Crawler -> Is_Leaf <<' '<<Crawler -> count<<endl;
			Crawler = Crawler -> ABC[key[i] - 'a'];
		}
		count = (count == 0?1:count);
		cout<<"Count: "<<count<<endl<<endl;
		return count;
	}


};



int main()
{

	Trie_Node *head = new Trie_Node();

	int N;
	cin>>N;
	string aux;
	vector<string> pal;
	for(int i = 0 ; i < N ; i++)
	{
		cin>>aux;
		head -> insert(aux);
		pal.push_back(aux);
	}
	
	double res = 0;

	for(int i = 0 ; i < N; i++)
	{
		res+= head -> Conex_Search(pal[i]);
	}

	cout<<fixed<<setprecision(2)<<res/N<<'\n';
	return 0;
}