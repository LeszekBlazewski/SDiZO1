#include <iostream>
#include <chrono>
#include <random>
#include <bits/stdc++.h>
using namespace std;

#include "Array.cpp"
#include "List.cpp"
#include "Heap.cpp"
#include "BstTree.cpp"

// do testow, maxMem/keySize w bajtach
long long maxMem = 1000000000;
int keySize = sizeof(int);
int maxD = maxMem / keySize;
random_device rd;  // seed
mt19937 gen(rd()); // rng engine

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
        {
            const int dataRanges[8] = {10, 100, INT_MAX / 2 - 100000000, INT_MAX / 2 + 100000000, INT_MAX - 200000000, INT_MAX, 1, INT_MAX};
            const int dataRangesCount = 4;
            const int minElements = 16;
            const int minTestPrecision = 1;
            ofstream testOutput("Array.txt");
            if (!testOutput)
            {
                cout << "BLAD zapisu testow!";
            }
            testOutput << "CZASY  OPERACJI W NANOSEKUNDACH\n";
            cout << "Wstawianie na koniec...";
            testOutput << "Wstawianie na koniec:\n";
            {
                testOutput << "wielkosc struktury\t[1,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = 2500000 / i;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        array->generateArray(i, dataRanges[k * 2 + 1], dataRanges[k * 2]);
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            array->addElementBack(dis(gen));
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = (chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision;
                        testOutput << "\t" << timeResult;
                    }
                    testOutput << endl;
                }
            }
            cout << "DONE!\nWstawianie na środek...";
            testOutput << "Wstawianie na środek:\n";
            {
                testOutput << "wielkosc struktury\t[1,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = 2500000 / i;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        array->generateArray(i, dataRanges[k * 2 + 1], dataRanges[k * 2]);
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            array->addElement(i / 2, dis(gen));
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = (chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision;
                        testOutput << "\t" << timeResult;
                    }
                    testOutput << endl;
                }
            }
            cout << "DONE!\nWstawianie na początek...";
            testOutput << "Wstawianie na początek:\n";
            {
                testOutput << "wielkosc struktury\t[1,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = 2500000 / i;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        array->generateArray(i, dataRanges[k * 2 + 1], dataRanges[k * 2]);
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            array->addElementFront(dis(gen));
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = (chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision;
                        testOutput << "\t" << timeResult;
                    }
                    testOutput << endl;
                }
            }
            cout << "DONE!\nWyszukiwanie - klucz poza przedziałem...";
            testOutput << "Wyszukiwanie - klucz poza przedziałem:\n";
            {
                testOutput << "wielkosc struktury\t[1,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = 2500000 / i;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        array->generateArray(i, dataRanges[k * 2 + 1], dataRanges[k * 2]);
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            array->isElementInArray(-1);
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = (chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision;
                        testOutput << "\t" << timeResult;
                    }
                    testOutput << endl;
                }
            }
            cout << "DONE!\nUsuwanie z końca...";
            testOutput << "Usuwanie z końca:\n";
            {
                testOutput << "wielkosc struktury\t[1,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = 2500000 / i;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            array->deleteElementBack();
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = (chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision;
                        testOutput << "\t" << timeResult;
                    }
                    testOutput << endl;
                }
            }
            cout << "DONE!\nUsuwanie z środka...";
            testOutput << "Usuwanie z środka:\n";
            {
                testOutput << "wielkosc struktury\t[1,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = 2500000 / i;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        array->generateArray(i, dataRanges[k * 2 + 1], dataRanges[k * 2]);
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            array->deleteElement(i / 2);
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = (chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision;
                        testOutput << "\t" << timeResult;
                    }
                    testOutput << endl;
                }
            }
            cout << "DONE!\nUsuwanie z początku...";
            testOutput << "Usuwanie z początku:\n";
            {
                testOutput << "wielkosc struktury\t[1,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = 2500000 / i;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        array->generateArray(i, dataRanges[k * 2 + 1], dataRanges[k * 2]);
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            array->deleteElementFront();
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = (chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision;
                        testOutput << "\t" << timeResult;
                    }
                    testOutput << endl;
                }
            }
            cout << "DONE!\n";
            testOutput.close();
            break;
        }
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
        {
            const int dataRanges[8] = {10, 100, INT_MAX / 2 - 100000000, INT_MAX / 2 + 100000000, INT_MAX - 200000000, INT_MAX, 1, INT_MAX};
            const int dataRangesCount = 4;
            const int minElements = 16;
            const int minTestPrecision = 2;
            const int baseTestPrecision = 3000000;
            ofstream testOutput("List.txt");
            if (!testOutput)
            {
                cout << "BLAD zapisu testow!";
            }
            testOutput << "CZASY  OPERACJI W NANOSEKUNDACH\n";
            cout << "Wstawianie na koniec...";
            testOutput << "Wstawianie na koniec:\n";
            {
                testOutput << "wielkosc struktury\t[10,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = baseTestPrecision / i;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        list->generateList(i, dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            list->push_back(dis(gen));
                            list->pop_front();
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = ((chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision) - 60;
                        testOutput << "\t" << timeResult;
                    }

                    testOutput << endl;
                }
            }
            cout << "DONE!\nWstawianie na środek...";
            testOutput << "Wstawianie na środek:\n";
            {
                testOutput << "wielkosc struktury\t[10,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = baseTestPrecision / i;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        list->generateList(i, dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            list->addElement(i / 2, dis(gen));
                            list->pop_front();
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = ((chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision) - 60;
                        testOutput << "\t" << timeResult;
                    }

                    testOutput << endl;
                }
            }
            cout << "DONE!\nWstawianie na początek...";
            testOutput << "Wstawianie na początek:\n";
            {
                testOutput << "wielkosc struktury\t[10,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = baseTestPrecision;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        list->generateList(i, dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            list->push_front(dis(gen));
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = (chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision;
                        testOutput << "\t" << timeResult;
                    }
                    testOutput << endl;
                }
            }
            cout << "DONE!\nWyszukiwanie - klucz poza przedziałem...";
            testOutput << "Wyszukiwanie - klucz poza przedziałem:\n";
            {
                testOutput << "wielkosc struktury\t[1,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = baseTestPrecision / i;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        list->generateList(i, dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            list->findElement(-1);
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = (chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision;
                        testOutput << "\t" << timeResult;
                    }
                    testOutput << endl;
                }
            }
            cout << "DONE!\nUsuwanie z końca...";
            testOutput << "Usuwanie z końca:\n";
            {
                testOutput << "wielkosc struktury\t[1,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = baseTestPrecision / i;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        list->generateList(i, dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            list->pop_back();
                            list->push_front(dis(gen));
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = ((chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision) - 140;
                        testOutput << "\t" << timeResult;
                    }
                    testOutput << endl;
                }
            }
            cout << "DONE!\nUsuwanie z środka...";
            testOutput << "Usuwanie z środka:\n";
            {
                testOutput << "wielkosc struktury\t[1,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = baseTestPrecision / i;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        list->generateList(i, dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            list->deleteElement(i / 2);
                            list->push_front(dis(gen));
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = ((chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision) - 140;
                        testOutput << "\t" << timeResult;
                    }
                    testOutput << endl;
                }
            }
            cout << "DONE!\nUsuwanie z początku...";
            testOutput << "Usuwanie z początku:\n";
            {
                testOutput << "wielkosc struktury\t[1,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = baseTestPrecision;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        list->generateList(i, dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            list->pop_front();
                            list->push_front(dis(gen));
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = ((chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision) - 140;
                        testOutput << "\t" << timeResult;
                    }
                    testOutput << endl;
                }
            }
            cout << "DONE!\n";
            testOutput.close();
        }
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
        {
            const int dataRanges[8] = {10, 100, INT_MAX / 2 - 100000000, INT_MAX / 2 + 100000000, INT_MAX - 200000000, INT_MAX, 1, INT_MAX};
            const int dataRangesCount = 4;
            const int minElements = 16;
            const int minTestPrecision = 10;
            const int baseTestPrecision = 2500000;
            ofstream testOutput("Heap.txt");
            if (!testOutput)
            {
                cout << "BLAD zapisu testow!";
            }
            testOutput << "CZASY  OPERACJI W NANOSEKUNDACH - BEZ REALOKACJI\n";
            cout << "Wstawianie...";
            testOutput << "Wstawianie:\n";
            {
                testOutput << "wielkosc struktury\t[10,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = baseTestPrecision;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        heap->generateHeap(i, dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            heap->addElement(dis(gen));
                            //heap->deleteElementByPos(i);
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = ((chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision);
                        testOutput << "\t" << timeResult;
                    }
                    testOutput << endl;
                }
            }
            cout << "DONE!\nWyszukiwanie - klucz poza przedziałem..."; // OK
            testOutput << "Wyszukiwanie - klucz poza przedziałem:\n";
            {
                testOutput << "wielkosc struktury\t[10,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = (baseTestPrecision * 20) / i;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        heap->generateHeap(i, dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            heap->findElementPosition(-1);
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = (chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision;
                        testOutput << "\t" << timeResult;
                    }
                    testOutput << endl;
                }
            }
            cout << "DONE!\nUsuwanie...";
            testOutput << "Usuwanie:\n";
            {
                testOutput << "wielkosc struktury\t[10,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = baseTestPrecision;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        heap->generateHeap(i, dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            heap->heap_pop();
                            //heap->addElement(dis(gen));
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = ((chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision);
                        testOutput << "\t" << timeResult;
                    }
                    testOutput << endl;
                }
            }
            cout << "DONE!\n";
            testOutput.close();
            break;
        }
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
        {
            const int dataRanges[8] = {10, 100, INT_MAX / 2 - 100000000, INT_MAX / 2 + 100000000, INT_MAX - 200000000, INT_MAX, 1, INT_MAX};
            const int dataRangesCount = 4;
            const int minElements = 16;
            const int minTestPrecision = 10;
            const int baseTestPrecision = 2500000;
            ofstream testOutput("BstTree.txt");
            if (!testOutput)
            {
                cout << "BLAD zapisu testow!";
            }
            testOutput << "CZASY  OPERACJI W NANOSEKUNDACH\n";
            cout << "Wstawianie...";
            testOutput << "Wstawianie:\n";
            {
                testOutput << "wielkosc struktury\t[10,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = baseTestPrecision;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        tree->generateTree(i, dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        tree->rebalanceDSW();
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            tree->addElement(dis(gen));
                            tree->rebalanceDSW();
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = ((chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision);
                        testOutput << "\t" << timeResult;
                    }
                    testOutput << endl;
                }
            }
            cout << "DONE!\nWyszukiwanie - klucz poza przedziałem...";
            testOutput << "Wyszukiwanie - klucz poza przedziałem:\n";
            {
                testOutput << "wielkosc struktury\t[10,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = (baseTestPrecision * 20) / i;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        tree->generateTree(i, dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        tree->rebalanceDSW();
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            tree->findNode(-1);
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = (chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision;
                        testOutput << "\t" << timeResult;
                    }
                    testOutput << endl;
                }
            }
            cout << "DONE!\nUsuwanie...";
            testOutput << "Usuwanie:\n";
            {
                testOutput << "wielkosc struktury\t[10,100]\t[~INT_MAX/2]\t[~INT_MAX]\t[1,INT_MAX]\n";
                for (int i = minElements; i <= maxD; i *= 2)
                {
                    testOutput << i << "\t";
                    int testPrecision = baseTestPrecision;
                    if (testPrecision < minTestPrecision)
                    {
                        testPrecision = minTestPrecision;
                    }
                    for (int k = 0; k < dataRangesCount; k++)
                    {
                        uniform_int_distribution<> dis(dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        tree->generateTree(i, dataRanges[k * 2], dataRanges[k * 2 + 1]);
                        tree->rebalanceDSW();
                        auto startTime = chrono::high_resolution_clock::now();
                        for (int j = 0; j < testPrecision; j++)
                        {
                            tree->deleteElement(dis(gen));
                            tree->rebalanceDSW();
                        }
                        auto endTime = chrono::high_resolution_clock::now();
                        auto timeResult = ((chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count()) / testPrecision);
                        testOutput << "\t" << timeResult;
                    }
                    testOutput << endl;
                }
            }
            cout << "DONE!\n";
            testOutput.close();
            break;
        }
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