#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "Interpreter.h"
#include <stack>
#include <stdio.h>
#include <ctype.h>
#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

using namespace std;

ArithmeticExpression* readAExpression (string ss);
BooleanExpression* readBExpression (string ss);


int main(int argc, char* argv[])
{
  if(argc < 2){
    // REMOVE THIS!

    //ArithmeticExpression* exp = readAExpression("(Value[(5* int[4])]   +8)");
    //exp->print(cout);
    //cout << endl;

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
  vector<Line*> theProgram;

  
  //loop to read all lines of the program
  while(getline(input, curr)) {
    stringstream ss;
    ss << curr;
    string command; // the command
    unsigned int line;  // the line number
    
    ss >> line;
    ss >> command;
    LineNumber* tLine = new LineNumber(line);

    //cout << "On line: " << line << endl;


    if (command == "PRINT") {
      // you obviously need to put a lot of stuff here and in the other cases
      // build a Print_Command object

      // cout << "found a print command: " << endl;

      ArithmeticExpression* arex;
      string tString; // remaining portion of the line
      getline (ss, tString);
      arex = readAExpression (tString);
      Command* printCom = new Print_Command(arex);
      Line* newLine = new Line (tLine, printCom); 
      // ^ is the line object for this line of orig code
      theProgram.push_back(newLine);

    }
    else if (command == "LET") {
      // check if variable is array or int
      string var;
      ss >> var;
      char c;
      ss.get(c);

      while (c == ' ')
      {
        // do nothing
        ss.get(c);
      }


      if (c == '[')
      {

        // use Let array class
        string tString; // remaining portion of the line
        getline (ss, tString);
        tString= tString;
        string exp1, exp2;

        // !!NOT PERFECT!! WHAT IF EXPRESSION HAS ] IN IT
        int found = tString.find(']');
        exp1 = tString.substr(0, found); // index
        exp2 = tString.substr(found+1, tString.length()); //new value
        ArithmeticExpression* index = readAExpression(exp1);
        ArithmeticExpression* newValue = readAExpression(exp2);
        Command* letArrCom = new LetArray_Command(var, index, newValue);
        Line* newLine = new Line (tLine, letArrCom);
        theProgram.push_back(newLine);

      }

      else
      {
        // use Let const class

      ArithmeticExpression* arex;
      string tString; // remaining portion of the line
      getline (ss, tString);
      tString = c + tString;
      arex = readAExpression (tString);
      Command* LetConstCom = new LetConst_Command(var, arex);
      Line* newLine = new Line (tLine, LetConstCom); 
      // ^ is the line object for this line of orig code
      theProgram.push_back(newLine);

      }
    }
    else if (command == "GOTO") {
      int goToThisLine;
      ss >> goToThisLine;
      LineNumber* goToLineNumberObj = new LineNumber (goToThisLine);
      Command* GoToCom = new Goto_Command(goToLineNumberObj);
      Line* newLine = new Line (tLine, GoToCom);
      theProgram.push_back(newLine);

    }
    else if (command == "IF") {

      string tString; // remaining portion of the line
      getline (ss, tString);
      int found = tString.find("THEN");
      string be = tString.substr(0, found);
      string goToLine = tString.substr(found+4, tString.length());
      LineNumber* goToLineNumberObj = new LineNumber (atoi(goToLine.c_str()));
      BooleanExpression* boep = readBExpression(be);
      Command* IfThenCom = new IfThen_Command(goToLineNumberObj, boep);
      Line* newLine = new Line (tLine, IfThenCom);
      theProgram.push_back(newLine);
    }
    else if (command == "GOSUB") {
      int goToThisLine;
      ss >> goToThisLine;
      LineNumber* goToLineNumberObj = new LineNumber (goToThisLine);
      Command* GoSubCom = new Gosub_Command(tLine, goToLineNumberObj);
      Line* newLine = new Line (tLine, GoSubCom);
      theProgram.push_back(newLine);
    }
    else if (command == "RETURN") {
      Command* returnCom = new Return_Command();
      Line* newLine = new Line (tLine, returnCom);
      theProgram.push_back(newLine);
    }
    else if (command == "END") {
      Command* endCom = new End_Command();
      Line* newLine = new Line (tLine, endCom);
      theProgram.push_back(newLine);
    }
    else {
      // This should never happen - print an error?
      cerr << "Invalid Command at line " << line << endl;
    }
  }



  // finished reading through program

  // print out vector of line objects to output file

  for (int i = 0; i < (int) theProgram.size(); ++i)
  {
    Line* thisLine = theProgram[i];
    thisLine -> ln -> print(cout);
    cout << " ";
    thisLine -> com -> print(cout);
    cout << endl;
  }

  // run through program and execute commands, output goes to cout
  Interpreter* interpretProgram = new Interpreter(theProgram);
  interpretProgram -> runProgram(cout);



  // memory handling
  int counter = theProgram.size();

  while (theProgram.size() > 0)
  {
    Line* toDelete = theProgram[counter-1];
    theProgram.pop_back();
    delete toDelete;
    counter--;
  }
  

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
  stack <string> arrayVariableName;
  
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
      arrayVariableName.push(theV);
      // cout << "pushed array name on stack" << endl;


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

      if (!operatorStack.empty())
      {
        ArithmeticExpression* lhs = aeStack.top();
       aeStack.pop();
       ArithmeticExpression* rhs = aeStack.top();
       aeStack.pop();
       char theOperator = operatorStack.top();
       operatorStack.pop();
       ArithmeticExpression* tooAdd;

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

      

      // cout << "the operator is " << theOperator << endl;




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

        // cout << endl << "arrray name is: " << arrayVariableName << endl;
        // cout << "trying to create theArray object" << endl;
        ArithmeticExpression* theArray = new ArrayVariable (arrayVariableName.top(), index);
        arrayVariableName.pop();
        // cout << "created theArray object" << endl;
        aeStack.push(theArray);
      }
    }
    else if (theChar == '+' || theChar == '-' || theChar == '*' || theChar == '/')
    {
      // store operator
      // make the char stack into a variable or constant
      // push that on the expression stack

      operatorStack.push(theChar);
      // cout << "just pushed " << theChar << " on Operator stack" << endl;

      if (!variablesStack.empty())
      {
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

    }
    else if (isdigit(theChar) || isalpha(theChar))
    {
      // add digit or letter to variable stack
      variablesStack.push(theChar);
    }
    else
    {
      // cerr << "Invalid input:" << theChar << endl;
      // could throw exception so that correct line number is printed
    }

  }

  if (aeStack.empty() && !variablesStack.empty())
  {
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

  ArithmeticExpression* toReturn = aeStack.top();

  return toReturn;

}











BooleanExpression* readBExpression (string ss)
{
  int found = ss.find("=");
  ArithmeticExpression* aexpr1;
  ArithmeticExpression* aexpr2;
  string a1, a2;
  BooleanExpression* toReturn;

  
  if (found != (int) string::npos)
  {
    // it is  an = expr

    a1 = ss.substr(0, found);
    a2 = ss.substr(found+1, ss.length());
    aexpr1 = readAExpression(a1);
    aexpr2 = readAExpression(a2);
    toReturn = new Equal (aexpr1, aexpr2);
  }
  else
  {
    // not an = expr, see if it is >
    found = ss.find(">");
    if (found != (int) string::npos)
    {
      // it is a > expr
      a1 = ss.substr(0, found);
      a2 = ss.substr(found+1, ss.length());
      aexpr1 = readAExpression(a1);
      aexpr2 = readAExpression(a2);
      // Less than with terms flipped is a greater than!
      toReturn = new LessThan (aexpr2, aexpr1);

    }
    else
    {
      // not a = OR > expr
      found = ss.find("<");
      if (found != (int) string::npos)
      {
        // is a < expression


        a1 = ss.substr(0, found);
        a2 = ss.substr(found+1, ss.length());
        
        aexpr1 = readAExpression(a1);
        aexpr2 = readAExpression(a2);
        toReturn = new LessThan (aexpr1, aexpr2);
      }
      else
      {
        // NOT a =, > OR < expr
        cerr << "No comparison for boolean expression" << endl;
        // potential throw exception so line # can be printed
        toReturn = NULL;
      }
    }
  }

  return toReturn;
}