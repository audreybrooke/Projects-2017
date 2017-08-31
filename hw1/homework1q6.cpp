/*

Audrey Brooke
CSCI 104
Homework 1

program takes a file with int length and string
and reverses the string

*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string reverse (int first, int last, string theString)
{
	if (last <= first)
	{
		return theString;
	}

	char temp = theString[first];
	theString[first] = theString[last];
	theString[last] = temp;
	return reverse (first+1, last-1, theString);

}



int main (int argc, char* argv[])
{

	int numLetters;
	string input;
	string output;

	ifstream ifile (argv[1]);

	bool failed = ifile.fail();

	if (failed)
	{
		cout << "ifile failed to read in text file" << endl;
		return 0;
 	}

	else
	{
		ifile >> numLetters;
		getline (ifile, input);
		// ifile >> input;
		// ifile.getline(input, numLetters);
		getline (ifile, input);
		
		cout << "Number inputed: " << numLetters << endl;
		cout << "Text inputed: " << input << endl;

		if (ifile.fail())
		{
			cout << "ifile failed to read an int and string" << endl;
			return 0;
		}

		else 
		{
			output = reverse (0, numLetters-1, input);
			cout << output << endl;
		}
	}

}