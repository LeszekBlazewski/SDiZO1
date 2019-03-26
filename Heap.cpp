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
    numberOfElementsInHeap = 0;
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
    numberOfElementsInHeap = 0;
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
    int elementPosition = findElementPosition(value); // search the position of the element which should be removed

    if (elementPosition != -1)
    {
        int parent = (elementPosition - 1) / 2; // calucalte the position of parent

        heap[elementPosition] = heap[numberOfElementsInHeap - 1]; // replace the found element with the last element in heap
        heap[numberOfElementsInHeap - 1] = 0;                     // set the moved element to zero which indicates that the field is empty
        numberOfElementsInHeap -= 1;                              // decrease the number of elements

        if (elementPosition == 0 || heap[parent] > heap[elementPosition]) // if found element is root OR value at found position is less than it's parent we need to switch element only down from given
            heapifyDown(elementPosition);
        else
            heapifyUp(elementPosition); // in other case we need to fix the heap condition upside

        return 0;
    }
    else
        return -1;
}

template <typename T>
void Heap<T>::displayRecurrence(string sMiddle, string sBefore, int currNode)
{
    string s;
    if (currNode < size)
    {
        s = sMiddle;
        if (sBefore == (string(1, (char)47) + string(1, (char)126)))
            s[s.length() - 2] = ' ';
        displayRecurrence(s + (char)124 + " ", (string(1, (char)47)) + string(1, (char)126), 2 * currNode + 2);

        s = s.substr(0, sMiddle.length() - 2);

        cout << s << sBefore;
        if (heap[currNode] != 0)
            cout << heap[currNode];
        //else
        //cout << 'x';
        cout << endl;

        s = sMiddle;
        if (sBefore == (string(1, (char)92)) + string(1, (char)126))
            s[s.length() - 2] = ' ';
        displayRecurrence(s + (char)124 + " ", (string(1, (char)92)) + string(1, (char)126), 2 * currNode + 1);
    }
}

template <typename T>
void Heap<T>::display()
{
    displayRecurrence("", "", 0);
}

template <typename T>
void Heap<T>::heapifyUp(int position)
{
    while (position != 0) // until we reach the root
    {
        T newElem = heap[position];           // get value of new element
        int parentPos = ((position - 1) / 2); // calculate position of parent
        T parent = heap[parentPos];           // get parent value
        T temp;

        if (parent < newElem) // check if heap condition is satisfied (max heap so parent must be greater than child)
        {
            temp = heap[position];
            heap[position] = parent;
            heap[parentPos] = newElem;

            position = parentPos; // move to the parent position
        }
        else
            break;
    }
}

template <typename T>
void Heap<T>::heapifyDown(int position)
{
    while ((2 * position + 1) < numberOfElementsInHeap) // unitl we reach end of the heap
    {
        int leftPos = 2 * position + 1;  // get leftPosition from given one
        int rightPos = 2 * position + 2; // get right position
        T element = heap[position];      // get value of the element
        T temp;
        T left = heap[leftPos];                 // get the value of element at left position
        if (rightPos >= numberOfElementsInHeap) // if position of the right element exceedes number of elements
        {
            if (left > element) // if element on left is greater than the element on position given to heapify
            {
                temp = heap[leftPos];
                heap[leftPos] = element;
                heap[position] = temp;

                position = leftPos;
            }
            else
                break;
        }
        else // in other case
        {
            T right = heap[rightPos]; // get value on the right

            if (left > element || right > element) // if left value is greater than the current element or right is greater
            {
                if (left >= right)
                {
                    temp = heap[leftPos];
                    heap[leftPos] = element;
                    heap[position] = temp;

                    position = leftPos; // move the the left
                }
                else
                {
                    temp = heap[rightPos];
                    heap[rightPos] = element;
                    heap[position] = temp;

                    position = rightPos; // move to the right
                }
            }
            else
                break;
        }
    }
}

template <typename T>
void Heap<T>::heap_pop()
{
    int i, j, v;

    if (n--)
    {
        v = heap[n];

        i = 0;
        j = 1;

        while (j < n)
        {
            if (j + 1 < n && heap[j + 1] > heap[j])
                j++;
            if (v >= heap[j])
                break;
            heap[i] = heap[j];
            i = j;
            j = 2 * j + 1;
        }

        heap[i] = v;
    }
}