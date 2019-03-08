#ifndef ARRAY_H
#define ARRAY_H

#include <string>
#include <random>
using namespace std;

template <class T>
class Array
{
public:
  Array(mt19937 generator, int size = 0);
  ~Array();
  int loadFromFile(string fileName);
  bool isElementInArray(T element);
  void addElementFront(T element); // add element functions are splited because of measure time purposes
  void addElementBack(T element);
  int addElement(int index, T element);
  int deleteElementFront();
  int deleteElementBack();
  int deleteElement(int index);
  void display();
  void generateArray(int size, T maxValue = 1000, T minValue = 1);
  int getSize();

private:
  T *array;
  int size;
  mt19937 generator;
  void rearrangePointers(T *newArray, bool incrementSize); // help function to keep the code clean and more readable
};

#endif
