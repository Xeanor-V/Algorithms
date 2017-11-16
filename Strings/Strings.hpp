#include <bits/stdc++.h>
using namespace std;

////*/////
// Aho corasick algorithm for string multi matching //

	// Maximum number of states
	const int maxStates = 200105;
 
	// Maximum number of characters in input alphabet
	const int dictionarySize = 257;

	set<int> out[maxStates];
 
	// Back edges
	int failure[maxStates];
 
	// goTo acts like standard TRIE
	int goTo[maxStates][dictionarySize];

	// Creates Trie - with back edges
	int build(vector <string> words)
	{
		for(int i = 0 ; i < maxStates; i++) out[i].clear();
 		memset(failure, -1, sizeof failure);
   		memset(goTo, -1, sizeof goTo);
 
		int states = 1;

		// Creates normal trie and mark leafs in output set
		for(int i = 0; i < words.size(); i++)
		{
			string word = words[i];
			int currentState = 0;
			for(int j = 0; j < word.size(); j++)
			{
				int ch = word[j];
				if(goTo[currentState][ch] == -1)
					goTo[currentState][ch] = states++;
				currentState = goTo[currentState][ch];
			}
			out[currentState].insert(i);
		}

		// Set root to itself
		for (int ch = 0; ch < dictionarySize; ch++)
        	if(goTo[0][ch] == -1)
            	goTo[0][ch] = 0;

        queue<int> q;

        // Strings of size 1 always have failure to root
        for(int ch = 0 ; ch < dictionarySize; ch++)
        {
        	if(goTo[0][ch] != 0)
        	{
        		failure[ goTo[0][ch] ] = 0;
        		q.push(goTo[0][ch]);
        	}
        }

        // Fill up fail edges by doing BFS
        while (q.size())
    	{
	        int state = q.front();
	        q.pop();
	        // For the removed state, find fail function for
	        // all those characters for which goto function is
	        // not defined.
	        for (int ch = 0; ch <= dictionarySize; ++ch)
	        {
	            // If goto function is defined for character 'ch'
	            // and 'state'
	            if (goTo[state][ch] != -1)
	            {
	                // Find fail state of removed state
	                int X = failure[state];
	                // Find the deepest node labeled by proper
	                // suffix of string from root to current
	                // state.
	                while (goTo[X][ch] == -1)
	                      X = failure[X];
	 
	                X = goTo[X][ch];
	                failure[goTo[state][ch]] = X;
	                // Merge output values
	                out[goTo[state][ch]].insert(out[X].begin(), out[X].end());
	                q.push(goTo[state][ch]);
            	}
        	}
    	}
        return states;
	}

	// Returns the next state the machine will transition to using goto
	// and failure functions.
	int findNextState(int currentState, char nextInput)
	{
	    int answer = currentState;
	    int ch = nextInput;
	 
	    // If goto is not defined, use failure function
	    while (goTo[answer][ch] == -1)
	        answer = failure[answer];
	 
	    return goTo[answer][ch];
	}

	// This function finds all occurrences of all array words
	// in text.
	vector< vector<int> > searchWords(vector<string> words, string text)
	{
	    // Preprocess patterns.
	    // Build machine with goto, failure and output functions
		build(words);
	    // Initialize current state
	    int currentState = 0;
	 	vector< vector<int> > appears(words.size()); 
	    // Traverse the text through the nuilt machine to find
	    // all occurrences of words in arr[]
	    for (int i = 0; i < text.size(); ++i)
	    {
	        currentState = findNextState(currentState, text[i]);
	        // If match not found, move to next state
	        if (out[currentState].size() == 0)
	             continue;
	 		
	 		// If theres a match found ladded to the results;
	        for(auto iter = out[currentState].begin(); iter != out[currentState].end(); iter++)
	        {
	        	int word = *iter;
	        	appears[word].push_back(i - words[word].size() + 1);
	        }
	    }
	    return appears;
	}
////*/////

// Suffix sorting //

const int maxN = 100005;


struct Tuple
{
	int indxs[2];
	int pos;
};

int cmp(Tuple a,Tuple b) // Check tuples current step and next one to give sorting index.
{
	return (a.indxs[0] == b.indxs[0]) ? (a.indxs[1] < b.indxs[1]?1:0) : (a.indxs[0] < b.indxs[0]?1:0);
}


int sortIndex[500][maxN];

map<int,int> Suffix_Sort(string s)
{
	memset(sortIndex, 0 , sizeof(sortIndex));
	Tuple L[maxN];

	for(int i = 0 ; i < s.size() ; i++) //let's get all suffixes, we only need the first letter later we can form everyone based on this.
		sortIndex[0][i] = s[i] ;//-'a';

	int done_till = 1, step = 1;
	int N = s.size();

	for(;done_till < N; step++, done_till*=2) // 2 step jump and till we have gone through all the string, also keep track of steps.
	{

		for(int i = 0 ; i < N ; i++) //Lets rearm the Tuple
		{
			L[i].indxs[0] = sortIndex[step - 1][i]; // last SI is the current one
			L[i].indxs[1] = ( i + done_till ) < N? sortIndex[step-1][i + done_till]:-1; // next one is calculated using another previously 																				
			L[i].pos = i; // lets get new position                                         calculated SI of another suffix or if size too big -1
		}

		sort(L, L + N, cmp); // sorting tuples
			
		for(int i = 0 ; i < N; i++) //Lets calculate the new SI
		{
			sortIndex[ step ][ L[i].pos ] = i > 0 && L[i].indxs[0] == L[i - 1].indxs[0] && L[i].indxs[1] == L[i - 1].indxs[1] ? 
									sortIndex[ step ][ L[i-1].pos ] : i;
		}
		// after the sort the first one stays the same, now if it has the same values as i-1 it gets the same SI, if not then i (new SI)
	}
	//return step;
	map<int,int> res;
	for(int i = 0 ; i < s.size(); i++) res[sortIndex[step-1][i]] = i;
	return res;

}

////*/////

 // KMP //

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

vector<int> KMP(string text, string pattern) // returns position of ocurrences. 
{
	vector <int> F = Build_Failure(pattern);
	vector <int> res;
	int count = 0;
	int state = 0;
	int index = 0;
	while(true)
	{
		if(index == text.size()) break;

		if(text[index] == pattern[state] )
		{
			state++;
			index++;
			if(state == pattern.size()) // need to change if unique ocurrences
					res.push_back(index-pattern.size());
		}

		else if( state > 0) state = F[state];

		else index++;
	}
	return res;
}

////*////