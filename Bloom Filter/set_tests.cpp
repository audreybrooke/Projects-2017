#include "TrieSet.h"
#include "BloomFilter.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

void testBloomFilter(BloomFilter* bloom, vector<string>& queries, 
	ofstream& out, double &queryTime, vector<string>& bloomFilterResults);
void populateBloomFilter(BloomFilter* &bloom, vector<string>& webpages, double &insertTime);
void testTrie(TrieSet* &trie, vector<string>& queries, ofstream& out, 
	double &queryTime, vector<string>& trieResults);
void populateTrie (TrieSet* &trie, vector<string>& webpages, 
	double &insertTime);
int readInput(ifstream& in, vector<string>& webpages, 
	vector<string>& queries);
void calculateFalsePositives(int& falsePositives, int& totalNegatives, 
	vector<string>& trieResults, vector<string>& bloomFilterResults);
void outputResults(ofstream& out, int numWP, int numQ, double trieInsertTime, 
	double trieQueryTime, double bloomInsertTime, double bloomQueryTime, 
	int falsePositives, int totalNegatives);


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
	int numWP;
	numWP = readInput(ifile, webpages, queries);

	// TrieSet Tests (Steps 3-5)
	TrieSet* trie = new TrieSet();
	double trieInsertTime, trieQueryTime;
	vector<string> trieResults;
	populateTrie(trie, webpages, trieInsertTime);
	testTrie(trie, queries, ofile, trieQueryTime, trieResults);

	// BloomFilter Tests (Steps 6-8)
	BloomFilter* bloom = new BloomFilter(5 * numWP);
	double bloomInsertTime, bloomQueryTime;
	vector<string> bloomFilterResults;
	populateBloomFilter(bloom, webpages, bloomInsertTime);
	testBloomFilter(bloom, queries, ofile, bloomQueryTime, 
		bloomFilterResults);


	// Create the results for the output file
	int numQ, falsePositives, totalNegatives;
	falsePositives = 0;
	totalNegatives = 0;
	numQ = (int) queries.size();
	calculateFalsePositives(falsePositives, totalNegatives, 
		trieResults, bloomFilterResults);
	outputResults(ofile, numWP, numQ, trieInsertTime, trieQueryTime, 
		bloomInsertTime, bloomQueryTime, falsePositives, totalNegatives);

	delete trie;
	delete bloom;

	return 0;
}

/*
* outputs the results to the file
*/
void outputResults(ofstream& out, int numWP, int numQ, double trieInsertTime, 
	double trieQueryTime, double bloomInsertTime, double bloomQueryTime, 
	int falsePositives, int totalNegatives)
{

	out << numWP << " insertions\n";
	out << numQ << " queries\n";

	//trie results
	out << "total time for trie insertions: " << trieInsertTime;
	if (numWP == 0)
		out << " seconds (0";
	else
		out << " seconds (" << trieInsertTime/numWP;
	out << " seconds per insertion)\n";
	out << "total time for trie queries: " << trieQueryTime;
	if (numQ == 0)
		out << " seconds (0";
	else
		out << " seconds (" << trieQueryTime/numQ;
	out << " seconds per query)\n";

	
	//bloom results
	out << "total time for bloom insertions: " << bloomInsertTime;
	if (numWP == 0)
		out << " seconds (0";
	else
		out << " seconds (" << bloomInsertTime/numWP;
	out << " seconds per insertion)\n";
	out << "total time for bloom queries: " << bloomQueryTime;
	if (numQ == 0)
		out << " seconds (0";
	else
		out << " seconds (" << bloomQueryTime/numQ;
	out << " seconds per query)\n";

	
	//false positive results
	out << falsePositives << " false positives (";
	if (totalNegatives == 0)
		out << "0.0 false positive rate)";
	else
		out << (double)falsePositives/(double)totalNegatives << " false positive rate)";
}

/*
* Compares the results of trie and bloom filter to determine false
* positives
*/
void calculateFalsePositives(int& falsePositives, int& totalNegatives, 
	vector<string>& trieResults, vector<string>& bloomFilterResults)
{
	for (int i = 0; i < (int) trieResults.size(); ++i)
	{
		if (trieResults[i] == "no")
		{
			totalNegatives++;
			if (bloomFilterResults[i] == "yes")
			{
				falsePositives++;
			}
		}
	}
}

/*
* runs tests on Bloom Filter with given queries
*/
void testBloomFilter(BloomFilter* bloom, vector<string>& queries, 
	ofstream& out, double &queryTime, vector<string>& bloomFilterResults)
{
	clock_t start;
	start = clock();
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
	queryTime = (clock() - start) / (double) CLOCKS_PER_SEC;

	for (int i = 0; i < (int) bloomFilterResults.size(); ++i)
	{
		out << bloomFilterResults[i] << "\n";
	}
}

/*
* inputs the webpages into the bloom filter
*/
void populateBloomFilter(BloomFilter* &bloom, vector<string>& webpages, 
	double &insertTime)
{
	clock_t start;
	start = clock();
	for (int i = 0; i < (int) webpages.size(); ++i)
	{
		bloom->insert(webpages[i]);
	}
	insertTime = (clock() - start) / (double) CLOCKS_PER_SEC;
}

/*
* tests the trie with given queries
*/
void testTrie(TrieSet* &trie, vector<string>& queries, ofstream& out,
	double & queryTime, vector<string>& trieResults)
{
	clock_t start;
	start = clock();

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

	queryTime = (clock() - start) / (double) CLOCKS_PER_SEC;

	for (int i = 0; i < (int) trieResults.size(); ++i)
	{
		out << trieResults[i] << "\n";
	}
}


/*
* inputs the webpages to the trie
*/
void populateTrie (TrieSet* &trie, vector<string>& webpages, 
	double &insertTime)
{
	clock_t start;
	start = clock();

	for (int i = 0; i < (int) webpages.size(); ++i)
	{
		trie->insert(webpages[i]);
	}

	insertTime = (clock() - start) / (double) CLOCKS_PER_SEC;
}

/*
* reads the input file into the approrpriate vectors
*/
int readInput(ifstream& in, vector<string>& webpages, 
	vector<string>& queries)
{
	string line;
	int numWP;
	in >> numWP;
	long total = 0;

	// read webpages
	for (int i = 0; i < numWP; ++i)
	{
		in >> line;
		webpages.push_back(line);
		total += line.size();
	}
	cout << "total = " << total << ". average = " << total / numWP << endl;

	// read queries
	while(!in.fail())
	{
		in >> line;
		queries.push_back(line);
	}
	queries.pop_back();

	return numWP;
}
