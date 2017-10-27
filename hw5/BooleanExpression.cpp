#include "BooleanExpression.h"

using namespace std;


// Equal

BooleanExpression::~BooleanExpression()
{

}

Equal::Equal (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

Equal::~Equal ()
{
  delete _ae1;
  delete _ae2;
}
  
void Equal::print (std::ostream & o) const
{
  o << "[";
  _ae1->print (o);
  o << " = ";
  _ae2->print (o);
  o << "]";
}

bool Equal::getValue(map<string, int> &variableMap, map<string, map <int, int> > &arrayVariableMap, set<string> &arrNameSet)
{
  if (_ae1->getValue(variableMap, arrayVariableMap, arrNameSet) == _ae2->getValue(variableMap, arrayVariableMap, arrNameSet))
  {
    return true;
  }

  return false;
}

// LessThan

LessThan::LessThan (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

LessThan::~LessThan ()
{
  delete _ae1;
  delete _ae2;
}
  
void LessThan::print (std::ostream & o) const
{
  o << "[";
  _ae1->print (o);
  o << " < ";
  _ae2->print (o);
  o << "]";
}

bool LessThan::getValue(map<string, int> &variableMap, map<string, map <int, int> > &arrayVariableMap, set<string> &arrNameSet)
{
  // cout << "in less than get value" << endl;

  if (_ae1->getValue(variableMap, arrayVariableMap, arrNameSet) < _ae2->getValue(variableMap, arrayVariableMap, arrNameSet))
  {
    // cout << "returning true" << endl;
    return true;
  }

  // cout << "returning false" << endl;
  return false;
}