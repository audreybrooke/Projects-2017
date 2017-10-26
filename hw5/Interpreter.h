#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <iostream>
#include "Command.h"

class Command;
class Line;

class Interpreter {
  // abstract class for a BASIC Command

 public:
  Interpreter (std::vector<Line*> prg);
  ~Interpreter();
  
  void runProgram(std::ostream& out);
  // void moveToLine(int goTo);
  // runs the program

  friend class Command;

private:
  vector<Line*> theProgram;
  map<string, int> variableMap;
  stack<LineNumber*> returnStack;
  vector<Line*>::iterator theIterator;

};

// add below other classes that are needed

#endif