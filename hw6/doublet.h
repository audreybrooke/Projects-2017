#ifndef DOUBLET_H
#define DOUBLET_H

#include <string>

struct node
{
	public:
		std::string val;
		int priority;
};


struct myComparison {
	bool operator() (const node& lhs, const node& rhs);
};

#endif