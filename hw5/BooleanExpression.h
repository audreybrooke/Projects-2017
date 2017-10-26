#include <iostream>
#include "ArithmeticExpression.h"

// This file is for classes that have to do with Boolean expressions

class BooleanExpression {
  // abstract class for a Boolean expression

 public:
  virtual ~BooleanExpression()=0;
  virtual void print (std::ostream & o) const = 0;
  virtual bool getValue(map<string, int> &variableMap) = 0;
  // pure virtual print function. Don't implement!
};

// add below other classes that are needed

// Equal

class Equal : public BooleanExpression {
 public:
  Equal (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~Equal ();
  
  virtual void print (std::ostream & o) const;
  virtual bool getValue(map<string, int> &variableMap);
  // because the class is not abstract, we must implement print
  
 private:
  ArithmeticExpression *_ae1, *_ae2; // the left and right term
};

// LessThan

class LessThan : public BooleanExpression {
 public:
  LessThan (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~LessThan ();
  
  virtual void print (std::ostream & o) const;
  virtual bool getValue(map<string, int> &variableMap);
  // because the class is not abstract, we must implement print
  
 private:
  ArithmeticExpression *_ae1, *_ae2; // the left and right term
};