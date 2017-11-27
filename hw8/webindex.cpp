#include "TrieSet.h"
#include "BloomFilter.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void testBloomFilter(BloomFilter* bloom, vector<string>& queries, ofstream& out);
void populateBloomFilter(BloomFilter* &bloom, vector<string>& webpages);
void testTrie(TrieSet* &trie, vector<string>& queries, ofstream& out);
void populateTrie (TrieSet* &trie, vector<string>& webpages);
void readInput(ifstream& in, vector<string>& webpages, vector<string>& queries);


int main(int argc, char const *argv[])
{
	// check input
	if (argc < 3)
	{
		cerr << "Please include 2 files" << endl;
		return 0;
	}

	ifstream ifile(argv[1]);
	ofstream ofile (argv[2]);

	if (ifile.fail() || ofile.fail())
	{
		cerr << "Please include valid files" << endl;
		return 0;
	}

	// Setup (Steps 1 and 2)
	vector<string> webpages;
	vector<string> queries;
	readInput(ifile, webpages, queries);

	// TrieSet Tests (Steps 3-5)
	TrieSet* trie = new TrieSet();
	double trieInsertTime, trieQueryTime;
	int totalNegatives;
	populateTrie(trie, webpages);
	testTrie(trie, queries, ofile);

	// BloomFilter Tests (Steps 6-8)
	BloomFilter* bloom = new BloomFilter();
	double bloomInsertTime, bloomQueryTime;
	populateBloomFilter(bloom, webpages);
	testBloomFilter(bloom, queries, ofile);



	return 0;
}

/*
* runs tests on Bloom Filter with given queries
*/
void testBloomFilter(BloomFilter* bloom, vector<string>& queries, ofstream& out)
{
	vector<string> bloomFilterResults;
	for (int i = 0; i < (int)queries.size(); ++i)
	{
		if (bloom->contains(queries[i]))
		{
			bloomFilterResults.push_back("yes");
		}
		else
		{
			bloomFilterResults.push_back("no");
		}
	}

	for (int i = 0; i < (int) bloomFilterResults.size(); ++i)
	{
		out << bloomFilterResults[i] << "\n";
	}
}

/*
* inputs the webpages into the bloom filter
*/
void populateBloomFilter(BloomFilter* &bloom, vector<string>& webpages)
{
	for (int i = 0; i < (int) webpages.size(); ++i)
	{
		bloom->insert(webpages[i]);
	}
}

/*
* tests the trie with given queries
*/
void testTrie(TrieSet* &trie, vector<string>& queries, ofstream& out)
{
	vector<string> trieResults;

	for (int i = 0; i < (int) queries.size(); ++i)
	{
		if (trie->contains(queries[i]))
		{
			trieResults.push_back("yes");
		}
		else
		{
			trieResults.push_back("no");
		}
	}

	for (int i = 0; i < (int) trieResults.size(); ++i)
	{
		out << trieResults[i] << "\n";
	}
}


/*
* inputs the webpages to the trie
*/
void populateTrie (TrieSet* &trie, vector<string>& webpages)
{
	for (int i = 0; i < (int) webpages.size(); ++i)
	{
		trie->insert(webpages[i]);
	}
}

/*
* reads the input file into the approrpriate vectors
*/
void readInput(ifstream& in, vector<string>& webpages, vector<string>& queries)
{
	string line;
	int numWP;
	in >> numWP;

	// read webpages
	for (int i = 0; i < numWP; ++i)
	{
		in >> line;
		webpages.push_back(line);
	}

	// read queries
	while(!in.fail())
	{
		in >> line;
		queries.push_back(line);
	}
}