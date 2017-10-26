#include "ArithmeticExpression.h"

// class Interpreter;

// Addition

ArithmeticExpression::~ArithmeticExpression()
{
  
}


Addition::Addition (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

Addition::~Addition ()
{
  delete _ae1;
  delete _ae2;
}
  
void Addition::print (std::ostream & o) const
{
  o << "(";
  _ae1->print (o);
  o << " + ";
  _ae2->print (o);
  o << ")";
}

int Addition::getValue () const
{
  return _ae1->getValue() + _ae2->getValue();
}

// Subtraction

Subtraction::Subtraction (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

Subtraction::~Subtraction ()
{
  delete _ae1;
  delete _ae2;
}
  
void Subtraction::print (std::ostream & o) const
{
  o << "(";
  _ae1->print (o);
  o << " - ";
  _ae2->print (o);
  o << ")";
}

int Subtraction::getValue () const
{
  return _ae1->getValue() - _ae2->getValue();
}

// Multiplication

Multiplication::Multiplication (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

Multiplication::~Multiplication ()
{
  delete _ae1;
  delete _ae2;
}
  
void Multiplication::print (std::ostream & o) const
{
  o << "(";
  _ae1->print (o);
  o << " * ";
  _ae2->print (o);
  o << ")";
}

int Multiplication::getValue () const
{
  return _ae1->getValue() * _ae2->getValue();
}

// Division

Division::Division (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

Division::~Division ()
{
  delete _ae1;
  delete _ae2;
}
  
void Division::print (std::ostream & o) const
{
  o << "(";
  _ae1->print (o);
  o << " / ";
  _ae2->print (o);
  o << ")";
}

int Division::getValue () const
{
  if (_ae2->getValue() == 0)
  {
    // throw exception for divide by 0
  }

  return _ae1->getValue() / _ae2->getValue();
}

// Constant

Constant::Constant (int value)
{
  _value = value;
}

Constant::~Constant()
{

}
  
void Constant::print (std::ostream & o) const
{
  o << _value;
}

int Constant::getValue () const
{
  return _value;
}

// Variable

Variable::Variable (string vName)
{
  variable = vName;

  // if vName is already in variableMap do I need to do something different?
  // for now, no
}

Variable::~Variable()
{
  
}
  
void Variable::print (std::ostream & o) const
{
  o << variable;
}

int Variable::getValue () const
{
  // CHECK IF variable is even in map!!

  return 0;// Interpreter::variableMap[variable];
}

// ArrayVariable

ArrayVariable::ArrayVariable (string vName, ArithmeticExpression *ae1)
{
  variable = vName;
  _ae1 = ae1;
}

ArrayVariable::~ArrayVariable()
{
  delete _ae1;
}
  
void ArrayVariable::print (std::ostream & o) const
{
  o << variable << "[";
  _ae1->print(o);
  o << "]";
}

int ArrayVariable::getValue () const
{
  // use varibale name and value of _ae1
  // if there is no set value for that index, return 0
  // !!!! NEEDS TO BE FIXED !!!! 

  return 0;
}