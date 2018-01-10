#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <locale>

using namespace std;


void createAdjacencyList(map<string, vector<string> >& theGraph,
	int dictionaryLength, ifstream& ifile, string begin);

bool findShortestPath(map<string, vector<string> >& theGraph, string start,
	string end, map<string, int>& distances, map<string, string>& predecesors,
	int& expansions);

struct myComparison {
	bool operator() (const pair<int, string>& lhs, const pair<int, string>& rhs);
};

bool myComparison::operator() (const pair<int, string>& lhs,
 const pair<int, string>& rhs)
{
	 	if (lhs.first != rhs.first)
	 	{
	 		return lhs.first > rhs.first;
	 	}
	 	else 
	 	{
	 		return lhs.second > rhs.second;
	 	}
	 	return false;
}

string makeLower(string word)
{
	locale loc;
	for (int i = 0; i < (int) word.size(); ++i)
	{
		word[i] = tolower(word[i], loc);
	}
	return word;
}

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
	beginWord = makeLower(beginWord);
	string endWord = argv[2];
	endWord = makeLower(endWord);

	int dictionaryLength;

	ifile >> dictionaryLength;

	map<string, vector<string> > theGraph;


	// create adjacency list
	// string keys lead to an array of adjeacent words
	createAdjacencyList(theGraph, dictionaryLength, ifile, beginWord);

	map<string, int> distances;
	map<string, string> predecesors;

	// find the shortest path
	int expansions = 0;
	bool didFindPath = findShortestPath(theGraph, beginWord, endWord, distances,
	 predecesors, expansions);

	// check if predecessors are correct
	/*
	map<string, string>::iterator it;
	for (it = predecesors.begin(); it != predecesors.end(); it++)
	{
		cout << (*it).first << "'s predecesor is " << (*it).second << endl;
	}
	// output the result!
	int expansions = 0;
	string onWord = endWord;
	while(onWord != beginWord)
	{
		cout << onWord << endl;
		onWord = predecesors[onWord];
		expansions++;
	}

	cout << beginWord << endl;
	*/

	// determine the list of transformations based on predecessors
	vector<string> result;
	int path = 0;
	string onWord = endWord;
	while(onWord != beginWord &&didFindPath)
	{
		result.push_back(onWord);
		onWord = predecesors[onWord];
		path++;
	}
	result.push_back(beginWord);

	// output the predecessors in reverse order (begining to end)
	vector<string>::iterator it;
	for (it = result.end(), it--; it != result.begin(); it--)
	{
		cout << (*it) << endl;
	}
	if (didFindPath)
	{
		cout << endWord << endl;
	}
	else
	{
		cout << "No transformation" << endl;		
	}

	// overcounts the last word by one
	expansions--;
	cout << "expansions = " << expansions << endl;


	return 0;
}


void createAdjacencyList(map<string, vector<string> >& theGraph,
	int dictionaryLength, ifstream& ifile, string begin)
{
	string word;
	for (int i = 0; i < dictionaryLength; ++i)
	{
		// add words to the graph
		ifile >> word;
		word = makeLower(word);

		if (word.size() == begin.size())
			{
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
	}

	// test the graph
	/*
	cout << "Adjacency List" << endl;

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

	cout << endl;
	*/

	
}


bool findShortestPath(map<string, vector<string> >& theGraph, string start,
 string end, map<string, int>& distances, map<string, string>& predecesors,
 int& expansions)
{
	// keep track of the number of expansions so far
	// increment every time you remove the min value
	// from the min heap (priority queue?)
	// The starting word should increment the number
	// of expansions (from 0 to 1), but the ending
	// word should not.
	// int expansions = 0;

	// distances are all infinite?
	set <string> beenChecked;

	// create priority queue of pairs
	// myComparison comp; // greater<pair<int, string> >
	// greater is a stl comparator
	priority_queue< pair<int, string> , vector <pair<int, string> >,
	 greater<pair<int, string> > > pq;

	// first value is distance, second is value (string)
	// place starting word in the queue (distance = 0)
	pq.push(make_pair(0, start));
	distances[start] = 0;
	beenChecked.insert(start);

	// itterate through priority queue until it is empty
	while (!pq.empty())
	{
		// remove smallest distance word from priority, u
		expansions++;
		string u = pq.top().second;
		int uWeight = pq.top().first;
		pq.pop();
		// cout << "removed " << u << " from priority queue" << endl;

		// check if you have found the end word
		if (u == end)
		{
			// cout << "found end word" << endl;
			return true;
		}

		// look though all words adjacent to u
		vector<string> uAdjacent = theGraph[u];
		vector<string>::iterator it;

		for (it = uAdjacent.begin(); it != uAdjacent.end(); it++)
		{
			// each adjacent word is "v"			
			string v = (*it);
			int vWeight = uWeight + 1;
		
			// if u provides a shorter path to v than
			// recorded path, or v has not been discovered
			// aka infinite distance
			if (beenChecked.count(v) == 0 || distances[v] > vWeight)
			{
				// update the distance of v
				// insert v into priority queue (will update value)
				beenChecked.insert(v);
				distances[v] = vWeight;
				predecesors[v] = u;
				// determine heuristic
				int heuristic = 0;
				// count differences between end word and v
				for (int i = 0; i < (int) end.size(); ++i)
				{
					if (end[i] != v[i])
					{
						heuristic++;
					}
				}
				int f = heuristic + vWeight;
				int n = (int) v.size();
				int prioWeight = (f * (n-1)) + heuristic;

				pq.push(make_pair(prioWeight, v));

				//expansions++;
			}
			// beenChecked.insert(v);
		}
	}

	return false;
}
