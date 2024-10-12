#include "AVL.hpp"
#include "RED_BLACK_H.hpp"
#include "enderecamentoAberto.hpp"
#include "encadeamentoExterior.hpp"
#include "readFile.hpp"
#include <iostream>
#include <chrono>

using namespace std;

int main(int argc, char* argv[])
{
    /*The arguments are received via CLI*/
    if (argc != 3)
    {
        throw invalid_argument("ERROR! WRONG AMOUNT OF ARGUMENTS\n USE: freq <AVL|RB|hashOpen|hashExt> <file>.txt");
    }
    string dataStructure = argv[1];
    string book = argv[2];
    vector<UnicodeString> bookContent = getContent(book);

    /*
    The overall idea is that for each word at the book, it will first be checked
    if it is already contained in the structure. If this isn't the case, it is 
    insert with the value of one (since it is the first aparation of the word),
    otherwise, its value will be obtained and be saved into a integer named
    "value", which its incrementation will correspond to new value of the pair
    in question.
    */

    if (dataStructure == "AVL")
    {
        AVLtree<UnicodeString,int>* myAVL = new AVLtree<UnicodeString,int>();
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < bookContent.size(); i++)
        {
            if (!myAVL->contains(bookContent[i]))
                myAVL->add(bookContent[i],1);
            else
            {
                int value = myAVL->get(bookContent[i]);
                myAVL->modify(bookContent[i],value+1);
            }
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << "-=-=-=-=-=-Frequency=-=-=-=-=-=-=" << endl;
        myAVL->inOrderUni();
        cout << "-=-=-=-=-=-=Comparisons-=-=-=-=-=-=" << endl;
        cout << myAVL->getCounter() << endl;
        cout << "-=-=-=-=-=-=-=Duration-=-=-=-=-=-=-=" << endl;
        double durationInSeconds = duration / 1000000.0;
        cout << durationInSeconds << " seconds" << endl;
    }
    else if (dataStructure == "RB")
    {
        RedBlackTree<UnicodeString,int>* myRB = new RedBlackTree<UnicodeString,int>();
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < bookContent.size(); i++)
        {
            if (!myRB->contains(bookContent[i]))
                myRB->add(bookContent[i],1);
            else
            {
                int value = myRB->get(bookContent[i]);
                myRB->modify(bookContent[i],value+1);
            }
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << "-=-=-=-=-=-Frequency=-=-=-=-=-=-=" << endl;
        myRB->inOrderUni();
        cout << "-=-=-=-=-=-=Comparisons-=-=-=-=-=-=" << endl;
        cout << myRB->getCounter() << endl;
        cout << "-=-=-=-=-=-=-=Duration-=-=-=-=-=-=-=" << endl;
        double durationInSeconds = duration / 1000000.0;
        cout << durationInSeconds << " seconds" << endl;
    }
    else if (dataStructure == "hashExt")
    {
        hashEncadeamentoExt<UnicodeString, int, hashUnicodeString>* hashExt = new hashEncadeamentoExt<UnicodeString,int,hashUnicodeString>(10);
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < bookContent.size(); i++)
        {
            if (!hashExt->contains(bookContent[i]))
                hashExt->add(bookContent[i],1);
            else
            {
                int value = hashExt->get(bookContent[i]);
                hashExt->modify(bookContent[i],value+1);
            }
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << "-=-=-=-=-=-Frequency=-=-=-=-=-=-=" << endl;
        hashExt->inOrderUni();
        cout << "-=-=-=-=-=-=Comparisons-=-=-=-=-=-=" << endl;
        cout << hashExt->getCounter() << endl;
        cout << "-=-=-=-=-=-=-=Duration-=-=-=-=-=-=-=" << endl;
        double durationInSeconds = duration / 1000000.0;
        cout << durationInSeconds << " seconds" << endl;
    }
    
    else if (dataStructure == "hashOpen")
    {
        HashAddrAberto<UnicodeString, int, hashUnicodeString2>* hashOpen = new HashAddrAberto<UnicodeString,int,hashUnicodeString2>(10);
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < bookContent.size(); i++)
        {
            if (!hashOpen->contains(bookContent[i]))
                hashOpen->add(bookContent[i],1);
            else
            {
                int value = hashOpen->get(bookContent[i]);
                hashOpen->modify(bookContent[i],value+1);
            }
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << "-=-=-=-=-=-Frequency=-=-=-=-=-=-=" << endl;
        hashOpen->inOrderUni();
        cout << "-=-=-=-=-=-=Comparisons-=-=-=-=-=-=" << endl;
        cout << hashOpen->getCounter() << endl;
        cout << "-=-=-=-=-=-=-=Duration-=-=-=-=-=-=-=" << endl;
        double durationInSeconds = duration / 1000000.0;
        cout << durationInSeconds << " seconds" << endl;
    }
    else
        throw invalid_argument("No such a option!");
}