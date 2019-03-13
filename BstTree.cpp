#include <iostream>
#include <fstream>
#include <random>

#include "BstTree.h"

using namespace std;

template <typename T>
BstTree<T>::BstTree(mt19937 generator) : generator(generator)
{
	root = nullptr;
}

template <typename T>
BstTree<T>::~BstTree()
{
	deleteTree(root);
}

template <typename T>
void BstTree<T>::deleteTree(BstNode<T> *root)
{
	if (root != nullptr) // check if root is not null
	{
		deleteTree(root->left); // recurension to delete properly the tree
		deleteTree(root->right);
		delete root;
	}
}

template <typename T>
void BstTree<T>::generateTree(int size, T minValue, T maxValue)
{
	uniform_int_distribution<> dist(minValue, maxValue);
	deleteTree(root);
	root = nullptr;
	for (int i = 0; i < size; i++)
	{
		addElement(dist(generator));
	}
}

template <typename T>
void BstTree<T>::initializePrintVariables()
{
	cr = cl = cp = "  ";
	cr[0] = ' ';
	cr[1] = ' ';
	cl[0] = ' ';
	cl[1] = ' ';
	cp[1] = ' ';
	cp[0] = ' ';
}

template <typename T>
int BstTree<T>::loadFromFile(string filename)
{
	ifstream stream(filename);
	if (!stream.is_open())
		return -1;

	int length;
	T value;
	deleteTree(root);
	//root = nullptr;				CHECK IF THIS CAN BE SO
	stream >> length;

	for (int i = 0; i < length; i++) // read all values from file and insert them into newly created array
	{
		stream >> value;
		addElement(value);
	}
	stream.close();
	return 0;
}

template <typename T>
BstNode<T> *BstTree<T>::findNode(T element)
{
	BstNode<T> *ptr = root;									 // tmp ptr to not mess up the tree
	while (ptr != nullptr && ptr->key != element)			 // until ptr exists and key differs from searched element
		ptr = (element < ptr->key) ? ptr->left : ptr->right; // if element is less than current node key move left otherwise move right

	return ptr; // return found pointer or nullptr if it does not exists
}
template <typename T>
BstNode<T> *BstTree<T>::minimalNode()
{
	BstNode<T> *tmp = root; // tmp pointer to not mess up the link in the tree

	if (tmp != nullptr)		 // check if tree contains any elements
		while (tmp->left)	// if yes keep iterating left until the last node
			tmp = tmp->left; // move left

	return tmp; // return found pointer OR nullptr if tree is empty
}

template <typename T>
BstNode<T> *BstTree<T>::findSuccessor(BstNode<T> *node)
{
	BstNode<T> *successor; // successor of the node given in parameter

	if (node != nullptr) // if given node exists
	{
		if (node->right)		  // if right son of the given node exists
			return minimalNode(); // search the minimal node
		else
		{
			successor = node->up;							// successors becomes the parent of the node
			while (successor && (node == successor->right)) // until successor exists and node equals right son of successor
			{
				node = successor;		   // node becomes successor
				successor = successor->up; // successor is to parent node
			}
			return successor;
		}
	}
	return node; // return the node if it points to null
}

template <typename T>
void BstTree<T>::addElement(T value)
{
	BstNode<T> *newNode = new BstNode<T>;
	newNode->left = newNode->right = nullptr;
	newNode->key = value;

	BstNode<T> *tmp = root; //tmp will contain the place where our new node should be inserted

	if (root == nullptr) // if tree is empty new node becomes the root
		root = newNode;
	else
		while (true) // keep iterating
		{
			if (value < tmp->key) // if value which should be inserted is lower than current node value move left
			{
				if (!tmp->left) // If left son does not exists, new node becomes the left son
				{
					tmp->left = newNode;
					break; // no need to iterate
				}
				else
					tmp = tmp->left; // keep moving left
			}
			else // when value is greater move right
			{
				if (!tmp->right) // If right son does not exists
				{
					tmp->right = newNode; // If right node does not exists, new node becomes the right son
					break;
				}
				else
					tmp = tmp->right; // else keep moving right
			}
		}
	newNode->up = tmp; // father of the new node is always the node pointed by tmp
}

template <typename T>
int BstTree<T>::deleteElement(T value)
{
	BstNode<T> *Y, *Z;

	// First search the node which contains the given value
	BstNode<T> *nodeToDelete = findNode(value);

	if (nodeToDelete != nullptr) // check if node with given value exists in tree
	{
		if (nodeToDelete->left == nullptr || nodeToDelete->right == nullptr) // if nodeToDelete does not have sons or have only one Y points to the deleted node
			Y = nodeToDelete;
		else
			Y = findSuccessor(nodeToDelete); // in other case we have to find the successor of the node which should be deleted

		// Z points to son of Y or nullptr

		if (Y->left != nullptr) // if left son of Y exists
			Z = Y->left;		// Z points to it
		else
			Z = Y->right; // otherwise Z points to right son or nullptr

		if (Z != nullptr) // If son of Y exists, it replaces Y in tree ( Z is the son )
			Z->up = Y->up;

		// Y gets replaced by Z in tree

		if (!Y->up)				   // if parent does not exists
			root = Z;			   // we have reached the root
		else if (Y == Y->up->left) // if Y equals the parent left son
			Y->up->left = Z;	   // Z becomes the left son
		else
			Y->up->right = Z; /// otherwise Z becomes the right son of the parent node

		// If Y is the successor of X, we copy the values

		if (Y != nodeToDelete)
			nodeToDelete->key = Y->key;

		delete Y; // remove the node
		return 0;
	}
	else
		return -1; // this means that value given to delete is not in tree
}

template <typename T>
void BstTree<T>::display()
{
	displayRecurrence("", "", root);
}

template <typename T>
void BstTree<T>::displayRecurrence(string sMiddle, string sBefore, BstNode<T> *&currNode)
{
	string s;
	if (currNode != nullptr)
	{
		s = sMiddle;
		if (sBefore == (string(1, (char)47) + string(1, (char)126)))
			s[s.length() - 2] = ' ';
		displayRecurrence(s + (char)124 + " ", (string(1, (char)47)) + string(1, (char)126), currNode->right);

		s = s.substr(0, sMiddle.length() - 2);

		cout << s << sBefore << currNode->key << endl;

		s = sMiddle;
		if (sBefore == (string(1, (char)92)) + string(1, (char)126))
			s[s.length() - 2] = ' ';
		displayRecurrence(s + (char)124 + " ", (string(1, (char)92)) + string(1, (char)126), currNode->left);
	}
}
