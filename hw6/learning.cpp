#include "learning.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int count = 0;

int main(int argc, char const *argv[])
{
	if (argc < 1)
	{
		cerr << "Please include input file" << endl;
		return 0;
	}

	ifstream ifile(argv[1]);

	if (ifile.fail())
	{
		cerr << "Please provide valid input file" << endl;
		return 0;
	}

	int numOptions;
	double maxWork;

	ifile >> numOptions;
	ifile >> maxWork;

	if (ifile.fail())
	{
		cerr << "File formatted incorrectly" << endl;
		return 0;
	}

	vector<tClass*> classOptions;

	string cName;
	double cWork, cLearning;
	for (int i = 0; i < numOptions; ++i)
	{
		ifile >> cName;
		ifile >> cWork;
		ifile >> cLearning;
		tClass* thisClass = new tClass(cName, cWork, cLearning);
		classOptions.push_back(thisClass);
	}

	bool availableClasses[25];
	for (int i = 0; i < 25; ++i)
	{
		availableClasses[i] = true;
	}


	// test input
	 
	 cout << "Total Options: " << numOptions << endl;
	 cout << "Maximum Work: " << maxWork << endl;
	 cout << "Classes:" << endl;
	 for (int i = 0; i < (int)classOptions.size(); ++i)
	 {
	 	cout << "name: " << classOptions[i]->name << " work: ";
	 	cout << classOptions[i]->work << " learning: " << classOptions[i]->learning << endl;
	 }
	

	double currentMaxLearning = 0;
	findLearning(0, 0, currentMaxLearning, classOptions, maxWork, availableClasses);

	 

	cout << "Maximum learning: " << currentMaxLearning << endl;


	// delete tClass pointers in the vector!
	for (int i = 0; i < (int )classOptions.size(); ++i)
	{
		tClass* toDelete = classOptions[classOptions.size()-1];
		classOptions.pop_back();
		delete toDelete;
	}
	return 0;
}

void findLearning(double currTotalWork, double currTotalLearn, double& currMaxLearn,
	vector<tClass*>& classOptions, double maxWork, bool availableClasses[25])
{
	cout << ++count;
	for (int i = 0; i < (int) classOptions.size(); ++i)
	{
		double posLearnTotal = currTotalLearn + classOptions[i]->learning;
		double posWorkToal = currTotalWork + classOptions[i]->work;
		// cout << "Position: " << i << ". learn total: " << posLearnTotal << " work total: " << posWorkToal << endl;
		// cout << "available classes:";
		/*
		for (int j = 0; j < (int) classOptions.size(); ++j)
		{
			if (availableClasses[j])
			{
				cout << " " << j;
			}
		}
		cout << endl;
		*/

		if (availableClasses[i] && posWorkToal <= maxWork)
		{
			// cout << "valid option" << endl;
			availableClasses[i] = false;
			findLearning(posWorkToal, posLearnTotal, currMaxLearn, classOptions, maxWork, availableClasses);
			availableClasses[i] = true;
		}

	}
	if (currMaxLearn < currTotalLearn)
		currMaxLearn = currTotalLearn;

}


tClass::tClass(string n, double w, double l)
{
	name = n;
	work = w;
	learning = l;
}

tClass::~tClass(){}