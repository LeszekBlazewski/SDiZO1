#ifndef LIST_H
#define LIST_H

#include <string>
#include <random>
using namespace std;

template <class T>
struct Node
{
  T data;
  Node *prev;
  Node *next;
};

template <class T>
class List
{
public:
  List(mt19937 generator);
  ~List();
  void clearList();
  void push_front(T value);
  void push_back(T value);
  int addElement(int index, T value);
  int loadFromFile(string fileName);
  void generateList(int size, T minValue = 1, T maxValue = 1000);
  Node<T> *findElement(T value);
  void pop_front();
  void pop_back();
  int deleteElement(T value);
  void display();

private:
  Node<T> *head;
  Node<T> *tail;
  mt19937 generator;
};

#endif