#ifndef HEAP_H
#define HEAP_H

#include <string>
#include <random>
using namespace std;

template <class T>
class Heap
{
public:
  Heap(mt19937 generator, int size = 31); // we assume that there are 7 additional places when creating new heap
  ~Heap();
  void addElement(T value);
  int loadFromFile(string filename);
  void generateHeap(int size, T minValue = 1, T maxValue = 1000);
  int findElementPosition(T element);
  int deleteElement(T value);
  void display(string sp, string sn, int v);
  void initializePrintVariables();
  void heapifyDown(int position);
  void heapifyUp(int position);

private:
  mt19937 generator;
  T *heap;
  int size;
  int numberOfElementsInHeap;
  //variables to print pretty the heap
  string cr, cl, cp;
};

#endif