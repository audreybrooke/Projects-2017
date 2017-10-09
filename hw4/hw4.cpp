#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
//#include "Command.h"
#include "ArithmeticExpression.h"
#include <stack>
#include <stdio.h>
#include <ctype.h>
#include <algorithm>
#include <cstddef>
#include <string>

using namespace std;

ArithmeticExpression* readAExpression (string ss);


int main(int argc, char* argv[])
{
  if(argc < 2){
    // REMOVE THIS!

    ArithmeticExpression* exp = readAExpression("(Value[(5* int[4])]   +8)");
    exp->print(cout);
    cout << endl;

    //
    cerr << "Please provide an input file." << endl;
    return 1;
  }
  ifstream input(argv[1]);

  if (input.fail())
  {
    cerr << "Please provide a valid file." << endl;
  }

  string curr; // the current line

  /*
  //loop to read all lines of the program
  while(getline(input, curr)) {
    stringstream ss;
    ss << curr;
    string command; // the command
    unsigned int line;  // the line number
    
    ss >> line;
    ss >> command;
    if (command == "PRINT") {
      // you obviously need to put a lot of stuff here and in the other cases
      // build a Print_Command object

      ArithmeticExpression* arex;
      string tString;
      getline (ss, tString);
      arex = readAExpression (tString);
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


  */
  return 0;
}

