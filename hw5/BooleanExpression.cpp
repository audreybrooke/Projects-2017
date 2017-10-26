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

bool Equal::getValue(map<string, int> &variableMap)
{
  if (_ae1->getValue(variableMap) == _ae2->getValue(variableMap))
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

bool LessThan::getValue(map<string, int> &variableMap)
{
  // cout << "in less than get value" << endl;

  if (_ae1->getValue(variableMap) < _ae2->getValue(variableMap))
  {
    // cout << "returning true" << endl;
    return true;
  }

  // cout << "returning false" << endl;
  return false;
}