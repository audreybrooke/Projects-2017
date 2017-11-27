#include <string>
#include "trie.h"
#include <iostream>

using namespace std;




int main(int argc, char const *argv[])
{
	TrieSet* set = new TrieSet();
	set->insert("cat");
	cout << set->contains("cat") << endl; 	// 1
	cout << set->contains("catch") << endl; // 0
	cout << set->contains("ca") << endl;	// 0
	set->insert("ca");
	cout << set->contains("ca") << endl;	// 1
	set->remove("ca");
	cout << set->contains("cat") << endl;	// 1

	set->insert("dog");
	set->insert("dooooooooooooooooooooooooooooooood");
	cout << set->contains("papap") << endl; // 0
	cout << set->contains("doooo") << endl; // 0
	cout << set->contains("") << endl;		// 0
	set->insert("https://www.usc.edu/cs_rules");
	cout << set->contains("https://www.usc.edu/cs_rules") << endl; // 1

	delete set;

	return 0;
}



TrieSet::TrieSet()
{
	root = new TrieNode();
}

TrieSet::~TrieSet()
{
	destruct_helper(root);
}

void TrieSet::destruct_helper (TrieNode* loc)
{
	if (loc == NULL)
	{
		return;
	}

	for (int i = 0; i < 30; ++i)
	{
		destruct_helper(loc->children[i]);
	}

	delete loc;
}


/*
* Add this string to the set.
* Do nothing if the string is already in the set.
*/
void TrieSet::insert (string input)
{
	TrieNode* location = root;

	for (int i = 0; i < (int) input.size(); ++i)
	{
		// cout << "adding " << input[i] << endl;

		bool atEnd = false;
		int index = findIndex(input[i]);

		if (i == (int) input.size() - 1) atEnd = true;

		if (location->children[index] == NULL)
		{
			location->children[index] = new TrieNode();
			location->children[index]->parent = location;
		}
		if (atEnd)
		{
			location->children[index]->inSet = true;
		}

		location = location->children[index];
	}
}

/*
* Remove this string from the set.
* Do nothing if the string is not in the set.
*/
void TrieSet::remove (string input)
{
	TrieNode* location = root;

	for (int i = 0; i < (int) input.size(); ++i)
	{
		int index = findIndex(input[i]);
		bool atEnd = false;
		if (i == (int) input.size() - 1) atEnd = true;

		location = location->children[index];

		if (location == NULL)
		{
			return;
		}
		if (atEnd)
		{
			location->inSet = false;
		}
	}
}

/*
* returns whether this string is in the set.
*/
bool TrieSet::contains (std::string input)
{
	TrieNode* location = root;

	for (int i = 0; i < (int) input.size(); ++i)
	{
		// cout << "checking " << input[i] << endl;

		int index = findIndex(input[i]);
		bool atEnd = false;
		if (i == (int) input.size() - 1) atEnd = true;

		location = location->children[index];

		if (location == NULL)
		{
			// cout << "location is NULL" << endl;
			return false;
		}

		if (atEnd)
		{
			if (location->inSet)
			{
				return true;
			}
			return false;
		}
	}

	return false;
}

/*
* Determines which index corresponds to each letter
*/
int TrieSet::findIndex (char i)
{
	int index = 0;
	if (i == '/')
	{
	 	index = 26;
	}
	else if (i == ':')
	{
	 	index = 27;
	}
	else if (i == '_')
	{
	 	index = 28;
	}
	else if (i == '.')
	{
	 	index = 29;
	}
	else 
	{
		index = i - 'a';
	}

	return index;
}