#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "bst.h"
#include <algorithm>

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus 
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
	// Constructor/destructor.
	AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
	virtual ~AVLNode();

	// Getter/setter for the node's height.
	int getHeight() const;
	void setHeight(int height);

	// Getters for parent, left, and right. These need to be redefined since they 
	// return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
	// for more information.
	virtual AVLNode<Key, Value>* getParent() const override;
	virtual AVLNode<Key, Value>* getLeft() const override;
	virtual AVLNode<Key, Value>* getRight() const override;

protected:
	int mHeight;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a height of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
	: Node<Key, Value>(key, value, parent)
	, mHeight(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* Getter function for the height. 
*/
template<typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const
{
	return mHeight;
}

/**
* Setter function for the height. 
*/
template<typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height)
{
	mHeight = height;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods. 
	virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
	void remove(const Key& key);

private:
	/* Helper functions are strongly encouraged to help separate the problem
	   into smaller pieces. You should not need additional data members. */
	
	void zigzigLeft(AVLNode<Key,Value>* x, AVLNode<Key,Value>* y, AVLNode<Key,Value>* z);
	void zigzagLeft(AVLNode<Key,Value>* x, AVLNode<Key,Value>* y, AVLNode<Key,Value>* z);
	void zigzigRight(AVLNode<Key,Value>* x, AVLNode<Key,Value>* y, AVLNode<Key,Value>* z);
	void zigzagRight(AVLNode<Key,Value>* x, AVLNode<Key,Value>* y, AVLNode<Key,Value>* z);
	AVLNode<Key, Value>* findInvalidHeight(AVLNode<Key, Value>* begin);
	AVLNode<Key, Value>* removeHelper(const Key& key);
	void updateHeight(AVLNode<Key, Value>* newNode);
	AVLNode<Key, Value>* fixProblem(AVLNode<Key, Value>* problemNode);
	void insertHelper(const std::pair<Key, Value>& keyValuePair);


};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	// TODO

	// insert node as if tree is a binary tree
	insertHelper(keyValuePair);
	updateHeight(static_cast<AVLNode<Key, Value>*> (this->mRoot));

	// update new node's height
	Node<Key, Value>* temp = this->internalFind(keyValuePair.first);
	// std::cout << temp->getValue() << std::endl;
	AVLNode<Key, Value>* newNode = static_cast<AVLNode<Key, Value>*> (temp);
	if (newNode != NULL)
	{
		newNode->setHeight(0);
		// std::cout << "setheight success" << std::endl;
		updateHeight(newNode);
	
		// check if heights are valid (function)
		AVLNode<Key, Value>* problemNode = findInvalidHeight(newNode);

		// if there is an invalid height, determine if it is a zigzig or a zigzag
		// and fix it
		if (problemNode != NULL)
		{
			// std::cout << "problem node is " << problemNode->getValue() << std::endl;

			fixProblem(problemNode);
		}
	}
	// after one fix, the tree is garunteed to be balanced
	// std::cout << "root is " << this->mRoot->getValue() << std::endl;
}

