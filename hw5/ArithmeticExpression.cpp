#include "ArithmeticExpression.h"
#include <sstream>

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

int Addition::getValue (map<string, int> &variableMap, map<string, map<int, int> > &arrayVariableMap, set<string> &arrNameSet)
{
  return _ae1->getValue(variableMap, arrayVariableMap, arrNameSet) + _ae2->getValue(variableMap, arrayVariableMap, arrNameSet);
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

int Subtraction::getValue (map<string, int> &variableMap, map<string, map<int, int> > &arrayVariableMap, set<string> &arrNameSet)
{
  return _ae1->getValue(variableMap, arrayVariableMap, arrNameSet) - _ae2->getValue(variableMap, arrayVariableMap, arrNameSet);
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

int Multiplication::getValue (map<string, int> &variableMap, map<string, map<int, int> > &arrayVariableMap, set<string> &arrNameSet)
{
  return _ae1->getValue(variableMap, arrayVariableMap, arrNameSet) * _ae2->getValue(variableMap, arrayVariableMap, arrNameSet);
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

int Division::getValue (map<string,int> &variableMap, map<string, map<int, int> > &arrayVariableMap, set<string> &arrNameSet)
{
  if (_ae2->getValue(variableMap, arrayVariableMap, arrNameSet) == 0)
  {
    // throw exception for divide by 0
  }

  return _ae1->getValue(variableMap, arrayVariableMap, arrNameSet) / _ae2->getValue(variableMap, arrayVariableMap, arrNameSet);
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

int Constant::getValue (map<string, int> &variableMap, map<string, map<int, int> > &arrayVariableMap, set<string> &arrNameSet)
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

int Variable::getValue (map<string, int> &variableMap, map<string, map<int, int> > &arrayVariableMap, set<string> &arrNameSet)
{
  // CHECK IF variable is even in map!!
  // uh oh... how?

  return variableMap[variable];// Interpreter::variableMap[variable];
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

int ArrayVariable::getValue (map<string, int> &variableMap, map<string, map<int, int> > &arrayVariableMap, set<string> &arrNameSet)
{

  if (arrayVariableMap.find(variable) != arrayVariableMap.end())
  {
    // this array exists
    int index = _ae1 -> getValue(variableMap, arrayVariableMap, arrNameSet);
    if (arrayVariableMap[variable].find(index) != arrayVariableMap[variable].end())
    {
      // this specific index exists
      return arrayVariableMap[variable][index];
    }
    else
    {
      // this specific index does not exist
      arrayVariableMap[variable][index] = 0;
      return 0;
    }
  }

  // array does not exist yet... exception?

  return 0;






  // use varibale name and value of _ae1
  // if there is no set value for that index, return 0
  // !!!! NEEDS TO BE FIXED !!!! 
/*
  int index = _ae1 -> getValue(variableMap, arrayVariableMap, arrNameSet);
  stringstream ss;
  ss << index;
  string str = ss.str();
  string theKey = variable + "[" + str + "]";

  cout << "searching for key: " << theKey << endl;

  cout << "Does arrayname set contain " << variable << endl;

  if (arrNameSet.count(variable) != 0)
  {
    // array exists
    cout << "this array exists" << endl;
    if (arrayVariableMap.find(theKey) != arrayVariableMap.end())
    {
      // specific idex has been added
      cout << "this index exists" << endl;
      return arrayVariableMap[theKey];
    }
    // specific index was not added
    cout << "this index does not exist yet" << endl;
    return 0;
  } 

  // Array does not exist!!
  return 0;
  */
}