#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <iostream>
#include <set>
#include "Command.h"

class Command;
class Line;



class end_call
{
  public:
    end_call(const string m=""):msg(m){}
     ~end_call(){}
    const char* what(){return msg.c_str();}
  private:
    string msg;
};




class Interpreter {
  // abstract class for a BASIC Command

 public:
  Interpreter (std::vector<Line*> prg);
  ~Interpreter();
  
  void runProgram(std::ostream& out);
  // void moveToLine(int goTo);
  // runs the program

  // friend class Command;

private:
  vector<Line*> theProgram; // the commands and their line numbers in order
  map<string, int> variableMap; // map of ints (values) with strings as variable name
  stack<LineNumber*> returnStack; // stack of lines to return to for GOSUB and return
  vector<Line*>::iterator theIterator; // keeps track of which line the program should execute
  set<string> arrayNames;  // keeps track of all arrays that have been made
  map<string, map<int, int> > arrayVariableMap; // arrays that exist and the value at their indecies
};

// add below other classes that are needed

#endif