#include "Command.h"
#include <map>
#include <set>
#include <stack>
#include <vector>

using namespace std;



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

void Print_Command::execute(Interpreter &theI)
{
  (theI.outputStream) << _ae1 -> getValue();
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

void LetConst_Command::execute(Interpreter &theI) 
{
  // add/replace a variable to map with specific value
  theI.variableMap[variable] = _ae1;
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

void LetArray_Command::execute(Interpreter &theI) 
{
  // FILL IN when array plan is made
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

void Goto_Command::execute(Interpreter &theI)
{
  // move iterator to the point that matches the given line
  theI.moveToLine(_num->line);

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

void IfThen_Command::execute(Interpreter &theI)
{
  // if the boolean expression results to true, move the iterator
  if (_be1 -> getValue())
  {
    theI.moveToLine(_num->line);
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

void Gosub_Command::execute(Interpreter &theI)
{
  // put the line you came from on return stack and go to indidcated line
  theI.returnStack.push(_num1);
  theI.moveToLine(_num2->line);
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

void Return_Command::execute(Interpreter &theI)
{
  // go to the the line AFTER the most recent GOSUB line
  // find and remove the last gosub from the stack
  LineNumber* lastGoSub = theI.returnStack.top();
  theI.returnStack.pop();
  theI.moveToLine(lastGoSub->line);
  theI.theIterator++;
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

void End_Command::execute(Interpreter &theI)
{
  // terminate program
  if (++(theI.theIterator) == theI.theProgram.end())
  {
    // the program is over...
  }
  else
  {
    // end in middle of program, throw exception?
  }
}