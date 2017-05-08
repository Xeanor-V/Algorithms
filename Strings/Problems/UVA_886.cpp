#include <bits/stdc++.h>
using namespace std;

vector <int> Build_Failure(string pattern)
{
	vector <int> F(pattern.size()+1);
	F[0] = F[1] = 0; // Empty string and first preffix are always 0

	for(int i = 2 ; i <= pattern.size(); i++)
	{
		int j = F[i - 1]; // lets check if we can expand from the previous index of the partial match

		while(true)
		{
			if(pattern[j] == pattern[i -1]) // if our next character to match matches the first character of the suffix
			{								// then we haven found another common prefix/suffix
				F[i] = j + 1;
				break;
			}
			if(j == 0)		//if j still 0 that means that there wasn't a match at all
			{
				F[i] = 0;
				break;
			}
			j = F[j]; // lets check the next possible partial match to see if we can expand that one
		}
	}
	return F;
}

int KMP(string text, string patttern) // only counts matches
{
	vector <int> F = Build_Failure(patttern);

	int count = 0;
	int state = 0;
	int index = 0;
	while(true)
	{
		if(index == text.size()) break;

		if(text[index] == patttern[state] )
		{
			state++;
			index++;
			if(state == patttern.size()) // need to change if unique ocurrences
					count++;
		}

		else if( state > 0) state = F[state];

		else index++;
	}
	return count;
}

char tabla[26];

string convertir(string nombre, string  apellido)
{
	string aux = "";
	aux += tabla[tolower(nombre[0]) - 'a'];
	for(int i = 0 ; i < apellido.size() ;i++)
		aux+= tabla[tolower(apellido[i]) - 'a'];
	return aux;

}

bool matching(string text, string pat)
{
	int res = 0;
	for(int i = 0 ; i < pat.size() ; i++, res++) if(text[i] != pat[i]) return false;
	return true;
}



int main()
{
	tabla[0] = tabla[1] = tabla[2] = '2';
	tabla[3] = tabla[4] = tabla[5] = '3';
	tabla[6] = tabla[7] = tabla[8] = '4';
	tabla[9] = tabla[10] = tabla[11] = '5';
	tabla[12] = tabla[13] = tabla[14] = '6';
	tabla[15] = tabla[16] = tabla[17] = tabla[18]= '7';
	tabla[19] = tabla[20] = tabla[21] = '8';
	tabla[22] = tabla[23] = tabla[24] = tabla[25] = '9';
	set <string> apar;

	string a,b,ext;
	vector< pair<string,string> > numeros;
	vector <string> quer;
	while(cin>>a)
	{
		if(isalpha(a[0]))
		{
			cin>>b;
			cin>>ext;
			numeros.push_back( make_pair(convertir(a,b) , ext) );
			apar.insert(ext);
			//cout<<convertir(a,b)<<endl;
		}
		else
		{
			quer.push_back(a);
		}
	}

	for(int i = 0 ; i < quer.size() ; i++)
	{
		int maxi = 0;
		vector<int> res;
		set<string>::iterator it;
		it = apar.find(quer[i]);
		if(it != apar.end())
		{
			cout<<quer[i]<<'\n';
			continue;
		}
		else
		{
			for(int j = 0 ; j < numeros.size() ; j++)
			{
				bool count = matching(numeros[j].first, quer[i]);
				if(count)
				{
					res.push_back(j);
				}
			}
		}

		if(res.size() == 0) cout<<0;
		else
		{
			for(int j = 0 ; j < res.size() ; j++)
			{
				if(j == 0) cout<<numeros[res[j]].second;
				else cout<<' '<<numeros[res[j]].second;
			}
		}
		cout<<'\n';
	}

	
}