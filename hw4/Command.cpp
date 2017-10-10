#include "Command.h"

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