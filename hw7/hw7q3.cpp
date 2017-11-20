#include "avlbst.h"
#include "Command.h"
#include "BooleanExpression.h"
#include "ArithmeticExpression.h"
#include "Variable.h"
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
		return 0;
	}

	ifstream prg1 (argv[1]);
	ifstream prg2 (argv[2]);

	if (prg1.fail() || prg2.fail())
	{
		cout << "please provide valid file/s" << endl;
		return 0;
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
		vector<string> varNamesPrg1 = program1->GetIntVariables();
		vector<string> arrNamesPrg1 = program1->GetArrayVariables();

		int vari = 0;
		int arri = 0;
		while (vari < (int) varNamesPrg1.size() && arri < (int) arrNamesPrg1.size())
		{
			if (varNamesPrg1[vari] < arrNamesPrg1[arri])
			{
				string var2 = (*(variablesMap1to2->find(varNamesPrg1[vari]))).second;
				cout << varNamesPrg1[vari] << " " << var2 << endl;
				vari++;
			}
			else
			{
				string arr2 = (*(arrayVariablesMap1to2->find(arrNamesPrg1[arri]))).second;
				cout << arrNamesPrg1[arri] << " " << arr2 << endl;
				arri++;
			}
		}
		for (vari = vari; vari < (int) varNamesPrg1.size(); vari++)
		{
			string var2 = (*(variablesMap1to2->find(varNamesPrg1[vari]))).second;
			cout << varNamesPrg1[vari] << " " << var2 << endl;
		}
		for (arri = arri; arri < (int) arrNamesPrg1.size(); arri++)
		{
			string arr2 = (*(arrayVariablesMap1to2->find(arrNamesPrg1[arri]))).second;
			cout << arrNamesPrg1[arri] << " " << arr2 << endl;
		}
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
			PrintCommand* printC1 = (PrintCommand*) linesPrg1[i];
			ArithmeticExpression* p1AE = printC1->GetArithmeticExpression();
			ArithmeticExpression* p2AE = ((PrintCommand*)linesPrg2[i])->GetArithmeticExpression();
			bool aeResult = compareAE(p1AE, p2AE, variablesMap, arrayVariablesMap);
			if (!aeResult) return false;
		}
		else if (commandId1 == "LetCommand")
		{
			// compare the variables
			VariableArithmeticExpression* p1V = ((LetCommand*)linesPrg1[i])->
			GetVariableExpression();
			VariableArithmeticExpression* p2V = ((LetCommand*)linesPrg2[i])->
			GetVariableExpression();
			bool vResult = compareVar(p1V, p2V, variablesMap, arrayVariablesMap);
			if (!vResult) return false;

			// compare the AExps
			ArithmeticExpression* p1AE = ((LetCommand*)linesPrg1[i])->GetArithmeticExpression();
			ArithmeticExpression* p2AE = ((LetCommand*)linesPrg2[i])->GetArithmeticExpression();
			bool aeResult = compareAE(p1AE, p2AE, variablesMap, arrayVariablesMap);
			if (!aeResult) return false;
		}
		else if (commandId1 == "GoToCommand")
		{
			// compare destination lines
			int p1Dest = ((GoToCommand*)linesPrg1[i])->GetDstLine();
			int p2Dest = ((GoToCommand*)linesPrg2[i])->GetDstLine();
			bool lResult = compareLine(p1Dest, p2Dest, linesMap);
			if (!lResult) return false;

		}
		else if (commandId1 == "IfThenCommand")
		{
			// compare destination lines
			int p1Dest = ((IfThenCommand*)linesPrg1[i])->GetDstLine();
			int p2Dest = ((IfThenCommand*)linesPrg2[i])->GetDstLine();
			bool lResult = compareLine(p1Dest, p2Dest, linesMap);
			if (!lResult) return false;

			// compare boolean expressions
			BooleanExpression* p1Bool = ((IfThenCommand*)linesPrg1[i])->GetBooleanExpression();
			BooleanExpression* p2Bool = ((IfThenCommand*)linesPrg2[i])->GetBooleanExpression();
			bool bResult = compareBE(p1Bool, p2Bool, variablesMap, arrayVariablesMap);
			if (!bResult) return false;
		}
		else if (commandId1 == "GoSubCommand")
		{
			// compare destination lines
			int p1Dest = ((GoSubCommand*)linesPrg1[i])->GetDstLine();
			int p2Dest = ((GoSubCommand*)linesPrg2[i])->GetDstLine();
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
	if ((*(linesMap->find(p1Dest))).second != p2Dest)
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
	//if(p1Bool->GetClassId() != p2Bool->GetClassId())
	//	return false;

	string type1 = p1Bool->GetClassId();
	string type2 = p2Bool->GetClassId();

	ArithmeticExpression* rhs1 = ((BinaryBooleanExpression*)p1Bool)->GetRhs();
	ArithmeticExpression* lhs1 = ((BinaryBooleanExpression*)p1Bool)->GetLhs();
	ArithmeticExpression* rhs2 = ((BinaryBooleanExpression*)p2Bool)->GetRhs();
	ArithmeticExpression* lhs2 = ((BinaryBooleanExpression*)p2Bool)->GetLhs();


	if (type1 == type2)
	{

		bool rhsComp = compareAE(rhs1, rhs2, variablesMap, arrayVariablesMap);
		bool lhsComp = compareAE(lhs1, lhs2, variablesMap, arrayVariablesMap);
		
		if (!rhsComp || !lhsComp)
		{
			if (type1 == "EqualToExpression")
			{
				// could be "equivalent" if order is swithced
				// eq1 is lhs1 = rhs1
				// eq2 is lhs2 = rhs2
				// these are "equivalent" when: lhs1 = rhs2 and rhs1 = lhs2

				bool crossComp1 = compareAE(lhs1, rhs2, variablesMap, arrayVariablesMap);
				bool crossComp2 = compareAE(rhs1, lhs2, variablesMap, arrayVariablesMap);
				if (crossComp1 && crossComp2) return true;
			}
			return false;
		}
	}
	else if (type1 == "LessThanExpression" && type2 == "GreaterThanExpression")
	{
		// type1 is lhs1 < rhs1
		// type2 is lhs2 > rhs2
		// these are "equivalent" when: lhs1 = rhs2 and rhs1 = lhs2
		// aka lhs1 < rhs1 = lhs2 > rhs2

		bool crossComp1 = compareAE(lhs1, rhs2, variablesMap, arrayVariablesMap);
		bool crossComp2 = compareAE(rhs1, lhs2, variablesMap, arrayVariablesMap);
		if (crossComp1 && crossComp2) return true;
		return false;
	}
	else if (type2 == "LessThanExpression" && type1 == "GreaterThanExpression")
	{
		// type2 is lhs2 < rhs2
		// type1 is lhs1 > rhs1
		// these are "equivalent" when: lhs2 = rhs1 and rhs2 = lhs1
		// aka lhs2 < rhs2 = lhs1 > rhs1

		bool crossComp1 = compareAE(lhs1, rhs2, variablesMap, arrayVariablesMap);
		bool crossComp2 = compareAE(rhs1, lhs2, variablesMap, arrayVariablesMap);
		if (crossComp1 && crossComp2) return true;
		return false;
	}
	else if (type1 != type2)
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
	string type1 = p1V->GetClassId();
	string type2 = p2V->GetClassId();
	if (type1 != type2)
	{
		return false;
	}

	if (type1 == "IntVariableArithmeticExpression")
	{
		// variable is an int

		IntVariable* IntVar1 = ((IntVariableArithmeticExpression*)p1V)->GetIntVariable();
		IntVariable* IntVar2 = ((IntVariableArithmeticExpression*)p2V)->GetIntVariable();
		string varName1 = IntVar1->GetName();
		string varName2 = IntVar2->GetName();

		if (variablesMap->find(varName1) != variablesMap->end())
		{
			// this mapping exists
			if ((*(variablesMap->find(varName1))).second != varName2)
			{
				// this variable does not map to the same name it did before
				return false;
			}
		}
		else
		{
			// mapping does not exist yet, add it to the map
			// first, check if varName2 already is a value
			// iterate through mapping, check if any value
			// already equals varName2, if so, return false
			for (AVLTree<string, string>::iterator it = variablesMap->begin(); it != variablesMap->end(); ++it)
			{
				if ((*(it)).second == varName2) return false;
			}

			variablesMap->insert(pair<string, string>(varName1, varName2));
		}
	}
	else
	{
		// variable is an array

		// check if index value is the same
		ArithmeticExpression* index1 = ((ArrayVariableArithmeticExpression*)p1V)->GetArrayIndex();
		ArithmeticExpression* index2 = ((ArrayVariableArithmeticExpression*)p2V)->GetArrayIndex();
		if (! compareAE(index1, index2, variablesMap, arrayVariablesMap)) return false;

		// check if array name is the same
		ArrayVariable* ArrVar1 = ((ArrayVariableArithmeticExpression*)p1V)->GetArrayVariable();
		ArrayVariable* ArrVar2 = ((ArrayVariableArithmeticExpression*)p2V)->GetArrayVariable();
		string arrName1 = ArrVar1->GetName();
		string arrName2 = ArrVar2->GetName();
		if (arrayVariablesMap->find(arrName1) != arrayVariablesMap->end())
		{
			// this mapping exists
			if ((*(arrayVariablesMap->find(arrName1))).second != arrName2)
			{
				// variable does not map to same name as it did before
				return false;
			}
		}
		else
		{
			// mapping does not exist yet, add it to the map
			// first, check if arrName2 already is a value
			// iterate through mapping, check if any value
			// already equals arrName2, if so, return false
			for (AVLTree<string, string>::iterator it = arrayVariablesMap->begin(); it != arrayVariablesMap->end(); ++it)
			{
				if ((*(it)).second == arrName2) return false;
			}

			arrayVariablesMap->insert(pair<string, string>(arrName1, arrName2));
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
		int const1 = ((ConstantArithmeticExpression*)p1AE)->GetConstantValue();
		int const2 = ((ConstantArithmeticExpression*)p2AE)->GetConstantValue();
		if (const1 != const2) return false;
		return true;
	}
	else if (type1 == "IntVariableArithmeticExpression")
	{
		// variable is an int

		IntVariable* IntVar1 = ((IntVariableArithmeticExpression*)p1AE)->GetIntVariable();
		IntVariable* IntVar2 = ((IntVariableArithmeticExpression*)p2AE)->GetIntVariable();
		string varName1 = IntVar1->GetName();
		string varName2 = IntVar2->GetName();

		if (variablesMap->find(varName1) != variablesMap->end())
		{
			// this mapping exists
			if ((*(variablesMap->find(varName1))).second != varName2)
			{
				// this variable does not map to the same name it did before
				return false;
			}
		}
		else
		{
			// mapping does not exist yet, add it to the map
			// first, check if varName2 already is a value
			// iterate through mapping, check if any value
			// already equals varName2, if so, return false
			for (AVLTree<string, string>::iterator it = variablesMap->begin(); it != variablesMap->end(); ++it)
			{
				if ((*(it)).second == varName2) return false;
			}

			// mapping does not exist yet, add it to the map
			variablesMap->insert(pair<string, string>(varName1, varName2));
		
		}

		/*
		IntVariable* v1 = ((IntVariableArithmeticExpression*)p1AE)->GetIntVariable();
		IntVariable* v2 = ((IntVariableArithmeticExpression*)p2AE)->GetIntVariable();

		return compareVar(((VariableArithmeticExpression*)v1), ((VariableArithmeticExpression*)v2), variablesMap, arrayVariablesMap);
		*/
	}
	else if (type1 == "ArrayVariableArithmeticExpression")
	{

		// variable is an array

		// check if index value is the same
		ArithmeticExpression* index1 = ((ArrayVariableArithmeticExpression*)p1AE)->GetArrayIndex();
		ArithmeticExpression* index2 = ((ArrayVariableArithmeticExpression*)p2AE)->GetArrayIndex();
		if (! compareAE(index1, index2, variablesMap, arrayVariablesMap)) return false;

		// check if array name is the same
		ArrayVariable* ArrVar1 = ((ArrayVariableArithmeticExpression*)p1AE)->GetArrayVariable();
		ArrayVariable* ArrVar2 = ((ArrayVariableArithmeticExpression*)p2AE)->GetArrayVariable();
		string arrName1 = ArrVar1->GetName();
		string arrName2 = ArrVar2->GetName();
		if (arrayVariablesMap->find(arrName1) != arrayVariablesMap->end())
		{
			// this mapping exists
			if ((*(arrayVariablesMap->find(arrName1))).second != arrName2)
			{
				// variable does not map to same name as it did before
				return false;
			}
		}
		else
		{
			// mapping does not exist yet, add it to the map
			// first, check if arrName2 already is a value
			// iterate through mapping, check if any value
			// already equals arrName2, if so, return false
			for (AVLTree<string, string>::iterator it = arrayVariablesMap->begin(); it != arrayVariablesMap->end(); ++it)
			{
				if ((*(it)).second == arrName2) return false;
			}

			arrayVariablesMap->insert(pair<string, string>(arrName1, arrName2));
		}
	
		/*
		ArrayVariable* v1 = ((ArrayVariableArithmeticExpression*)p1AE)->GetArrayVariable();
		ArrayVariable* v2 = ((ArrayVariableArithmeticExpression*)p2AE)->GetArrayVariable();

		return compareVar(((VariableArithmeticExpression*)v1), ((VariableArithmeticExpression*)v2), variablesMap, arrayVariablesMap);
		*/
	}
	else if  (type1 == "AdditionExpression" || type1 == "MultiplicationExpression")
	{
		ArithmeticExpression* rhs1 = ((BinaryArithmeticExpression*)p1AE)->GetRhs();
		ArithmeticExpression* rhs2 = ((BinaryArithmeticExpression*)p2AE)->GetRhs();
		ArithmeticExpression* lhs1 = ((BinaryArithmeticExpression*)p1AE)->GetLhs();
		ArithmeticExpression* lhs2 = ((BinaryArithmeticExpression*)p2AE)->GetLhs();

		bool compRhs = compareAE(rhs1, rhs2, variablesMap, arrayVariablesMap);
		bool compLhs = compareAE(lhs1, lhs2, variablesMap, arrayVariablesMap);

		// "equivalent" if: rhs1 = lhs2 and lhs1 = rhs2
		// lhs1 + rhs1 = rhs2 + lhs1

		// "equivalent" if: lhs1 = rhs2 and rhs1 = lhs2
		// lhs1 * rhs1 = rhs2 * lhs2

		bool crossComp1 = compareAE(rhs1, lhs2, variablesMap, arrayVariablesMap);
		bool crossComp2 = compareAE(lhs1, rhs2, variablesMap, arrayVariablesMap);



		if (!compRhs || !compLhs)
		{
			// do not match, there was no cheating,
			// BUT WAIT! check if there was a switch first
			if (crossComp1 && crossComp2)
			{
				return true;
			}
			return false;
		}

	}
	else
	{
		ArithmeticExpression* rhs1 = ((BinaryArithmeticExpression*)p1AE)->GetRhs();
		ArithmeticExpression* rhs2 = ((BinaryArithmeticExpression*)p2AE)->GetRhs();
		ArithmeticExpression* lhs1 = ((BinaryArithmeticExpression*)p1AE)->GetLhs();
		ArithmeticExpression* lhs2 = ((BinaryArithmeticExpression*)p2AE)->GetLhs();

		bool compRhs = compareAE(rhs1, rhs2, variablesMap, arrayVariablesMap);
		bool compLhs = compareAE(lhs1, lhs2, variablesMap, arrayVariablesMap);

		if (!compRhs || !compLhs) return false;
		return true;
	}

	// do not need to specify which type of expression for
	// subtraction or division because
	// the first if statment handles it

	/*
	else if (type1 == "SubtractionExpression")
	else if (type1 == "DivisionExpression")
	*/

	return true;
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