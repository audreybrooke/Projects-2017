#ifndef LEARNING_H
#define LEARNING_H

#include <string>
#include <vector>

struct tClass {
	tClass(std::string n, double w, double l);
	~tClass();
	std::string name;
	double work;
	double learning;
};

void findLearning (double currTotalWork, double currTotalLearn, double& currMaxLearn,
	std::vector<tClass*>& classOptions, double maxWork, bool availableClasses[25]);
  
#endif