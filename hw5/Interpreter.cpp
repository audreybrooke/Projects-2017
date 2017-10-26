#include "Interpreter.h"

using namespace std;

Interpreter::Interpreter(vector<Line*> prg)
{
  theProgram = prg;
}

Interpreter::~Interpreter()
{
	
}

// void Interpreter::moveToLine(int goTo)
// {
//   for (theIterator = theProgram.begin(); theIterator != theProgram.end(); theIterator++)
//   {
//     if (*theIterator -> ln -> line == goTo)
//     {
//       // found the location to jump to, leave iterator here
//       break;
//     }
//   }

//   // line number not found!
//   // THROW EXCEPTION!
// }


void Interpreter::runProgram(std::ostream& out)
{
	// set iterator to the begining of the program (first line)
	theIterator = theProgram.begin();

	while (theIterator != theProgram.end())
	{
		(*theIterator) -> com -> execute(theProgram, variableMap, returnStack, theIterator, out);
		// send ostream, variableMap, returnStack and iterator by reference
	}	
}