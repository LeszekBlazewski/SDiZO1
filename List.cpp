#include <iostream>
#include <fstream>
#include <random>

#include "List.h"

using namespace std;

template <typename T>
List<T>::List(mt19937 generator) : generator(generator)
{
    tail = nullptr;
    head = nullptr;
}

template <typename T>
List<T>::~List()
{
    clearList();
}

template <typename T>
void List<T>::clearList()
{
    if (head != nullptr) // check if list is not empty
    {
        Node<T> *ptr = head;         // save the head as temp to iterate
        while (ptr->next != nullptr) // check if we have reached the end of the list
        {
            ptr = ptr->next;  // assign next pointer to iterator
            delete ptr->prev; // delete previous pointer
        }
        delete ptr; // delete the last pointer (iterator)
        head = nullptr;
        tail = nullptr;
    }
}

template <typename T>
void List<T>::push_front(T value)
{
    Node<T> *newNode = new Node<T>; //create new node for pointer
    newNode->data = value;          // assign value
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (head == nullptr) //check if list is empty if so assign tail & head to the new pointer (head assigned at end)
        tail = newNode;
    else
    {
        newNode->prev = nullptr; //new node becomes head so prev is nullptr
        newNode->next = head;    //next points to head
        head->prev = newNode;    //prev from head points to new node
    }
    head = newNode; //assign new node as head
}

template <typename T>
void List<T>::push_back(T value)
{
    Node<T> *newNode = new Node<T>;
    newNode->data = value;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (head == nullptr) // if list is empty => head == tail so asign new node to head && to tail (end of function)
        head = newNode;
    else
    {
        newNode->next = nullptr; // new node becomes tail so it must point to null
        newNode->prev = tail;    // previous from new node must point to the current tail
        tail->next = newNode;    // current tail must point to newly created node
    }
    tail = newNode; // tail becomes new node
}

template <typename T>
int List<T>::addElement(int index, T value)
{
    // if empty list or given index was 0 (push front)
    if (index == 0 || head == nullptr)
    {
        push_front(value);
        return 0;
    }

    if (index < 0) //check if user inserted resonable index
        return -1;

    //insert new item between nodes (algorithm searches the node which index was provided and inserts the node before it)

    Node<T> *newNode = new Node<T>;
    newNode->data = value;

    Node<T> *tmp = head; //stores node which is searched (based on given index)

    for (int t = 0; t < index; t++)
    {
        if (tmp)
            tmp = tmp->next; //move to the insertion point
        else
            break;
    }

    //this ensures that whenever user inserts a index which is greater or equal zero new value will be pushed as last element
    if (tmp == nullptr) //this means that we have reached the tail so we can push back
    {
        push_back(value);
        return 0;
    }

    // Algorithm to isnert node before node found in loop

    newNode->next = tmp; //next node of the new one is the node which is currently on position given by index parameter

    newNode->prev = tmp->prev; // previous node of new node becaomes the previous one from the old node (because we insert BEFORE the node at index position)

    tmp->prev->next = newNode; //node before the node at index postion must point to new node

    tmp->prev = newNode; // we insert BEFORE given node so previous node of the node at idex postion points to new node

    return 0;
}

template <typename T>
int List<T>::loadFromFile(string filename)
{
    ifstream stream(filename, ifstream::in);
    if (!stream)
        return -1;
    int length;
    T value;
    stream >> length;
    clearList();
    for (int i = 0; i < length; i++)
    {
        stream >> value;
        addElement(i, value);
    }
    stream.close();
    return 0;
}

template <typename T>
void List<T>::generateList(int size, T minValue, T maxValue)
{
    clearList();

    uniform_int_distribution<> dist(minValue, maxValue);

    for (int i = 0; i < size; i++)
        push_back(dist(generator));
}

template <typename T>
Node<T> *List<T>::findElement(T value)
{
    Node<T> *ptr = head; // we need help pointer to not mess up the links in the list
    while (ptr != nullptr)
    {
        if (ptr->data == value)
            return ptr;
        ptr = ptr->next;
    }
    return ptr; // if element wasn't found return ptr == nullptr
}

template <typename T>
void List<T>::pop_front()
{
    if (head != nullptr)
    {
        Node<T> *node = head;
        head = head->next;
        if (head != nullptr)
            head->prev = nullptr;
        delete node;
    }
}

template <typename T>
void List<T>::pop_back()
{
    if (tail != nullptr)
    {
        Node<T> *node = tail;
        tail = tail->prev;
        if (tail != nullptr)
            tail->next = nullptr;
        delete node;
    }
}

template <typename T>
int List<T>::deleteElement(T value)
{
    Node<T> *p = findElement(value);

    if (p != nullptr)
    {
        Node<T> *pPrev, *pNext;
        pPrev = p->prev;
        pNext = p->next;

        if (pNext != nullptr)
            pNext->prev = pPrev;
        else
            tail = pPrev;

        if (pPrev != nullptr)
            pPrev->next = pNext;
        else
            head = pNext;

        delete p;

        return 0;
    }
    else
        return -1;
}

template <typename T>
void List<T>::display()
{
    cout << endl;

    //display list in standard order
    Node<T> *ptr = head; // we need help pointer to not mess up the links in the list
    while (ptr != nullptr)
    {
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
    cout << endl;

    //display list from the end
    ptr = tail;
    while (ptr != nullptr)
    {
        cout << ptr->data << " ";
        ptr = ptr->prev;
    }
    cout << endl;
}