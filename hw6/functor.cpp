#include "functor.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

bool AlphaStrComp::operator() (const std::string& lhs, const std::string& rhs) 
{ return (lhs < rhs); }

bool LengthStrComp::operator()(const std::string& lhs, const std::string& rhs) 
{ 
	return ((lhs.size() < rhs.size())
		|| (lhs.size() == rhs.size() && lhs < rhs)); 
}

bool NumStrComp::operator()(const std::string& lhs, const std::string& rhs) 
{ 
	int lhsValue = 0;
	char current;
	for (int i = 0; i < lhs.size(); i++)
	{
		current = lhs[i];
		if (isdigit(current))
		{
			lhsValue += current - '0';
		}
		else if (isalpha(current))
		{
			if (isupper(current))
			{
				lhsValue = current - 'A' + 10;
			}
			else
			{
				lhsValue = current - 'a' + 10;
			}
		}
	}

	int rhsValue = 0;

	for (int i = 0; i < rhs.size(); i++)
	{
		current = rhs[i];
		if (isdigit(current))
		{
			rhsValue += current - '0';
		}
		else if (isalpha(current))
		{
			if (isupper(current))
			{
				rhsValue = current - 'A' + 10;
			}
			else
			{
				rhsValue = current - 'a' + 10;
			}
		}
	}


	return (lhsValue <  rhsValue
		|| (lhsValue == rhsValue && lhs < rhs));
}