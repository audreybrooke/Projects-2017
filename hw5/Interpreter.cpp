#include "Interpreter.h"
#include <exception>
#include <stdexcept>
#include <sstream>

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

	try{

		while (theIterator != theProgram.end())
		{
			(*theIterator) -> com -> execute(theProgram, variableMap, returnStack, theIterator, out, arrayNames, arrayVariableMap);
			// send ostream, variableMap, returnStack and iterator by reference
		}

	}
	catch (logic_error &e) {

		//cout << "caught 'logic' error" << endl;

		int index = (*theIterator) -> ln -> line;
  		stringstream ss;
  		ss << index;
 		string str = ss.str();

		out << "Error in Line " << str << ": " << e.what() << endl;
	}
	catch (end_call &e) {
		return;
	}
	catch (divide_by_zero &e) {

		int index = (*theIterator) -> ln -> line;
  		stringstream ss;
  		ss << index;
 		string str = ss.str();

		out << "Error in Line " << str << ": " << e.what()<< endl;
	}
	catch(exception &e) {
		out << "General Exception" << endl;
	}
}