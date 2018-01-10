#include "avlbst.h"
#include <string>
#include <iostream>


using namespace std;

int main(int argc, char const *argv[])
{

	AVLTree<int, int>* bst = new AVLTree <int, int>();

	cout << "inserting 20" << endl;
	bst->insert(pair<int, string>(20, 1));
	bst->print();
	cout << "inserting 4" << endl;
	bst->insert(pair<int, string>(4, 2));
	bst->print();
	cout << "inserting 26" << endl;
	bst->insert(pair<int, string>(26, 3));
	bst->print();
	cout << "inserting 3" << endl;
	bst->insert(pair<int, string>(3, 4));
	bst->print();
	cout << "inserting 9" << endl;
	bst->insert(pair<int, string>(9, 5));
	bst->print();
	cout << "inserting 21" << endl;
	bst->insert(pair<int, string>(21, 6));
	bst->print();
	cout << "inserting 30" << endl;
	bst->insert(pair<int, string>(30, 7));
	bst->print();
	cout << "inserting 2" << endl;
	bst->insert(pair<int, string>(2, 8));
	bst->print();
	cout << "inserting 7" << endl;
	bst->insert(pair<int, string>(7, 9));
	bst->print();
	cout << "inserting 11" << endl;
	bst->insert(pair<int, string>(11, 10));
	bst->print();


	delete bst;


	return 0;
}
