#include "learning.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;


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
	
	/*
	for (int i = 0; i < 25; ++i)
	{
		availableClasses[i] = true;
	}
	*/

	// test input
	 /*
	 cout << "Total Options: " << numOptions << endl;
	 cout << "Maximum Work: " << maxWork << endl;
	 cout << "Classes:" << endl;
	 for (int i = 0; i < (int)classOptions.size(); ++i)
	 {
	 	cout << "name: " << classOptions[i]->name << " work: ";
	 	cout << classOptions[i]->work;
	 	cout << " learning: " << classOptions[i]->learning << endl;
	 }
	*/

	double currentMaxLearning = 0;
	findLearning(classOptions, 0, availableClasses, currentMaxLearning, maxWork, 0.0);

	 

	cout << "Maximum learning: " << currentMaxLearning << endl;


	// delete tClass pointers in the vector!
	while ( (int)classOptions.size() > 0)
	{
		tClass* toDelete = classOptions.back();
		classOptions.pop_back();
		delete toDelete;
	}
	return 0;
}


// NOT THE FUNCTION USED!!!!
// this checks all permutations of classes instead of combinations
// look below for combinations implementation (which is the one
// used by main)
void findLearning(double currTotalWork, double currTotalLearn, double& currMaxLearn,
	vector<tClass*>& classOptions, double maxWork, bool availableClasses[25])
{
	// cout << ++count;
	for (int i = 0; i < (int) classOptions.size(); ++i)
	{
		double posLearnTotal = currTotalLearn + classOptions[i]->learning;
		double posWorkToal = currTotalWork + classOptions[i]->work;
		// cout << "Position: " << i << ". learn total: " << posLearnTotal
		// << " work total: " << posWorkToal << endl;
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
			findLearning(posWorkToal, posLearnTotal, currMaxLearn, classOptions,
				maxWork, availableClasses);
			availableClasses[i] = true;
		}

	}
	if (currMaxLearn < currTotalLearn)
		currMaxLearn = currTotalLearn;

}


// checks all combinations of classes! works much faster than permutations
// this is utilized by main

void findLearning(vector<tClass*>& classOptions, int location, bool availableClasses[25],
	double& currentMaxLearning, double maxWork, double currWork)
{

	if (location == (int) classOptions.size()-1)
	{
		availableClasses[location] = false;
		checkCombos(classOptions, availableClasses, currentMaxLearning, maxWork);
		availableClasses[location] = true;
		checkCombos(classOptions, availableClasses, currentMaxLearning, maxWork);
		return;
	}

	if (currWork < maxWork)
	{
		availableClasses[location] = false;
		findLearning(classOptions, location + 1, availableClasses, currentMaxLearning,
			maxWork, currWork);
	}
	if (currWork+classOptions[location]->work < maxWork)
	{
		availableClasses[location] = true;
		findLearning(classOptions, location + 1, availableClasses, currentMaxLearning,
			maxWork, currWork+classOptions[location]->work);		
	}


}

void checkCombos(vector<tClass*>& classOptions, bool availableClasses[25],
	double& currentMaxLearning, double maxWork)
{
	// cout << "checking combo:";
	double totalWork = 0;
	double totalLearning = 0;
	for (int i = 0; i < (int) classOptions.size(); ++i)
	{
		if (availableClasses[i])
		{
			totalWork+= classOptions[i]->work;
			totalLearning+= classOptions[i]->learning;
			// cout << classOptions[i]->name << " ";
		}
	}
	// cout << endl;

	if (totalWork <= maxWork && totalLearning > currentMaxLearning)
	{
		currentMaxLearning = totalLearning;
		// cout << "New max learning: " << currentMaxLearning << endl;
	}
}


tClass::tClass(string n, double w, double l)
{
	name = n;
	work = w;
	learning = l;
}

tClass::~tClass(){}