/**
* Remove function for a given key. Finds the node, reattaches pointers, and then balances when finished. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
	// TODO
	std::cout << "\n !!! in remove" << std::endl;

	// remove value as if it is a BST
	AVLNode<Key, Value>* problemNode;
	AVLNode<Key, Value>* checkHere = removeHelper(key);

	if (checkHere == NULL)
	{
		problemNode = NULL;
		std::cout << "No node to check" << std::endl;
	}
	else
	{
		std::cout << "checking node " << checkHere->getValue() << checkHere->getKey() << std::endl;
		problemNode = findInvalidHeight(checkHere);
	}


	// check if heights are valid
	// if a height is invalid, determine if it is a zigzig or a zig zag and fix
	// continue checking heights until you reach the root (no invalid heights)
	// must check all the way up the tree because a fix might cause more imbalances
	while (problemNode != NULL)
	{
		// determine if it is a zigzig or a zig zag and fix
		std::cout << "problem node is " << problemNode->getValue() << problemNode->getKey() << std::endl;
		checkHere = fixProblem(problemNode);


		// set checkHere = to where to start searching again
		problemNode = findInvalidHeight(checkHere);
	}

}

/*
* deletes as if the tree is a binary tree
* returns a pointer to where to start checking for imbalances
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::removeHelper(const Key& key)
{
	AVLNode<Key, Value>* toDelete = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));

	if (toDelete == NULL)
	{
		return NULL;
	}

	AVLNode<Key, Value>* r = toDelete;

	if (toDelete->getRight() != NULL && toDelete->getLeft() == NULL)
	{
		// toDelete has only a right child

		r = toDelete->getRight();

		if (toDelete->getParent() == NULL)
		{
			this->mRoot = static_cast <AVLNode<Key, Value>*> (r);
		}
		else if (toDelete->getParent()->getRight() == toDelete)
		{
			toDelete->getParent()->setRight(r);
			r->setParent(toDelete->getParent());
		}
		else
		{
			toDelete->getParent()->setLeft(r);
			r->setParent(toDelete->getParent());
		}

		return r;
	}
	else if (toDelete->getRight() != NULL && toDelete->getRight() == NULL)
	{
		// toDelete has only a left child

		r = toDelete->getLeft();

		if (toDelete->getParent() == NULL)
		{
			this->mRoot = static_cast <AVLNode<Key, Value>*> (r);
		}
		else if (toDelete->getParent()->getRight() == toDelete)
		{
			toDelete->getParent()->setRight(r);
			r->setParent(toDelete->getParent());
		}
		else
		{
			toDelete->getParent()->setLeft(r);
			r->setParent(toDelete->getParent());
		}

		return r;
	}
	else if (toDelete->getRight() != NULL && toDelete->getRight() != NULL)
	{
		// toDelete has 2 children

		// find min value in right subtree

		r = toDelete->getRight();
		if (r->getLeft() != NULL)
		{
			// minimum value is the left most node of right subtree

			while(r->getLeft() != NULL)
			{
				r = r->getLeft();
			}

			r->getParent()->setLeft(NULL);

			// place r in toDelete's spot

			// r takes over toDelete's left child
			r->setLeft(toDelete->getLeft());
			if (toDelete->getLeft() != NULL)
			{
				toDelete->getLeft()->setParent(r);
			}

			// r becomes the child of toDelete's parent
			r->setParent(toDelete->getParent());
			if (toDelete->getParent() == NULL)
			{
				this->mRoot = static_cast <AVLNode <Key, Value>* > (r);
			}
			else
			{
				if (toDelete->getParent()->getRight() == toDelete)
				{
					toDelete->getParent()->setRight(r);
				}
				else
				{
					toDelete->getParent()->setLeft(r);
				}
			}

			// r takes over toDelete's right child

			r->setRight(toDelete->getRight());
			if (toDelete->getRight() != NULL)
			{
				toDelete->getRight()->setParent(r);
			}
		}
		else
		{
			// minimum value is the right child of toDelete

			// r takes over toDelete's left child
			r->setLeft(toDelete->getLeft());
			if (toDelete->getLeft() != NULL)
			{
				toDelete->getLeft()->setParent(r);
			}

			// r becomes the child of toDelete's parent
			r->setParent(toDelete->getParent());
			if (toDelete->getParent() == NULL)
			{
				this->mRoot = static_cast <AVLNode <Key, Value>* > (r);
			}
			else
			{
				if (toDelete->getParent()->getRight() == toDelete)
				{
					toDelete->getParent()->setRight(r);
				}
				else
				{
					toDelete->getParent()->setLeft(r);
				}
			}

		}

		int lh = -1;
		int rh = -1;
		if (r->getLeft() != NULL) lh = r->getLeft()->getHeight();
		if (r->getRight() != NULL) rh = r->getRight()->getHeight();

		r->setHeight(1+ std::max(lh,rh));
		
		if (r->getRight() != NULL)
		{
			return r->getRight();
		}

		return r;
		
	}
	else
	{
		// toDelete has no children

		if (toDelete->getParent() != NULL)
		{
			if (toDelete->getParent()->getLeft() == toDelete)
			{
				// toDelete is the left child
				toDelete->getParent()->setLeft(NULL);
			}
			else
			{
				toDelete->getParent()->setRight(NULL);
			}

			return toDelete->getParent();
		}
	}

	if (toDelete->getParent() != NULL)
	{
		r = toDelete->getParent();
		delete toDelete;
		return r;
	}
	else if (this->mRoot != NULL)
	{
		delete toDelete;
		return static_cast<AVLNode<Key,Value>*>(this->mRoot);
	}

	delete toDelete;
	return NULL;

}


/*
* Determines which nodes need to be rotated and calls appropriate zig-zig/ zig-zag
* returns the new "local root"
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::fixProblem(AVLNode<Key, Value>* problemNode)
{
	if (problemNode == NULL)
	{
		return NULL;
	}

	// std::cout << "entering fixproblem. problem node is " << problemNode->getValue() << " height is" << problemNode->getHeight() << std::endl;
	if (problemNode->getRight() != NULL)
	{
		// std::cout << "right height = " << problemNode->getRight()->getHeight() << std::endl;
	}
	else
	{
		// std::cout <<"right height = -1" <<std::endl;
	}
	if (problemNode->getLeft() != NULL)
	{
		// std::cout << "left height = " << problemNode->getLeft()->getHeight() << std::endl;
	}
	else
	{
		// std::cout <<"left height = -1" <<std::endl;
	}

	AVLNode<Key, Value>* y = NULL;
	AVLNode<Key, Value>* x = NULL;
	// std::cout << "entering if" << std::endl;

	if (problemNode->getRight() != NULL && (problemNode->getLeft() == NULL || problemNode->getRight()->getHeight() > problemNode->getLeft()->getHeight()))
	{
		// too heavy on right side
		// std::cout << "right side too heavy" << std::endl;
		y = problemNode->getRight();

		if (y->getRight() == NULL || (y->getLeft() != NULL && y->getLeft()->getHeight() > y->getRight()->getHeight()))
		{
			// zig-zag
			// std::cout << "right left" << std::endl;
			x = y->getLeft();
			zigzagRight(x, y, problemNode);
			return x;
		}
		else
		{
			// zig-zig
			// std::cout << "right right " << std::endl;
			x = y->getRight();
			zigzigRight(x, y, problemNode);
			return y;
		}
	}
	else
	{
		// to heavy on left side
		y = problemNode->getLeft();
		// std::cout << "left-?. y = " << y->getValue() << std::endl;

		if (y->getLeft() == NULL || (y->getRight() != NULL && y->getRight()->getHeight() > y->getLeft()->getHeight()))
		{
			// zig-zag
			// std::cout << "left right" << std::endl;
			x = y->getRight();
			zigzagLeft(x, y, problemNode);
			return x;
		}
		else
		{
			// zig-zig
			x = y->getLeft();
			// std::cout << "left left" << std::endl;
			zigzigLeft(x, y, problemNode);
			return y;
		}
	}

	return NULL;

}


/**
* updates the heights of the tree. 
*/
template<typename Key, typename Value>
void AVLTree<Key,Value>::updateHeight(AVLNode<Key, Value>* newNode)
{
	if (newNode == NULL)
	{
		return;
	}

	// std::cout <<"in update height. checking " << newNode->getKey() << newNode->getValue() << ".  height = " << newNode->getHeight() << std::endl;
	if (newNode->getLeft() == NULL && newNode->getRight() == NULL)
	{
		// newNode->setHeight(0);
	}
	else if (newNode->getLeft() == NULL)
	{
		// right child can not be NULL
		newNode->setHeight(newNode->getRight()->getHeight() + 1);
	}
	else if (newNode->getRight() == NULL)
	{
		// left child can not be NULL
		newNode->setHeight(newNode->getLeft()->getHeight() + 1);
	}
	else
	{
		int lHeight = newNode->getLeft()->getHeight();
		int rHeight = newNode->getRight()->getHeight();
		int maxH = rHeight;
		if (lHeight > rHeight)
		{
			maxH = lHeight;
		}
		newNode->setHeight(maxH + 1);
	}
	// std::cout << "new hieght for " << newNode->getValue() << " height = " << newNode->getHeight() << std::endl;

	updateHeight((newNode->getParent()));
}

