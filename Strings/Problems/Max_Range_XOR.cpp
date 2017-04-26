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


	long long Query_XOR(string Y)
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
		long long res = 0;
		for(int i = 0 ; i < aux.size() ; i++)
		{
			if(aux[i] == '1') res = (res | (1<<(aux.size() - (i+1) )) );
		}
		return res;
	}
};



string int_to_bin(long long n, int NB)
{
	string aux = "";
	for(int i = NB; i >=0; i--)
	{
		if(n & (1<<i)) aux+="1";
		else aux+="0";
	}
	return aux;
}

//Obtaining maximun xor from all contiguos subarrays of an array
// N for size of set
// Y for upperbound of XOR


int num_bits(long long n)
{
	int res = 0;
	while(n)
	{
		n/=2;
		res++;
	}
	return res;
}

int main()
{
	//cout<<num_bits(100000)<<endl;
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int N, T;
	cin>>T;
	while(T--)
	{
		Trie_Node *head = new Trie_Node('0');
		cin>>N;
		long long maxN = 0;
		vector<long long> num(N);
		for(int i = 0 ; i < N ; i++)
		{
			cin>>num[i];
			maxN = max(maxN, num[i]);
		}
		maxN = num_bits(maxN); // find minimun number of bits for all numbers
		long long ans = 0;
		long long pre = 0;
		head -> insert( int_to_bin(0,maxN));
		for(int i = 0 ; i < N; i++)
		{
			pre = pre ^ num[i];
			string aux = int_to_bin(pre,maxN);
			ans = max(ans, head -> Query_XOR(aux));
			head -> insert(aux);
		}
		cout<<ans<<'\n';
	}
	return 0;

}
/*

2  
5  
3  7  7  7  0  
5  
3  8  2  6  4

*/



