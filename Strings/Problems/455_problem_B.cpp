#include <bits/stdc++.h>
using namespace std;

struct Trie_Node
{
	Trie_Node *ABC[27]; 	//Standard ABC of lowercase letters.
	bool Is_Leaf;
	bool win;

	Trie_Node()
	{
		Is_Leaf = false;
		for(int i = 0 ; i < 27 ; i++) ABC[i] = NULL;
		win = false;
	}


							// 
	void insert(string key)
	{
		Trie_Node *Crawler = this;
		for(int i = 0 ; i < key.size(); i++)
		{
			if(Crawler -> ABC[key[i] - 'a'] == NULL)
			{
					Crawler -> ABC[key[i] -'a'] = new Trie_Node();
					Crawler -> ABC[key[i] - 'a'] -> win = !Crawler->win;
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

	bool move()
	{

	}


};



int main()
{
	Trie_Node *head = new Trie_Node();
	head->insert("aaa");
	head->insert("abcd");
	cout<<head->search("a")<<endl;
	cout<<head->search("aa")<<endl;
	cout<<head->search("aaa")<<endl;
	cout<<head->search("abcd")<<endl;
}