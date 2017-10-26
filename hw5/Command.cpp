#include "Command.h"
#include <map>
#include <set>
#include <stack>
#include <vector>

using namespace std;

void moveToLine (vector<Line*> &prg, vector<Line*>::iterator &it, int goTo)
{
  // cout << "entering moveToLine" << endl;
  for (it = prg.begin(); it != prg.end(); it++)
  {
    Line* thisLine= *it;
    if (thisLine -> ln -> line == goTo)
    {
      // found the location to jump to, leave iterator here
      // cout << "Found line number: " << goTo << endl;
      return;
    }
  }

  // line number not found!
  // THROW EXCEPTION!
}


Command::~Command()
{
  // cout << "deleting command" << endl;
}

// Line

  Line::Line (LineNumber* theNum, Command* theCom)
  {
    ln = theNum;
    com = theCom;
  }

  Line::~Line()
  {
    delete ln;
    delete com;
  }

// Print_Command

Print_Command::Print_Command (ArithmeticExpression *ae1)
{
  _ae1 = ae1;
}

Print_Command::~Print_Command ()
{
  delete _ae1;
}
  
void Print_Command::print (std::ostream & o) const
{
  o << "PRINT ";
  _ae1->print (o);
}

void Print_Command::execute (vector<Line*> &program, map<string, int> &varMap, stack<LineNumber*> &retStack, vector<Line*>::iterator &theIt, std::ostream &outStream)
{
  (outStream) << (_ae1 -> getValue(varMap)) << endl;
  theIt++;
}

// LetConst_Command

LetConst_Command::LetConst_Command (string variableName, ArithmeticExpression *ae1)
{
  _ae1 = ae1;
  variable = variableName;
}

LetConst_Command::~LetConst_Command ()
{
  delete _ae1;
}
  
void LetConst_Command::print (std::ostream & o) const
{
  o << "LET " << variable << " ";
  _ae1->print (o);
}

void LetConst_Command:: execute (vector<Line*> &program, map<string,int> &varMap, stack<LineNumber*> &retStack, vector<Line*>::iterator &theIt, std::ostream &outStream) 
{
  // add/replace a variable to map with specific value
  // cout << "In LetConst execute" << endl;

  // check if variable is already in map???

  // map should have ints not expressions!

  varMap[variable] = _ae1 -> getValue(varMap);
  theIt++;
}

// LetArray_Command

LetArray_Command::LetArray_Command (string variableName, ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
  variable = variableName;
}

LetArray_Command::~LetArray_Command ()
{
  delete _ae1;
  delete _ae2;
}
  
void LetArray_Command::print (std::ostream & o) const
{
  o << "LET " << variable << "["; 
  _ae1->print (o);
  o << "] ";
  _ae2->print (o);
}

void LetArray_Command::execute (vector<Line*> &program, map<string, int> &varMap, stack<LineNumber*> &retStack, vector<Line*>::iterator &theIt, std::ostream &outStream) 
{
  // FILL IN when array plan is made
  theIt++;
}


// Goto_Command

Goto_Command::Goto_Command (LineNumber *num)
{
  _num = num;
}

Goto_Command::~Goto_Command ()
{
  delete _num;
}
  
void Goto_Command::print (std::ostream & o) const
{
  o << "GOTO <";
  _num->print (o);
  o << ">";
}

void Goto_Command::execute (vector<Line*> &program, map<string, int> &varMap, stack<LineNumber*> &retStack, vector<Line*>::iterator &theIt, std::ostream &outStream)
{
  // move iterator to the point that matches the given line
  moveToLine(program, theIt, _num->line);
  // cout << "returned from moveToLine" << endl;

}


// IfThen_Command

IfThen_Command::IfThen_Command (LineNumber *num, BooleanExpression *be1)
{
  _num = num;
  _be1 = be1;
}

IfThen_Command::~IfThen_Command ()
{
  delete _num;
  delete _be1;
}
  
void IfThen_Command::print (std::ostream & o) const
{
  o << "IF ";
  _be1->print (o);
  o << " THEN <";
  _num->print(o);
  o << ">";
}

void IfThen_Command:: execute (vector<Line*> &program, map<string, int> &varMap, stack<LineNumber*> &retStack, vector<Line*>::iterator &theIt, std::ostream &outStream)
{
  // cout << "Entering If execute" << endl;
  // if the boolean expression results to true, move the iterator
  if (_be1 -> getValue(varMap))
  {
    // cout << "about to call MoveToLine in IFTHEN" << endl;
    moveToLine(program, theIt, _num->line);
    // cout << "iterator moved" << endl;
  }
  else
  {
      theIt++;
  }
}



// Gosub_Command

Gosub_Command::Gosub_Command (LineNumber *num1, LineNumber *num2)
{
  _num1 = num1;
  _num2 = num2;
}

Gosub_Command::~Gosub_Command ()
{
  // delete _num1;
  // don't delete num1 because the Line destructor will delete it
  delete _num2;
}
  
void Gosub_Command::print (std::ostream & o) const
{
  o << "GOSUB <";
  _num2->print (o);
  o << ">";
}

void Gosub_Command:: execute (vector<Line*> &program, map<string, int> &varMap, stack<LineNumber*> &retStack, vector<Line*>::iterator &theIt, std::ostream &outStream)
{
  // put the line you came from on return stack and go to indidcated line
  retStack.push(_num1);
  moveToLine(program, theIt, _num2->line);
}

// Return_Command

void Return_Command::print (std::ostream & o) const
{
	o << "RETURN";
}

Return_Command::Return_Command()
{

}

Return_Command::~Return_Command()
{

}

void Return_Command:: execute (vector<Line*> &program, map<string, int> &varMap, stack<LineNumber*> &retStack, vector<Line*>::iterator &theIt, std::ostream &outStream)
{
  // go to the the line AFTER the most recent GOSUB line
  // find and remove the last gosub from the stack
  LineNumber* lastGoSub = retStack.top();
  retStack.pop();
  moveToLine(program, theIt, lastGoSub->line);
  theIt++;
}

// End_Command

End_Command::End_Command()
{
  
}

End_Command::~End_Command()
{
  
}

void End_Command::print (std::ostream & o) const
{
	o << "END";
}

void End_Command::execute (vector<Line*> &program, map<string, int> &varMap, stack<LineNumber*> &retStack, vector<Line*>::iterator &theIt, std::ostream &outStream)
{
  // terminate program
  theIt++;
  if (theIt == program.end())
  {
    // the program is over...
  }
  else
  {
    // end in middle of program, throw exception?
  }
}