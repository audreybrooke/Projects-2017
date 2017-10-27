#ifndef COMMAND_H
#define COMMAND_H


#include <iostream>
#include <string>
#include "BooleanExpression.h"
#include "LineNumber.h"
#include "Interpreter.h"
#include <stdexcept>
#include <exception>

class Interpreter;
class Line;


class Command {
  // abstract class for a BASIC Command

 public:
  virtual ~Command()=0;
  virtual void print (std::ostream & o) const = 0;
  virtual void execute (vector<Line*> &program, 
    map<string, int> &varMap, 
    stack<LineNumber*> &retStack, 
    vector<Line*>::iterator &theIt, 
    std::ostream &outStream,
    set<string> &arrName,
    map<string, map<int, int> > &arrVarMap) = 0;
  friend class Interpreter;
  // pure virtual print function. Don't implement!
};

class Line
{

public:
  Line (LineNumber* theNum, Command* theCom);
  ~Line();
  LineNumber* ln;
  Command* com;
};

// add below other classes that are needed

// Print_Command

class Print_Command : public Command {
 public:
  Print_Command (ArithmeticExpression *ae1);
  ~Print_Command ();
  
  virtual void print (std::ostream & o) const;
  virtual void execute (vector<Line*> &program, map<string, int> &varMap, stack<LineNumber*> &retStack, vector<Line*>::iterator &theIt, std::ostream &outStream, set<string> &arrName, map<string, map<int, int> > &arrVarMap);
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
  virtual void execute (vector<Line*> &program, map<string, int> &varMap, stack<LineNumber*> &retStack, vector<Line*>::iterator &theIt, std::ostream &outStream, set<string> &arrName, map<string, map<int, int> > &arrVarMap);
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
  virtual void execute (vector<Line*> &program, map<string, int> &varMap, stack<LineNumber*> &retStack, vector<Line*>::iterator &theIt, std::ostream &outStream, set<string> &arrName, map<string, map<int, int> > &arrVarMap);
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
  virtual void execute (vector<Line*> &program, map<string, int> &varMap, stack<LineNumber*> &retStack, vector<Line*>::iterator &theIt, std::ostream &outStream, set<string> &arrName, map<string, map<int, int> > &arrVarMap);
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
  virtual void execute (vector<Line*> &program, map<string, int> &varMap, stack<LineNumber*> &retStack, vector<Line*>::iterator &theIt, std::ostream &outStream, set<string> &arrName, map<string, map<int, int> > &arrVarMap);
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
  virtual void execute (vector<Line*> &program, map<string, int> &varMap, stack<LineNumber*> &retStack, vector<Line*>::iterator &theIt, std::ostream &outStream, set<string> &arrName, map<string, map<int, int> > &arrVarMap);
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
  virtual void execute (vector<Line*> &program, map<string, int> &varMap, stack<LineNumber*> &retStack, vector<Line*>::iterator &theIt, std::ostream &outStream, set<string> &arrName, map<string, map<int, int> > &arrVarMap);
  // because the class is not abstract, we must implement print
};


// End_Command


class End_Command : public Command {
 public:
  End_Command ();
  ~End_Command ();
  
  virtual void print (std::ostream & o) const;
  virtual void execute (vector<Line*> &program, map<string, int> &varMap, stack<LineNumber*> &retStack, vector<Line*>::iterator &theIt, std::ostream &outStream, set<string> &arrName, map<string, map<int, int> > &arrVarMap);
  // because the class is not abstract, we must implement print
};


class line_number_error
{
  public:
    line_number_error(const string m=""):msg(m){}
    ~line_number_error(){}
    const char* what(){return msg.c_str();}
  private:
    string msg;
};

#endif