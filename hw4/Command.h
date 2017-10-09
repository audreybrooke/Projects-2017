#include <iostream>
#include <string>
#include "BooleanExpression.h"
#include "LineNumber.h"


class Command {
  // abstract class for a BASIC Command

 public:
  virtual ~Command()=0;
  virtual void print (std::ostream & o) const = 0;
  // pure virtual print function. Don't implement!
};

struct Line
{
  LineNumber* ln;
  Command* com;
  Line (LineNumber* theNum, Command* theCom);
  ~Line();
};

// add below other classes that are needed

// Print_Command

class Print_Command : public Command {
 public:
  Print_Command (ArithmeticExpression *ae1);
  ~Print_Command ();
  
  virtual void print (std::ostream & o) const;
  // because the class is not abstract, we must implement print
  
 private:
  ArithmeticExpression *_ae1; // the term
};

// LetConst_Command

class LetConst_Command : public Command {
 public:
  LetConst_Command (string variableName, ArithmeticExpression *ae1);
  ~LetConst_Command ();
  
  virtual void print (std::ostream & o) const;
  // because the class is not abstract, we must implement print
  
 private:
  string variable;
  ArithmeticExpression *_ae1; // the term
};


// LetArray_Command


class LetArray_Command : public Command {
 public:
  LetArray_Command (string variableName, ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~LetArray_Command ();
  
  virtual void print (std::ostream & o) const;
  // because the class is not abstract, we must implement print
  
 private:
  ArithmeticExpression *_ae1, *_ae2; // ae1 = index ae2 = value
  string variable;
};

// Goto_Command

class Goto_Command : public Command {
 public:
  Goto_Command (LineNumber *num);
  ~Goto_Command ();
  
  virtual void print (std::ostream & o) const;
  // because the class is not abstract, we must implement print
  
 private:
  LineNumber *_num; // the line
};

// IfThen_Command

class IfThen_Command : public Command {
 public:
  IfThen_Command (LineNumber *num, BooleanExpression *be1);
  ~IfThen_Command ();
  
  virtual void print (std::ostream & o) const;
  // because the class is not abstract, we must implement print
  
 private:
  LineNumber *_num; // the line
  BooleanExpression *_be1; // the term
};

// Gosub_Command

class Gosub_Command : public Command {
 public:
  Gosub_Command (LineNumber *num1, LineNumber *num2);
  ~Gosub_Command ();
  
  virtual void print (std::ostream & o) const;
  // because the class is not abstract, we must implement print
  
 private:
  LineNumber *_num1; // the original line
  LineNumber *_num2; // the destination line
};

//Return_Command

class Return_Command : public Command {
 public:
  Return_Command ();
  ~Return_Command ();
  
  virtual void print (std::ostream & o) const;
  // because the class is not abstract, we must implement print
};


// End_Command

//Return_Command

class End_Command : public Command {
 public:
  End_Command ();
  ~End_Command ();
  
  virtual void print (std::ostream & o) const;
  // because the class is not abstract, we must implement print
};