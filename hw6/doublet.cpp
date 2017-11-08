#include "functor.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc < 3)
	{
		cerr << "Not enough command line parameters" << endl;
		return 0;
	}

	ifstream ifile(argv[3]);

	if (ifile.fail())
	{
		cerr << "Please provide valid input file" << endl;
		return 0;
	}

	string beginWord = argv[1];
	string endWord = argv[2];

	int dictionaryLength;

	ifile >> dictionaryLength;

	// create adjacency list
	// string keys lead to an array of adjeacent words
	string word;
	map<string, vector<string> > theGraph;

	for (int i = 0; i < dictionaryLength; ++i)
	{
		// add words to the graph
		ifile >> word;
		vector<string> nada;
		theGraph.insert(std::pair<string, vector<string> > (word, nada));

		// iterate through all combinations of the word with one letter changed
		// check if those words are in the graph already
		// if so, add word to their adjacency list
		// also add the "misspelling" to word's adjacency list

		// create all misspellings of word
		string alphabet = "abcdefghijklmnopqrstuvwxyz";
		string misspelling;

		for (int i = 0; i < (int) word.size(); ++i)
		{
			// at each location of word
			for (int j = 0; j < 26; ++j)
			{
				misspelling = word.substr(0,i) + alphabet[j] + word.substr(i+1);
				// cout << misspelling << endl;
				if (misspelling != word && theGraph.count(misspelling) == 1)
				{
					theGraph[misspelling].push_back(word);
					theGraph[word].push_back(misspelling);
				}
			}
		}
	}

	// test the graph
	cout << "Adjacency List for " << argv[3] << endl << endl;

	map<string, vector<string> >::iterator it;
	for ( it = theGraph.begin(); it != theGraph.end(); ++it)
	{
		// goes through each node created
		cout << it->first << "'s adjacency list: ";
		for (int i = 0; i < (int) (it->second).size(); ++i)
		{
			cout << (it->second)[i] << " ";
		}
		cout << endl;
	}



	return 0;
}