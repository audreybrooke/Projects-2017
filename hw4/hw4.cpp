#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <Command.h>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide an input file." << endl;
    return 1;
  }
  ifstream input(argv[1]);

  if (ifstream.fail())
  {
    cerr << "Please provide a valid file." << endl;
  }

  string curr; // the current line

  //loop to read all lines of the program
  while(getline(input, curr)) {
    stringstream ss << curr;
    string command; // the command
    unsigned int line;  // the line number
    
    ss >> line;
    ss >> command;
    if (command == "PRINT") {
      // you obviously need to put a lot of stuff here and in the other cases
      // build a Print_Command object

      ArithmeticExpression* arex;
      arex = readAExpression (ss);
      Command* printCom = new Print_Command(arex);

    }
    else if (command == "LET") {
      // check if variable is array or int
      string var;
      ss >> var;
      string peekChar = ss.peek();
      if (peekChar == "[")
      {
        // use Let array class

      }

      else
      {
        // use Let const class

      }
    }
    else if (command == "GOTO") {
    }
    else if (command == "IF") {
    }
    else if (command == "GOSUB") {
    }
    else if (command == "RETURN") {
    }
    else if (command == "END") {
    }
    else {
      // This should never happen - print an error?
      cerr << "Invalid Command at line " << line << endl;
    }
  }
  return 0;
}

ArithmeticExpression* readAExpression (istream & ss)
{
  // HELP THIS DOES NOT WORK!
  vector<ArithmeticExpression*> theStack;
  string item;

  while (item << ss)
  {
    
    if (item.find_first_not_of("0123456789") == string::npos)
    {
      // checks if the string is a number (int)
      ArithmeticExpression* theConst = new Constant ((int)item);
      theStack.push(theConst);
    }

    else if (item.find_first_not_of("+-*/") != string::npos)
    {
      // item has a non-operator / non-number element
      // it is a variable
      ArithmeticExpression* theVariable = new Variable(item);
      theStack.push(theVariable);

    }

    else
    {
      // item is an operator

      // push operator on stack as an indicator
      ArithmeticExpression* openParen = new Variable(item);


    }
  }
}