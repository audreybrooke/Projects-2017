#include <iostream>
#include <string>

using namespace std;

// This file is for classes that have to do with arithmetic expressions

class ArithmeticExpression {
  // abstract class for an arithmetic expression

 public:
  virtual void print (std::ostream & o) const = 0;
  // pure virtual print function. Don't implement!
};

/* if you prefer to have an abstract "BinaryArithmeticExpresion"
   class or something like that, feel free to insert it and
   have Addition inherit from that instead. */

class Addition : public ArithmeticExpression {
 public:
  Addition (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~Addition ();
  
  virtual void print (std::ostream & o) const;
  // because the class is not abstract, we must implement print
  
 private:
  ArithmeticExpression *_ae1, *_ae2; // the left and right term
};

// add below other classes that are needed

class Subtraction : public ArithmeticExpression {
 public:
  Subtraction (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~Subtraction ();
  
  virtual void print (std::ostream & o) const;
  // because the class is not abstract, we must implement print
  
 private:
  ArithmeticExpression *_ae1, *_ae2; // the left and right term
};

class Multiplication : public ArithmeticExpression {
 public:
  Multiplication (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~Multiplication ();
  
  virtual void print (std::ostream & o) const;
  // because the class is not abstract, we must implement print
  
 private:
  ArithmeticExpression *_ae1, *_ae2; // the left and right term
};

// Division

class Division : public ArithmeticExpression {
 public:
  Division (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~Division ();
  
  virtual void print (std::ostream & o) const;
  // because the class is not abstract, we must implement print
  
 private:
  ArithmeticExpression *_ae1, *_ae2; // the left and right term
};

// Constant

class Constant : public ArithmeticExpression {
 public:
  Constant (int value);
  ~Constant ();
  
  virtual void print (std::ostream & o) const;
  // because the class is not abstract, we must implement print
  
 private:
  int _value; // the value of the constant
};

// Variable

class Variable : public ArithmeticExpression {
 public:
  Variable (string vName);
  ~Variable ();
  
  virtual void print (std::ostream & o) const;
  // because the class is not abstract, we must implement print
  
 private:
  string variable; // the value of the constant
};

// Array Variable

class ArrayVariable : public ArithmeticExpression {
 public:
  ArrayVariable (string vName, ArithmeticExpression *ae1);
  ~ArrayVariable ();
  
  virtual void print (std::ostream & o) const;
  // because the class is not abstract, we must implement print
  
 private:
  string variable; // the value of the constant
  ArithmeticExpression *_ae1; // index
};