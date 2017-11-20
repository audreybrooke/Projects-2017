#include "avlbst.h"
#include "Command.h"
#include "RecursiveParser.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

typedef AVLTree<string, string>* stringMap;
typedef AVLTree<int, int>* intMap;

// function signatures
void createLineMapping(vector<Command*>& linesPrg1, vector<Command*>& 
	linesPrg2, intMap& linesMap1to2);
bool checkCheating(stringMap& variablesMap, stringMap& 
	arrayVariablesMap, intMap& linesMap, vector<Command*>& 
	linesPrg1, vector<Command*>& linesPrg2);
bool compareLine(int p1Dest, int p2Dest, intMap& linesMap);
bool compareBE(BooleanExpression* p1Bool, BooleanExpression* p2Bool, 
	stringMap variablesMap, stringMap arrayVariablesMap);
bool compareAE(ArithmeticExpression* p1AE, ArithmeticExpression* p2AE, 
	stringMap variablesMap, stringMap arrayVariablesMap);
bool compareVar(VariableArithmeticExpression* p1V, VariableArithmeticExpression* 
	p2V, stringMap variablesMap, stringMap arrayVariablesMap);

int main(int argc, char const *argv[])
{
	// check input
	if (argc < 3)
	{
		cout << "please provide 2 file names" << endl;
	}

	ifstream prg1 (argv[1]);
	ifstream prg2 (argv[2]);

	if (prg1.fail() || prg2.fail())
	{
		cout << "please provide valid file/s" << endl;
	}

	// create the parsers for program 1 and 2
	RecursiveParser* program1 = new RecursiveParser(prg1);
	RecursiveParser* program2 = new RecursiveParser(prg2);

	// maps that track the matching for line numbers,
	// array variables and int variables
	stringMap variablesMap1to2 = new AVLTree <string, string>();
	stringMap arrayVariablesMap1to2 = new AVLTree <string, string>();
	intMap linesMap1to2 = new AVLTree <int, int>();

	// find line number mapping
	vector<Command*> linesPrg1 = program1->GetCommands();
	vector<Command*> linesPrg2 = program2->GetCommands();
	if (linesPrg1.size() != linesPrg2.size())
	{
		cout << "not cheating" << endl;
		return 0;
	}	
	createLineMapping(linesPrg1, linesPrg2, linesMap1to2);

	// check variables / line numbers
	bool answer = checkCheating(variablesMap1to2, arrayVariablesMap1to2, 
		linesMap1to2, linesPrg1, linesPrg2);

	if (!answer)
	{
		cout << "not cheating" << endl;
	}
	else
	{
		// there was cheating
		cout << "cheating" << endl;
		// print mapping!!!
	}

	delete program1;
	delete program2;


	return 0;
}

void createLineMapping(vector<Command*>& linesPrg1, vector<Command*>& 
	linesPrg2, intMap& linesMap1to2)
{
	for (int i = 0; i < (int) linesPrg1.size(); ++i)
	{
		Command* prg1Line = linesPrg1[i];
		Command* prg2Line = linesPrg2[i];
		int p1Num = prg1Line->GetLineNumber();
		int p2Num = prg2Line->GetLineNumber();
		linesMap1to2->insert(pair<int, int> (p1Num, p2Num));
	}
}

/*
* Creates/checks the mapping between both programs.
* Returns true if cheating is detected
*/
bool checkCheating(stringMap& variablesMap, stringMap& 
	arrayVariablesMap, intMap& linesMap, vector<Command*>& 
	linesPrg1, vector<Command*>& linesPrg2)
{


	for (int i = 0; i < (int) linesPrg1.size(); ++i)
	{
		string commandId1 = linesPrg1[i]->GetClassId();
		string commandId2 = linesPrg2[i]->GetClassId();
		if (commandId1 != commandId2) return false;
		else if (commandId1 == "PrintCommand")
		{
			ArithmeticExpression* p1AE = linesPrg1[i]->GetArithmeticExpression();
			ArithmeticExpression* p2AE = linesPrg2[i]->GetArithmeticExpression();
			bool aeResult = compareAE(p1AE, p2AE, variablesMap, arrayVariablesMap);
			if (!aeResult) return false;
		}
		else if (commandId1 == "LetCommand")
		{
			// compare the variables
			VariableArithmeticExpression* p1V = linesPrg1[i]->
			GetVariableExpression();
			VariableArithmeticExpression* p2V = linesPrg2[i]->
			GetVariableExpression();
			bool vResult = compareVar(p1V, p2V, variablesMap, arrayVariablesMap);
			if (!vResult) return false;

			// compare the AExps
			ArithmeticExpression* p1AE = linesPrg1[i]->GetArithmeticExpression();
			ArithmeticExpression* p2AE = linesPrg2[i]->GetArithmeticExpression();
			bool aeResult = compareAE(p1AE, p2AE, variablesMap, arrayVariablesMap);
			if (!aeResult) return false;
		}
		else if (commandId1 == "GoToCommand")
		{
			// compare destination lines
			int p1Dest = linesPrg1[i]->GetDstLine();
			int p2Dest = linesPrg2[i]->GetDstLine();
			bool lResult = compareLine(p1Dest, p2Dest, linesMap);
			if (!lResult) return false;

		}
		else if (commandId1 == "IfThenCommand")
		{
			// compare destination lines
			int p1Dest = linesPrg1[i]->GetDstLine();
			int p2Dest = linesPrg2[i]->GetDstLine();
			bool lResult = compareLine(p1Dest, p2Dest, linesMap);
			if (!lResult) return false;

			// compare boolean expressions
			BooleanExpression* p1Bool = linesPrg1[i]->GetBooleanExpression();
			BooleanExpression* p2Bool = linesPrg2[i]->GetBooleanExpression();
			bool bResult = compareBE(p1Bool, p2Bool, variablesMap, arrayVariablesMap);
			if (!bResult) return false;
		}
		else if (commandId1 == "GoSubCommand")
		{
			// compare destination lines
			int p1Dest = linesPrg1[i]->GetDstLine();
			int p2Dest = linesPrg2[i]->GetDstLine();
			bool lResult = compareLine(p1Dest, p2Dest, linesMap);
			if (!lResult) return false;
		}
		// no need to check return or end commands because they have no
		// members to compare, their type is compared in the first if.
	}

	return true;
}

