#include "avlbst.h"
#include <string>
#include <iostream>


using namespace std;

int main(int argc, char const *argv[])
{



	AVLTree<int, string>* bst = new AVLTree <int, string>();

	cout << "inserting 9, dog" << endl;
	bst->insert(pair<int, string>(9, "dog"));
	bst->print();
	cout << "inserting 4, cow" << endl;
	bst->insert(pair<int, string>(4, "cow"));
	bst->print();
	cout << "inserting 11, cat" << endl;
	bst->insert(pair<int, string>(11, "cat"));
	bst->print();
	cout << "inserting 2, frog" << endl;
	bst->insert(pair<int, string>(3, "frog"));
	bst->print();
	cout << "inserting 5, dolphin" << endl;
	bst->insert(pair<int, string>(5, "dolphin"));
	bst->print();
	cout << "inserting 10, goat" << endl;
	bst->insert(pair<int, string>(10, "goat"));
	bst->print();
	cout << "inserting 12, pup" << endl;
	bst->insert(pair<int, string>(12, "pup"));
	bst->print();
	cout << "inserting 2, lamb" << endl;
	bst->insert(pair<int, string>(2, "lamb"));
	bst->print();
	cout << "inserting 7, pig" << endl;
	bst->insert(pair<int, string>(7, "pig"));
	bst->print();
	cout << "inserting 1, bird" << endl;
	bst->insert(pair<int, string>(1, "bird"));
	bst->print();
	cout << "inserting 6, lion" << endl;
	bst->insert(pair<int, string>(6, "lion"));
	bst->print();
	cout << "inserting 8, seal" << endl;
	bst->insert(pair<int, string>(8, "seal"));
	bst->print();
	cout << "inserting 13, bug" << endl;
	bst->insert(pair<int, string>(13, "bug"));
	bst->print();
	cout << "removing 5, dolphin" << endl;
	bst->remove(5);
	bst->print();
	cout << "removing 1, bird" << endl;
	bst->remove(1);
	bst->print();
	cout << "removing 9, dog" << endl;
	bst->remove(9);
	bst->print();


	delete bst;


	return 0;
}