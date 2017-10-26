#include <iostream>
#include <vector>
#include <map>
#include <stack>

class Command;
class Line;

class Interpreter {
  // abstract class for a BASIC Command

 public:
  Interpreter (vector<Line*> prg, std::ostream &out);
  ~Interpreter();
  
  void runProgram();
  void moveToLine(int goTo);
  // runs the program

  friend class Command;

private:
  vector<Line*> theProgram;
  map<string, ArithmeticExpression*> variableMap;
  stack<LineNumber*> returnStack;
  vector<Line*>::iterator theIterator;
  // ostream??
  std::ostream outputStream;

};

// add below other classes that are needed