// compare functions only return false if they know that there was definitely
// not cheating

/*
* checks if 2 lines are "equivalent" in the program matching
* if not returns false
*/
bool compareLine(int p1Dest, int p2Dest, intMap& linesMap)
{
	if (*(linesMap->find(i)).getValue() != p2Dest)
		return false;
	/*
	if (linesMap[i] != p2Dest)
		return false;
	*/
	return true;
}


/*
* checks if 2 BooleanExpressions are "equivalent." If not, returns false.
*/
bool compareBE(BooleanExpression* p1Bool, BooleanExpression* p2Bool, 
	stringMap variablesMap, stringMap arrayVariablesMap)
{
	if(p1Bool->GetClassId() != p2Bool->GetClassId())
		return false;

	ArithmeticExpression* rhs1 = p1Bool->GetRhs();
	ArithmeticExpression* lhs1 = p1Bool->GetLhs();
	ArithmeticExpression* rhs2 = p2Bool->GetRhs();
	ArithmeticExpression* lhs2 = p2Bool->GetLhs();

	bool rhsComp = compareAE(rhs1, rhs2, variablesMap, arrayVariablesMap);
	bool lhsComp = compareAE(lhs1, lhs2, variablesMap, arrayVariablesMap);

	if (!rhsComp || !lhsComp)
	{
		return false;
	}

	return true;
}


/*
* checks if 2 Variables are "equivalent." If not, returns false.
*/
bool compareVar(VariableArithmeticExpression* p1V, VariableArithmeticExpression* 
	p2V, stringMap variablesMap, stringMap arrayVariablesMap)
{
	string type1 = p1v->GetClassId();
	string type2 = p2V->GetClassId()
	if (type1 != type2)
	{
		return false;
	}

	if (type1 == "IntVariableArithmeticExpression")
	{
		// variable is an int

		IntVariable* 1IntVar = p1V->GetIntVariable();
		IntVariable* 2IntVar = p2V->GetIntVariable();
		string 1varName = 1IntVar->GetName();
		string 2varName = 2IntVar->GetName();

		if (variablesMap->find(1varName) != variablesMap->end())
		{
			// this mapping exists
			if (*(variablesMap->find(1varName))->getValue() != 2varName)
			{
				// this variable does not map to the same name it did before
				return false;
			}
		}
		else
		{
			// mapping does not exist yet, add it to the map
			variablesMap->insert(pair<string, string>(1varName, 2varName));
		}
	}
	else
	{
		// variable is an array

		// check if index value is the same
		ArithmeticExpression* index1 = p1v->GetArrayIndex();
		ArithmeticExpression* index2 = p2v->GetArrayIndex();
		if (! compareAE(index1, index2, variablesMap, arrayVariablesMap)) return false;

		// check if array name is the same
		ArrayVariable* 1ArrVar = p1v->GetArrayVariable();
		ArrayVariable* 2ArrVar = p2v->GetArrayVariable();
		string 1arrName = 1ArrVar->GetName();
		string 2arrName = 2ArrVar->GetName();
		if (arrayVariablesMap->find(1arrName) != arrayVariablesMap->end())
		{
			// this mapping exists
			if (*(arrayVariablesMap->find(1ArrVar))->getValue != 2arrName)
			{
				// variable does not map to same name as it did before
				return false;
			}
		}
		else
		{
			// mapping does not exist yet, add it to the map
			arrayVariablesMap->insert(pair<string, string>(1arrName, 2arrName));
		}
	}

	return true;
	
}




bool compareAE(ArithmeticExpression* p1AE, ArithmeticExpression* p2AE, 
	stringMap variablesMap, stringMap arrayVariablesMap)
{
	// determine which type of Arithmetic expression it is
	string type1 = p1AE->GetClassId();
	string type2 = p2AE->GetClassId();
	if (type1 != type2)
	{
		return false;
	}


	else if (type1 == "ConstantArithmeticExpression")
	{
		/* code */
	}
	else if (type1 == "IntVariableArithmeticExpression")
	{
		/* code */
	}
	else if (type1 == "ArrayVariableArithmeticExpression")
	{
		/* code */
	}
	else if (type1 == "AdditionExpression")
	{
		/* code */
	}
	else if (type1 == "SubtractionExpression")
	{
		/* code */
	}
	else if (type1 == "")
	{
		/* code */
	}
	else if (type1 == "")
	{
		/* code */
	}
}




/*


ArithmeticExpression.o: ArithmeticExpression.cpp ArithmeticExpression.h
	g++ -g -Wall -c ArithmeticExpression.cpp -o ArithmeticExpression.o

BooleanExpression.o: BooleanExpression.cpp BooleanExpression.h
	g++ -g -Wall -c BooleanExpression.cpp -o BooleanExpression.o

Command.o: Command.cpp Command.h
	g++ -g -Wall -c Command.cpp -o Command.o

RecursiveParser.o: RecursiveParser.cpp RecursiveParser.h
	g++ -g -Wall -c RecursiveParser.cpp -o RecursiveParser.o


*/