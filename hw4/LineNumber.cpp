#include "LineNumber.h"

using namespace std;

LineNumber::LineNumber(int num)
{
  line = num;
}

void LineNumber::print (std::ostream & o) const
{
  o << line;
}