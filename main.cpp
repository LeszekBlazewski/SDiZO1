#include <iostream>
#include <chrono>
#include <random>
using namespace std;

#include "Array.cpp"
#include "List.cpp"
#include "Heap.cpp"
#include "BstTree.cpp"

void displayMenuStructure(string info)
{
    cout << endl;
    cout << info << endl;
    cout << "1.Zbuduj z pliku" << endl;
    cout << "2.Usuń" << endl;
    cout << "3.Dodaj" << endl;
    cout << "4.Znajdź" << endl;
    cout << "5.Utworz losowo" << endl;
    cout << "6.Wyświetl" << endl;
    if (info == "---- DRZEWO BST ----")
    {
        cout << "7.Równoważenie drzewa BST (DSW)" << endl;
        cout << "8.Test (pomiary)" << endl;
    }
    else
        cout << "7.Test (pomiary)" << endl;

    cout << "0.Powrot do menu" << endl;
    cout << "Podaj opcje:";
}

void displayMainMenu()
{
    cout << endl;
    cout << "==== MENU GLOWNE ====" << endl;
    cout << "1.Tablica" << endl;
    cout << "2.Lista" << endl;
    cout << "3.Kopiec" << endl;
    cout << "4.Drzewo BST" << endl;
    cout << "5.Przygotuj dane testowe" << endl;
    cout << "0.Wyjscie" << endl;
    cout << "Podaj opcje:";
}

void displayMenuArray(Array<int> *array)
{
    int userInput, index, resultOfOperation, elementValue, addOption;
    do
    {
        displayMenuStructure("---- TABLICA ----");
        cin >> userInput;
        cout << endl;
        switch (userInput)
        {
        case 1:
        { //load table from file
            cout << "Podaj nazwe pliku: ";
            string filename;
            cin >> filename;
            if (array->loadFromFile(filename) == -1)
                cout << "Wczytywanie nie powiodło się!" << endl;
            else
            {
                cout << "Dane zostały wczytane" << endl;
                array->display();
            }
            break;
        }
        case 2: // remove element by given postion
            cout << "Podaj indeks w tablicy do usunięcia, zakres [0,n-1] gdzie n to rozmiar tablicy:" << endl;
            cin >> index;
            if (index == 0)
                resultOfOperation = array->deleteElementFront();
            else if (index == array->getSize() - 1)
                resultOfOperation = array->deleteElementBack();
            else
                resultOfOperation = array->deleteElement(index);

            if (resultOfOperation == -1)
                cout << "Brak elementów do usunięcia !" << endl;
            else if (resultOfOperation == -2)
                cout << "Podano nieprawidłowy indeks !" << endl;
            else
                array->display();
            break;
        case 3: // add element by given postion
            cout << "Podaj indeks w tablicy na którym powinien zostać dodany nowy element, zakres [0,n-1] lub n (jeśli element ma być dodany na koniec), gdzie n to rozmiar tablicy." << endl;
            cin >> index;
            cout << "Podaj wartość elementu, który należy dodać:";
            cin >> elementValue;
            if (index == 0)
            {
                array->addElementFront(elementValue);
                resultOfOperation = 0;
            }
            else if (index == array->getSize())
            {
                array->addElementBack(elementValue);
                resultOfOperation = 0;
            }
            else
                resultOfOperation = array->addElement(index, elementValue);

            if (resultOfOperation == -1)
                cout << "Podano błędny indeks !" << endl;
            else
                array->display();

            break;
        case 4: //search array for given element
        {
            cout << "Podaj wartość elementu, który należy wyszukać:";
            cin >> elementValue;
            bool isInTable = array->isElementInArray(elementValue);
            if (isInTable)
                cout << "Element znajduje się w tablicy" << endl;
            else
                cout << "Podany element nie występuje w tablicy" << endl;

            break;
        }
        case 5: // generate random values and fill the table
            cout << "Podaj rozmiar tablicy:";
            int length;
            cin >> length;
            array->generateArray(length);
            array->display();
            break;
        case 6: //display the table
            array->display();
            break;
        case 7: //funckja służąca do testowania.
            break;
        }
    } while (userInput != 0);
}

void displayMenuList(List<int> *list)
{
    int userInput, index, elementValue, resultOfOperation;
    do
    {
        displayMenuStructure("---- LISTA ----");
        cin >> userInput;
        cout << endl;
        switch (userInput)
        {
        case 1:
        { // load list from file
            cout << "Podaj nazwe pliku: ";
            string filename;
            cin >> filename;
            if (list->loadFromFile(filename) == -1)
                cout << "Wczytywanie nie powiodło się!" << endl;
            else
            {
                cout << "Dane zostały wczytane\n\n";
                list->display();
            }
            break;
        }
        case 2: // remove element by given value
            cout << "Podaj wartość do usunięcia:" << endl;
            cin >> elementValue;
            resultOfOperation = list->deleteElement(elementValue);
            if (resultOfOperation == -1)
                cout << "Podana wartość nie występuje na liście !" << endl;
            else
                list->display();
            break;
        case 3: // add element by given postion
            cout << "Podaj indeks na którym ma zostać dodany element:";
            cin >> index;
            cout << "Podaj wartość elementu, który należy dodać:";
            cin >> elementValue;
            resultOfOperation = list->addElement(index, elementValue);
            if (resultOfOperation == -1)
                cout << "Podano błędny indeks !" << endl;
            else
                list->display();
            break;
        case 4: // search list for given element
        {
            cout << "Podaj wartość elementu, który należy wyszukać:";
            cin >> elementValue;
            Node<int> *element = list->findElement(elementValue);
            if (element != nullptr)
                cout << "Element znajduje się na liście." << endl;
            else
                cout << "Podany element nie występuje na liście." << endl;
            break;
        }
        case 5: // generate random values and fill the list
            cout << "Podaj rozmiar listy:";
            int size;
            cin >> size;
            list->generateList(size);
            list->display();
            break;
        case 6: //display the list
            list->display();
            break;
        case 7: //funckja służąca do testowania.
            break;
        }
    } while (userInput != 0);
}

