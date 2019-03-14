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
int BstTree<T>::loadFromFile(string filename)
{
	ifstream stream(filename);
	if (!stream.is_open())
		return -1;

	int length;
	T value;
	deleteTree(root);
	root = nullptr;
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
	if (root == NULL)
		return;

	cout << root->key << endl;
	displayRecurrence(root, "");
	cout << endl;
}

template <typename T>
void BstTree<T>::displayRecurrence(BstNode<T> *root, string prefix)
{
	if (root == NULL)
		return;

	bool hasLeft = (root->left != NULL);
	bool hasRight = (root->right != NULL);

	if (!hasLeft && !hasRight)
		return;

	cout << prefix;
	cout << ((hasLeft && hasRight) ? "├── " : "");
	cout << ((!hasLeft && hasRight) ? "└── " : "");

	if (hasRight)
	{
		bool printStrand = (hasLeft && hasRight && (root->right->right != NULL || root->right->left != NULL));
		string newPrefix = prefix + (printStrand ? "│   " : "    ");
		cout << root->right->key << endl;
		displayRecurrence(root->right, newPrefix);
	}

	if (hasLeft)
	{
		cout << (hasRight ? prefix : "") << "└── " << root->left->key << endl;
		displayRecurrence(root->left, prefix + "    ");
	}
}

template <typename T>
void BstTree<T>::rotateLeft(BstNode<T> *node)
{
	BstNode<T> *rightChild = node->right;
	BstNode<T> *parent = node->up;

	if (rightChild) // check if right child exists (if not we can't rotate)
	{
		node->right = rightChild->left; // right child left son becomes current node right son
		if (node->right)				// if the new assigned node is not nullptr ( it exists)
			node->right->up = node;		// new son must point now to the node which we are rotating

		rightChild->left = node; // child is moved up so new node becomes left son of the moved node
		rightChild->up = parent; // now the right child needs to point where previously node has pointed
		node->up = rightChild;   // right child is parent of the rotated node so assign up pointer to it

		if (parent) // check if the parent of previous up node exists
		{
			if (parent->left == node)	  // check if left son of parent of previous up node is the rotated node
				parent->left = rightChild; // left child of parent of previous up node becomes the right child of rotated node
			else
				parent->right = rightChild; // othewise it becomes the right son
		}
		else
			root = rightChild; // if parent does not exists the rotation reached the root so rotated node becomes new root
	}
}

template <typename T>
void BstTree<T>::rotateRight(BstNode<T> *node)
{
	BstNode<T> *leftChild = node->left; // get left child of node which will be rotated
	BstNode<T> *parent = node->up;		// get the parent of the node

	if (leftChild) // check if left child exists
	{
		node->left = leftChild->right; // now left child right son becomes current node left son
		if (node->left)				   // if the new assigned node is not nullptr ( it exists)
			node->left->up = node;	 // point the new son to the parent

		leftChild->right = node; // child is moved up so new node becomes right son of the moved node
		leftChild->up = parent;  // now the left child needs to point where previously node has pointed
		node->up = leftChild;	// left child is parent of the rotated node so assign up pointer to it

		if (parent) // check if the parent of previous up node exists
		{
			if (parent->left == node)	 // check if left son of parent of previous up node is the rotated node
				parent->left = leftChild; // left child of parent of previous up node becomes the  left child of rotated node
			else
				parent->right = leftChild; // othewise it becomes the right son
		}
		else
			root = leftChild; // if parent does not exists the rotation reached the root so rotated node becomes new root
	}
}

template <typename T>
unsigned BstTree<T>::calculateLog2(unsigned number)
{
	// quickly calculates the logarithm using shifting
	unsigned result = 1;

	while ((number = number >> 1) > 0)
		result = result << 1;

	return result;
}

template <typename T>
void BstTree<T>::rebalanceDSW()
{
	unsigned nodesNumber, rotateCounter;
	BstNode<T> *p;

	nodesNumber = 0; // initialize nodeCounter
	p = root;		 // start from the root
	while (p)		 // until we are inside the tree
		if (p->left) // if current processed not has left son
		{
			rotateRight(p); // rotate the tree right
			p = p->up;		// move to the parent
		}
		else
		{
			nodesNumber++; // Otherwise increate the number of nodes
			p = p->right;  // and move to the right son
		}

	// Teraz z listy tworzymy drzewo BST
	rotateCounter = nodesNumber + 1 - calculateLog2(nodesNumber + 1); // Wyznaczamy początkową liczbę obrotów

	p = root; // Start from the root
	for (int i = 0; i < rotateCounter; i++)
	{
		rotateLeft(p);	// every second node is rotated left
		p = p->up->right; // move to the right son of parrent of current node
	}

	nodesNumber = nodesNumber - rotateCounter; // Decrease the number of nodes by number of leafs

	while (nodesNumber > 1) // keep rotating th tree
	{
		nodesNumber = nodesNumber >> 1; // with each iteration the number of nodes decreases by 2
		p = root;						// start from the root
		for (int i = 0; i < nodesNumber; i++)
		{
			rotateLeft(p);	// every second node gets rotated
			p = p->up->right; // move the second next node
		}
	}
}