/**
* Checks the heights of tree starting at given node-> returns the node with invalid height->
* returns NULL if the tree is balanced 
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::findInvalidHeight(AVLNode<Key, Value>* begin)
{
	// std::cout << "trying to find invalid node at " << begin->getValue() << std::endl;
	AVLNode<Key, Value>* location = begin;
	while (location != NULL)
	{
		if (location->getRight() == NULL && location->getLeft() == NULL)
		{
			// location->setHeight(0);
		}
		else if (location->getRight() == NULL)
		{
			// std::cout << "there is a left child with height: " << location->getLeft()->getHeight() << std::endl;
			if (location->getLeft()->getHeight() != 0)
			{
				// y = location->getLeft();
				return location;
			}
		}
		else if (location->getLeft() == NULL)
		{
			// std::cout << "there must be a right child" << std::endl;
			if (location->getRight()->getHeight() != 0)
			{
				return location;
			}
		}
		else
		{
			// there is both a right and left child
			int leftHeight = location->getLeft()->getHeight();
			int rightHeight = location->getRight()->getHeight();
			if (rightHeight - leftHeight > 1)
			{
				return location;
			}
			else if (leftHeight - rightHeight > 1)
			{
				return location;
			}
		}

		location = location->getParent();
	}

	return NULL;
}


/**
* perform zigzig for left
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::zigzigLeft(AVLNode<Key,Value>* x, AVLNode<Key,Value>* y, AVLNode<Key,Value>* z)
{
	// AVLNode<Key,Value>* T0 = x->getLeft();
	// AVLNode<Key,Value>* T1 = x->getRight();
	AVLNode<Key,Value>* T2 = y->getRight();
	AVLNode<Key,Value>* T3 = z->getRight();
	AVLNode<Key,Value>* parent = z->getParent();

	z->setLeft(T2);
	y->setRight(z);
	z->setParent(y);
	y->setParent(parent);

	if (T2 != NULL)
	{
		T2->setParent(z);
	}
	if (parent == NULL)
	{
		this->mRoot = static_cast <AVLNode<Key,Value>*> (y);
	}
	else
	{
		if (parent->getLeft() == z)
		{
			// z was the left child
			parent->setLeft(y);
		}
		else
		{
			parent->setRight(y);
		}
	}

	// int T0Height = -1;
	// int T1Height = -1;
	int T2Height = -1; 
	int T3Height = -1;
	// if (T0 != NULL) T0Height = T0->getHeight();
	// if (T1 != NULL) T0Height = T1->getHeight();
	if (T2 != NULL) T2Height = T2->getHeight();
	if (T3 != NULL) T3Height = T3->getHeight();
	z->setHeight(1 + std::max(T2Height, T3Height));
	y->setHeight(1 + std::max(z->getHeight(), x->getHeight()));
	
	updateHeight(y);


	// std::cout << "rotate left-left success" << std::endl;
	// updateHeight(z);
	// std::cout << "update height z success" << std::endl;
	// updateHeight(x);

}


/**
* perform zigzag for left
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::zigzagLeft(AVLNode<Key,Value>* x, AVLNode<Key,Value>* y, AVLNode<Key,Value>* z)
{
	// std::cout << "	!! Left zig zag" << std::endl;
	AVLNode<Key,Value>* T0 = y->getLeft();
	AVLNode<Key,Value>* T1 = x->getLeft();
	AVLNode<Key,Value>* T2 = x->getRight();
	AVLNode<Key,Value>* T3 = z->getRight();
	AVLNode<Key,Value>* parent = z->getParent();


	x->setLeft(y);
	x->setRight(z);
	y->setRight(T1);
	z->setLeft(T2);
	z->setParent(x);
	y->setParent(x);
	x->setParent(parent);
	if (T1 != NULL)
	{
		T1->setParent(y);
	}
	if (T2 != NULL)
	{
		T2->setParent(z);
	}
	if (parent == NULL)
	{
		this->mRoot = static_cast <AVLNode<Key,Value>*> (x);
	}
	else
	{
		if (parent->getLeft() == z)
		{
			// z was the left child
			parent->setLeft(x);
		}
		else
		{
			parent->setRight(x);
		}
	}

	int T0Height = -1;
	int T1Height = -1;
	int T2Height = -1; 
	int T3Height = -1;
	if (T0 != NULL) T0Height = T0->getHeight();
	if (T1 != NULL) T1Height = T1->getHeight();
	if (T2 != NULL) T2Height = T2->getHeight();
	if (T3 != NULL) T3Height = T3->getHeight();
	z->setHeight(1 + std::max(T2Height, T3Height));
	y->setHeight(1 + std::max(T0Height, T1Height));
	x->setHeight(1 + std::max(z->getHeight(), y->getHeight()));
	
	updateHeight(x);

	//updateHeight(z);
	//updateHeight(y);

}


/**
* perform zigzig for right
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::zigzigRight(AVLNode<Key,Value>* x, AVLNode<Key,Value>* y, AVLNode<Key,Value>* z)
{
	AVLNode<Key,Value>* T0 = z->getLeft();
	AVLNode<Key,Value>* T1 = y->getLeft();
	AVLNode<Key,Value>* T2 = x->getLeft();
	AVLNode<Key,Value>* T3 = x->getRight();
	AVLNode<Key,Value>* parent = z->getParent();


	z->setRight(T1);
	y->setLeft(z);
	z->setParent(y);
	y->setParent(parent);
	if (T1 != NULL)
	{
		T1->setParent(z);
	}
	if (parent == NULL)
	{
		this->mRoot = static_cast <AVLNode<Key,Value>*> (y);
	}
	else
	{
		if (parent->getLeft() == z)
		{
			// z was the left child
			parent->setLeft(y);
		}
		else
		{
			parent->setRight(y);
		}
	}

	int T0Height = -1;
	int T1Height = -1;
	int T2Height = -1; 
	int T3Height = -1;
	if (T0 != NULL) T0Height = T0->getHeight();
	if (T1 != NULL) T1Height = T1->getHeight();
	if (T2 != NULL) T2Height = T2->getHeight();
	if (T3 != NULL) T3Height = T3->getHeight();
	z->setHeight(1 + std::max(T0Height, T1Height));
	x->setHeight(1 + std::max(T2Height, T3Height));
	y->setHeight(1 + std::max(z->getHeight(), x->getHeight()));
	
	updateHeight(y);

	//updateHeight(z);
	//updateHeight(x);

}


/**
* perform zigzif for right
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::zigzagRight(AVLNode<Key,Value>* x, AVLNode<Key,Value>* y, AVLNode<Key,Value>* z)
{
	AVLNode<Key,Value>* T0 = z->getLeft();
	AVLNode<Key,Value>* T1 = x->getLeft();
	AVLNode<Key,Value>* T2 = x->getRight();
	AVLNode<Key,Value>* T3 = y->getRight();
	AVLNode<Key,Value>* parent = z->getParent();


	x->setLeft(z);
	x->setRight(y);
	z->setRight(T1);
	y->setLeft(T2);
	z->setParent(x);
	y->setParent(x);
	x->setParent(parent);
	if (T1 != NULL)
	{
		T1->setParent(z);
	}
	if (T2 != NULL)
	{
		T2->setParent(y);
	}
	if (parent == NULL)
	{
		this->mRoot = static_cast <AVLNode<Key,Value>*> (x);
	}
	else
	{
		if (parent->getLeft() == z)
		{
			// z was the left child
			parent->setLeft(x);
		}
		else
		{
			parent->setRight(x);
		}
	}

	int T0Height = -1;
	int T1Height = -1;
	int T2Height = -1; 
	int T3Height = -1;
	if (T0 != NULL) T0Height = T0->getHeight();
	if (T1 != NULL) T1Height = T1->getHeight();
	if (T2 != NULL) T2Height = T2->getHeight();
	if (T3 != NULL) T3Height = T3->getHeight();
	z->setHeight(1 + std::max(T0Height, T1Height));
	y->setHeight(1 + std::max(T2Height, T3Height));
	x->setHeight(1 + std::max(z->getHeight(), y->getHeight()));
	
	updateHeight(x);

	//updateHeight(y);
	//updateHeight(z);

}


template<typename Key, typename Value>
void AVLTree<Key, Value>::insertHelper(const std::pair<Key, Value>& keyValuePair)
{
	// TODO
	Key toFind = keyValuePair.first;
	AVLNode<Key, Value>* location = static_cast<AVLNode<Key, Value>*> (this->mRoot);

	if (this->mRoot == NULL)
	{
		AVLNode<Key, Value>* addMe = new AVLNode<Key, Value> (keyValuePair.first, keyValuePair.second, NULL);
		addMe->setHeight(0);
	 	this->mRoot = addMe;
		return;
	}

	bool found = false;

	while (!found && location != NULL)
	{
		if (location->getKey() == toFind)
		{
			// this key already exists, update the value!
			location->setValue(keyValuePair.second);
			found = true;
		}
		else if (toFind < location->getKey())
		{
			// key is less than current location
			// std::cout << "key :" << toFind << " is less than " << location->getValue() << std::endl;

			if (location->getLeft() != NULL)
			{
				// there is a child here, move to its location to continue search
				
				location = location->getLeft();
			}
			else
			{
				// no child here. create a new node and place it here

				found = true;
				if (location != NULL)
				{
					AVLNode<Key, Value>* toInsert = new AVLNode<Key, Value> (keyValuePair.first, keyValuePair.second, location);
					toInsert->setHeight(0);
					location->setLeft(toInsert);
				}
				
			}
		}
		else
		{
			// key is greater than current location

			if (location->getRight() != NULL)
			{
				// there is a child here, move to its location to continue search
				
				location = location->getRight();
			}
			else
			{
				// no child here. create a new node and place it here

				found = true;
				AVLNode<Key, Value>* toInsert = new AVLNode<Key, Value> (keyValuePair.first, keyValuePair.second, location);
				toInsert->setHeight(0);
				location->setRight(toInsert);
			}
		}
	}
}



/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif