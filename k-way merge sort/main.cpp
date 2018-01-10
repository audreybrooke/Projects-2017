#include "msort.h"
#include <vector>
#include <string>
#include <iostream>

int main(int argc, char const *argv[])
{
	vector<string> sortMe;

		sortMe.push_back("car"); 
		sortMe.push_back("cat"); 
		sortMe.push_back("long");
		sortMe.push_back("short");
		sortMe.push_back("verysuperextralonegwordwowomgstopalready");
		sortMe.push_back("cool");
		sortMe.push_back("super");
		sortMe.push_back("TINY");
		sortMe.push_back("superficial");
		sortMe.push_back("zzzzzzzzzebra");
		sortMe.push_back("zoo");
		sortMe.push_back("fade");
		sortMe.push_back("bump"); 
		sortMe.push_back("iceland");
		sortMe.push_back("idle");
		sortMe.push_back("animal");

	// choose the comparison you would like
	LengthStrComp comp;



	mergeSort(sortMe, 3, comp);


	for (int i = 0; i < (int)sortMe.size(); ++i)
	{
		cout << sortMe[i] << endl;
	}




	return 0;
}