ArithmeticExpression* readAExpression (string ss)
{

  // go char by char
  // add to stack
  // if you hit operator or ( or [
  // pop everything and make it a string
  // reverse the string
  // check if its an int
  // make const or variable
  // BUT if [ make array
    // name variable name
    // push [ on operator stack
  // if ] 
    // peek operator stack -- if its is [ pop
    // pop arithmetic expression stack and make that the index
    // push array object on arithmetic expresion stack
  // if operatot +-/*
    // store operator
    // pop from char stack and make and push a var or const
  // if operator is )
    // pop 2 objects from arithemtic stack
    // switch "order" and create object correspoding to operator that is stored

  //creates the stacks

  stack<char> operatorStack;
  stack<ArithmeticExpression*> aeStack;
  stack<char> variablesStack;
  string arrayVariableName;
  
  for (int i = 0; i < (int)ss.length(); ++i)
  {
    // go char by char

    char theChar = ss[i];
    // determine what type theChar is and handle appropriately
    // cout << "on char: " << theChar << endl;
    // cout << "aeStack size is " << aeStack.size() << endl;

    if (theChar == ' ')
    {
      /* do nothing */
    }
    else if (theChar == '(')
    {
      // 
    }
    else if (theChar == '[')
    {
      // pop everything in variable stack and make it variable name
      string theV = "";
      
      while ((int)variablesStack.size() > 0)
      {
        theV+= variablesStack.top();
        variablesStack.pop();
      }

      reverse(theV.begin(), theV.end());
      arrayVariableName = theV;
      // !!! this will not work if the index expression contains another array


      // push [ on char stack to signify that the expression until ]
      // is the index of the array with name theV

      operatorStack.push('[');

    }
    else if (theChar == ')')
    {
      // 2 parts of the expression are being operated on!
      // pop 2 objects from expression stack, reverse them
      // and use corresponding operator to create new object

      if (! variablesStack.empty())
      {
        // make new variable / char and add it to expression stack
        string theV = "";
       
       while ((int)variablesStack.size() > 0)
       {
         theV+= variablesStack.top();
         variablesStack.pop();
       }
       reverse(theV.begin(), theV.end());

       if (theV.find_first_not_of("0123456789") == string::npos)
       {
          // string is entirely numbers, thus it is a constant
         ArithmeticExpression* theConst = new Constant (atoi(theV.c_str()));
          aeStack.push(theConst);
        }
        else
        {
          // string is a variable name
          ArithmeticExpression* theVariable = new Variable (theV);
          aeStack.push(theVariable);
       }
      }

      ArithmeticExpression* lhs = aeStack.top();
      aeStack.pop();
      ArithmeticExpression* rhs = aeStack.top();
      aeStack.pop();
      char theOperator = operatorStack.top();
      operatorStack.pop();
      ArithmeticExpression* tooAdd;

      cout << "the operator is " << theOperator << endl;


      if (theOperator == '+')
      {
        tooAdd = new Addition (rhs, lhs);
      }
      else if (theOperator == '-')
      {
        tooAdd = new Subtraction (rhs, lhs);
      }
      else if (theOperator == '*')
      {
        tooAdd = new Multiplication (rhs, lhs);
      }
      else if (theOperator == '/')
      {
        tooAdd = new Division (rhs, lhs);
      }
      else
      {
        cerr << "invalid operator:" << theOperator << endl;
      }

      aeStack.push(tooAdd);

    }
    else if (theChar == ']')
    {
      // peek operator stack, look for [
      if (operatorStack.top() == '[')
      {
        operatorStack.pop();
        // pop arithmetic expression
        // make that the index
        // push array on aeStack


      if (! variablesStack.empty())
      {
        // make new variable / char and add it to expression stack
        string theV = "";
       
       while ((int)variablesStack.size() > 0)
       {
         theV+= variablesStack.top();
         variablesStack.pop();
       }
       reverse(theV.begin(), theV.end());

       if (theV.find_first_not_of("0123456789") == string::npos)
       {
          // string is entirely numbers, thus it is a constant
         ArithmeticExpression* theConst = new Constant (atoi(theV.c_str()));
          aeStack.push(theConst);
        }
        else
        {
          // string is a variable name
          ArithmeticExpression* theVariable = new Variable (theV);
          aeStack.push(theVariable);
       }
      }

        ArithmeticExpression* index = aeStack.top();
        aeStack.pop();

        cout << endl << "arrray name is: " << arrayVariableName << endl;
        ArithmeticExpression* theArray = new ArrayVariable (arrayVariableName, index);
        aeStack.push(theArray);
      }
    }
    else if (theChar == '+' || theChar == '-' || theChar == '*' || theChar == '/')
    {
      // store operator
      // make the char stack into a variable or constant
      // push that on the expression stack

      operatorStack.push(theChar);
      cout << "just pushed " << theChar << " on Operator stack" << endl;

      if (!variablesStack.empty())
      {
        string theV = "";
        cout << "variablesStack not empty" << endl; 
      
        while ((int)variablesStack.size() > 0)
        {
          theV+= variablesStack.top();
          variablesStack.pop();
        }
        reverse(theV.begin(), theV.end());

        if (theV.find_first_not_of("0123456789") == string::npos)
        {
          // string is entirely numbers, thus it is a constant
          ArithmeticExpression* theConst = new Constant (atoi(theV.c_str()));
          aeStack.push(theConst);
       }
       else
       {
         // string is a variable name
         ArithmeticExpression* theVariable = new Variable (theV);
          aeStack.push(theVariable);
       }
      }

    }
    else if (isdigit(theChar) || isalpha(theChar))
    {
      // add digit or letter to variable stack
      variablesStack.push(theChar);
    }
    else
    {
      cerr << "Invalid input" << endl;
      // could throw exception so that correct line number is printed
    }

  }


return aeStack.top();





/*


  if (item[0] != "(")
  {
    // just 1 "thing", variable or constant
    if (item.find_first_not_of("0123456789") == string::npos)
    {
      // checks if the string is a number (int)
      ArithmeticExpression* theConst = new Constant ((int)item);
      // returns the constant
      return theConst;
    }

    else if (item.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos)
    {
      // item exists soley of letters
      // it is a variable

      if (ss.eof())
      {
        // not an array
         ArithmeticExpression* theVariable = new Variable(item);
        // retuns the variable
        return theVariable;
      }
      else if (ss.peek() == '[')
      {
        // array with space between var and []
        string variableName = item;
        string thisAEX;
        getline(ss, thisAEX, ']');
        thisAEX.substr(1);
        stringstream ll << thisAEX;
        ArithmeticExpression* index = readAExpression(ll);
        // create array object
      }

    }
    else
    {
      // item is an Array with no space
      string variableName = item.substr(0, '[');

    }
  }

  while (item << ss)
  {
    
    if (item.find_first_not_of("0123456789") == string::npos)
    {
      // checks if the string is a number (int)
      ArithmeticExpression* theConst = new Constant ((int)item);
      // pushes the constant on the stack
      theStack.push(theConst);
    }

    else if (item.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos)
    {
      // item exists soley of letters
      // it is a variable
      ArithmeticExpression* theVariable = new Variable(item);
      // pushes the variable on the stackn
      theStack.push(theVariable);

    }

    else
    {
      // item is an operator

      // push operator on stack as an indicator
      ArithmeticExpression* openParen = new Variable(item);


    }
  }
  */
}