void displayMenuHeap(Heap<int> *heap)
{
    int userInput, elementValue, resultOfOperation;
    do
    {
        displayMenuStructure("---- KOPIEC ----");
        cin >> userInput;
        cout << endl;
        switch (userInput)
        {
        case 1:
        { //load heap from file
            cout << "Podaj nazwe pliku: ";
            string filename;
            cin >> filename;
            if (heap->loadFromFile(filename) == -1)
                cout << "Wczytywanie nie powiodło się!" << endl;
            else
            {
                cout << "Dane zostały wczytane\n\n";
                heap->display();
            }
            break;
        }
        case 2: // remove element by given value
            cout << "Podaj wartość do usunięcia:" << endl;
            cin >> elementValue;
            resultOfOperation = heap->deleteElement(elementValue);
            if (resultOfOperation == -1)
                cout << "Podana wartość nie występuje w kopcu !" << endl;
            else
                heap->display();
            break;
        case 3: // add element
            cout << "Podaj wartość elementu, który należy dodać:";
            cin >> elementValue;
            heap->addElement(elementValue);
            heap->display();
            break;
        case 4: //search heap for given element
        {
            cout << "Podaj wartość elementu, który należy wyszukać:";
            cin >> elementValue;
            int elemPosition = heap->findElementPosition(elementValue);
            if (elemPosition != -1)
                cout << "Element znajduje się w kopcu." << endl;
            else
                cout << "Podany element nie występuje w kopcu." << endl;
            break;
        }
        case 5: // generate random values and fill the heap
            cout << "Podaj ilość elementów do wygenerowania:";
            int size;
            cin >> size;
            heap->generateHeap(size);
            heap->display();
            break;
        case 6: //display the heap
            heap->display();
            break;
        case 7: //funckja służąca do testowania.
            break;
        }
    } while (userInput != 0);
}

void displayMenuTree(BstTree<int> *tree)
{
    int userInput, elementValue, resultOfOperation;
    do
    {
        displayMenuStructure("---- DRZEWO BST ----");
        cin >> userInput;
        cout << endl;
        switch (userInput)
        {
        case 1:
        { //load tree from file
            cout << "Podaj nazwe pliku: ";
            string filename;
            cin >> filename;
            if (tree->loadFromFile(filename) == -1)
                cout << "Wczytywanie nie powiodło się!" << endl;
            else
            {
                cout << "Dane zostały wczytane\n\n";
                tree->display();
            }
            break;
        }
        case 2: // remove element by given value
            cout << "Podaj wartość do usunięcia:" << endl;
            cin >> elementValue;
            resultOfOperation = tree->deleteElement(elementValue);
            if (resultOfOperation == -1)
                cout << "Podana wartość nie występuje w kopcu !" << endl;
            else
                tree->display();
            break;
        case 3: // add element
            cout << "Podaj wartość elementu, który należy dodać:";
            cin >> elementValue;
            tree->addElement(elementValue);
            tree->display();
            break;
        case 4: //search tree for given element
        {
            cout << "Podaj wartość elementu, który należy wyszukać:";
            cin >> elementValue;
            BstNode<int> *node = tree->findNode(elementValue);
            if (node)
                cout << "Element znajduje się w drzewie." << endl;
            else
                cout << "Podany element nie występuje w drzewie." << endl;
            break;
        }
        case 5: // generate random values and fill the tree
            cout << "Podaj rozmiar drzewa:";
            int size;
            cin >> size;
            tree->generateTree(size);
            tree->display();
            break;
        case 6: //display the tree
            tree->display();
            break;
        case 7: //DSW algorithm to rebalance the tree
            tree->rebalanceDSW();
            tree->display();
            break;
        case 8: // test function
            break;
        }
    } while (userInput != 0);
}
int main()
{
    random_device rd;
    mt19937 generator(rd());
    Array<int> *array = new Array<int>(generator);
    List<int> *list = new List<int>(generator);
    Heap<int> *heap = new Heap<int>(generator);
    BstTree<int> *tree = new BstTree<int>(generator);
    int option;
    do
    {
        displayMainMenu();
        cin >> option;

        switch (option)
        {
        case 1:
            displayMenuArray(array);
            break;
        case 2:
            displayMenuList(list);
            break;
        case 3:
            displayMenuHeap(heap);
            break;
        case 4:
            displayMenuTree(tree);
            break;
        case 5:
            break;
        }
    } while (option != 0);

    cout << "Zakończono działanie programu" << endl;
    if (array)
        delete array;
    if (list)
        delete list;
    if (heap)
        delete heap;
    if (tree)
        delete tree;

    return 0;
}