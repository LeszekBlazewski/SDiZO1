#ifndef BstTree_H
#define BstTree_H

#include <string>
#include <random>
using namespace std;

template <class T>
struct BstNode
{
	BstNode *up;
	BstNode *left;
	BstNode *right;
	T key; // stores the actual data of the node - this also servers as the key of the BST TREE
};

template <class T>
class BstTree
{
  public:
	BstTree(mt19937 generator);
	~BstTree();
	int deleteElement(T value);
	int loadFromFile(string filename);
	void generateTree(int size, T minValue = 1, T maxValue = 1000);
	BstNode<T> *findNode(T element);
	void display(string sp, string sn, int v);
	void addElement(T value);

  private:
	mt19937 generator;
	BstNode<T> *root;
	void deleteTree(BstNode<T> *root);
	void findSuccessor(BstNode<T> *node);
	BstNode<T> *minimalNode();
	//variables to print pretty the tree
	void initializePrintVariables();
	string cr, cl, cp;
};
#endif