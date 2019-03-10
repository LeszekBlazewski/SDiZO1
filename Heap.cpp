#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <iomanip>

#include "Heap.h"

using namespace std;

template <typename T>
Heap<T>::Heap(mt19937 generator, int size) : generator(generator), size(size)
{
    heap = new T[size];         //allocate new array with default size of 15
    numberOfElementsInHeap = 0; // when creating the heap there are no elements in it
    initializePrintVariables();
}

template <typename T>
Heap<T>::~Heap()
{
    delete[] heap; // delete the dynamic allocated heap on exit
}

template <typename T>
void Heap<T>::addElement(T value)
{
    int i, j; // i - postion of inserted element, j - index of parent node

    i = numberOfElementsInHeap++; // assign index on which element will be put into heap (then increment the number of elements in heap by one)
    j = (i - 1) / 2;              // calculate the position of parent node

    while (i > 0 && heap[j] < value) // check if heap condidtion is satsfied
    {
        heap[i] = heap[j]; // switch child with parent
        i = j;             // move to the parent node
        j = (i - 1) / 2;   // calculate next parent node
    }

    heap[i] = value; // insert value at the right spot
}

template <typename T>
int Heap<T>::loadFromFile(string filename)
{
    ifstream stream(filename, ifstream::in);
    if (!stream)
        return -1;
    int length;
    T value;
    stream >> length;
    delete[] heap;
    heap = new T[length + 10];
    size = length + 10;
    for (int i = 0; i < length; i++)
    {
        stream >> value;
        addElement(value);
    }
    stream.close();
    return 0;
}

template <typename T>
void Heap<T>::generateHeap(int size, T minValue, T maxValue)
{
    delete[] heap;
    heap = new T[size + 10];
    this->size = size + 10;
    uniform_int_distribution<> dist(minValue, maxValue);

    for (int i = 0; i < size; i++)
        addElement(dist(generator));
}

template <typename T>
int Heap<T>::findElementPosition(T element)
{
    for (int i = 0; i < numberOfElementsInHeap; i++)
    {
        if (heap[i] == element)
            return i;
    }
    return -1;
}

template <typename T>
int Heap<T>::deleteElement(T value)
{
    int elementPosition = findElementPosition(value);

    if (elementPosition != -1)
    {
        //TODO !
    }
    else
        return -1;
}

template <typename T>
void Heap<T>::display(string sp, string sn, int v)
{
    string s;
    cout << endl;
    if (v < numberOfElementsInHeap)
    {
        s = sp;
        if (sn == cr)
            s[s.length() - 2] = ' ';
        display(s + cp, cr, 2 * v + 2);

        s = s.substr(0, sp.length() - 2);

        cout << s << sn << heap[v] << endl;

        s = sp;
        if (sn == cl)
            s[s.length() - 2] = ' ';
        display(s + cp, cl, 2 * v + 1);
    }
}

template <typename T>
void Heap<T>::initializePrintVariables()
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
void Heap<T>::heapifyUp(int position)
{
}
template <typename T>
void Heap<T>::heapifyDown(int position)
{
}