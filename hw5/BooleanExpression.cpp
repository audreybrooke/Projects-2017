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

bool Equal::getValue() const
{
  if (_ae1->getValue() == _ae2->getValue())
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

bool LessThan::getValue() const
{
  if (_ae1->getValue() < _ae2->getValue())
  {
    return true;
  }

  return false;
}