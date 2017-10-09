// Addition
#include "ArithmeticExpression.h"

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

// Constant

Constant::Constant (int value)
{
  _value = value;
}
  
void Constant::print (std::ostream & o) const
{
  o << _value;
}

// Variable

Variable::Variable (string vName)
{
  variable = vName;
}
  
void Variable::print (std::ostream & o) const
{
  o << variable;
}

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