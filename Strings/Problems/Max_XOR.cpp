#include <bits/stdc++.h>
using namespace std;

struct Trie_Node
{
	Trie_Node *ABC[27];
	bool Is_Leaf;
	char value;

	Trie_Node(char a)
	{
		Is_Leaf = false;
		for(int i = 0 ; i < 27 ; i++) ABC[i] = NULL;
		value = a;
	}


	//Standard ABC of lowercase letters.
	void insert(string key)
	{
		Trie_Node *Crawler = this;
		for(int i = 0 ; i < key.size(); i++)
		{
			if(Crawler -> ABC[key[i] - '0'] == NULL) Crawler -> ABC[key[i] -'0'] = new Trie_Node(key[i] - '0');
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


	int Query_XOR(string Y)
	{
			string aux ="";
			Trie_Node *Crawler = this;
			for(int i = 0 ; i < Y.size() ; i++) // Greedy approach, if we want to maximimize XOR we look for the bit
			{									// that will leave us a 1 in that position of the output
				if(Y[i] == '1')					//if we have a 1 in Y then we look for a 0 and viceversa for maximize
				{								//since all numbers are fixed bit size we will never leave the max Pos.
					if(Crawler -> ABC[0])
					{
						aux+="1";
						Crawler = Crawler ->ABC[0];
					}
					else
					{
						aux+="0";
						Crawler = Crawler -> ABC[1];
					}
				}
				else
				{
					if(Crawler -> ABC[1])
					{
						aux+="1";
						Crawler = Crawler ->ABC[1];
					}
					else
					{
						aux+="0";
						Crawler = Crawler -> ABC[0];
					}

				}
			}
		int res = 0;
		for(int i = 0 ; i < aux.size() ; i++)
		{
			if(aux[i] == '1') res = (res | (1<<(aux.size() - (i+1) )) );
		}
		return res;
	}
};

//Obtaining maximun xor from group of numbers
// N for size of set
// Y for upperbound of XOR

int main()
{
	Trie_Node *head = new Trie_Node('0');

	
	int N, Y;
	
	cin>>N>>Y;
	int maxN = Y;
	vector<int> num(N);
	for(int i = 0 ; i < N ; i++)
	{
		cin>>num[i];
		maxN = max(maxN, num[i]);
	}
	maxN = log2(maxN); // find minimun number of bits for all numbers
	string aux;
	for(int i = 0 ; i < N; i++) // convert to binary every number
	{
		aux = "";
		for(int j = maxN; j>=0; j--)
		{
			if(num[i] & 1<<j) aux+="1";
			else aux += "0";
		
		}
		head -> insert(aux);
	}
	aux ="";
	for(int i = maxN ; i>=0; i--) // Y to binary
	{
		if(Y & 1<<i) aux+="1";
			else aux += "0";
	}
	cout<<head -> Query_XOR(aux)<<endl;
	return 0;

}