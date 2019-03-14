#include <iostream>
#include <fstream>
#include <random>

#include "Array.h"

using namespace std;

template <typename T>
Array<T>::Array(mt19937 generator, int size) : generator(generator), size(size)
{
    array = new T[size]; //allocate new array with default size of 0
}

template <typename T>
Array<T>::~Array()
{
    delete[] array; // delete the dynamic allocated array on exit
}

template <typename T>
int Array<T>::loadFromFile(string filename)
{
    ifstream stream(filename, ifstream::in);
    if (!stream) // error while opening the file
        return -1;
    int length;
    T value;
    stream >> length; // get length of array (first number in file )
    T *newArray = new T[length];
    for (int i = 0; i < length; i++) // read all values from file and insert them into newly created array
    {
        stream >> value;
        newArray[i] = value;
    }
    stream.close();
    size = length;
    delete[] array;
    array = newArray;
    return 0;
}

template <typename T>
bool Array<T>::isElementInArray(T element)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == element)
            return true;
    }
    return false;
}

template <typename T>
void Array<T>::addElementFront(T element)
{
    T *newArray = new T[size + 1];
    newArray[0] = element;

    if (size > 0) // get elements from previous array when adding elemnt to front of non empty table
        for (int i = 0; i < size; i++)
            newArray[i + 1] = array[i];

    rearrangePointers(newArray, true);
}

template <typename T>
void Array<T>::addElementBack(T element)
{
    T *newArray = new T[size + 1];

    for (int i = 0; i < size; i++) // copy all of the elements of old array into new one
    {
        newArray[i] = array[i];
    }
    newArray[size] = element; //assign the new element

    rearrangePointers(newArray, true);
}

template <typename T>
int Array<T>::addElement(int index, T element)
{
    int resultOfOperation;

    if (index >= 0 && index <= size) //check if user requested adding an element with reasonable index
    {
        T *newArray = new T[size + 1]; //allocate new array

        for (int i = 0; i < index; i++) //copy all elemnts until given index
            newArray[i] = array[i];

        newArray[index] = element; // insert new element

        for (int i = index; i < size; i++) // copy all elements from that index to the end of array
            newArray[i + 1] = array[i];

        rearrangePointers(newArray, true);

        resultOfOperation = 0;
    }
    else
        resultOfOperation = -1;

    return resultOfOperation;
}

template <typename T>
int Array<T>::deleteElementFront()
{
    if (size == 0)
        return -1;

    T *newArray = new T[size - 1];

    for (int i = 1; i < size; i++) // copy all elements from FIRST index in old array into new array
        newArray[i - 1] = array[i];

    rearrangePointers(newArray, false);

    return 0;
}

template <typename T>
int Array<T>::deleteElementBack()
{
    if (size == 0)
        return -1;

    T *newArray = new T[size - 1];

    for (int i = 0; i < size - 1; i++)
    {
        newArray[i] = array[i];
    }
    rearrangePointers(newArray, false);

    return 0;
}

template <typename T>
int Array<T>::deleteElement(int index)
{
    int resultOfOperation;

    if (index > 0 && index < size)
    {
        T *newArray = new T[size - 1];

        for (int i = 0; i < index; i++)
            newArray[i] = array[i];

        for (int i = index; i < size - 1; i++)
            newArray[i] = array[i + 1];

        rearrangePointers(newArray, false);

        resultOfOperation = 0;
    }
    else
        resultOfOperation = -2;

    return resultOfOperation;
}
template <typename T>
void Array<T>::display()
{
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

template <typename T>
void Array<T>::generateArray(int size, T maxValue, T minValue)
{
    T *newArray = new T[size];

    uniform_int_distribution<> dist(minValue, maxValue);

    for (int i = 0; i < size; i++)
        newArray[i] = dist(generator);

    this->size = size;
    delete[] array;
    array = newArray;
}

template <typename T>
void Array<T>::rearrangePointers(T *newArray, bool incrementSize)
{
    // based on given parameter increments or decrements size by 1;
    if (incrementSize)
        size++;
    else
        size--;

    delete[] array;
    array = newArray;
}

template <typename T>
int Array<T>::getSize()
{
    return size;
}