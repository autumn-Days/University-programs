#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <limits>
#include "node.hpp"
#include "set.hpp"
#include "syntaxVerifier.hpp"

using namespace std;

void inserter(Set<int>*& mySet)
{
    string lim = "";
    cout << "Quantos elementos você deseja inserir?" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, lim);
    
    try
    {
        //tratamento de erros do limite
        if (lim.size() == 0)
            throw invalid_argument(insufficientParameters());
        else if (haveMoreThanOneParameter(lim))
            throw invalid_argument(excessiveParameters());
        else if (!areNumbers(lim))
            throw invalid_argument(illegalCharacters());
        else
        {
            lim = removeWhiteSpaces(lim);
            int lim2 = stoi(lim);
            if (lim2 < 1)
                throw invalid_argument(negativeSuperiorLimit());
            else if (lim2 == 1)
                cout << "Qual é?" << endl;
            else
                cout << "Quais são?" << endl;

            string num = "";

            for (int i = 0; i < lim2; i++)
            {
                cin >> num;
                if ((int) num.size() == 0)
                    throw invalid_argument(insufficientParameters());
                else if (!areNumbers(num))
                    throw invalid_argument(warningOnlyIntegersAllowed());
                else
                {
                    mySet->insert(stoi(num));
                }
            }
        }
    }
    catch (exception &erro)
    {
        cout << erro.what() << endl;
    }
}

void remover(Set<int>*&mySet)
{
    //Esta condição está tratada no SET, o único motivo para esta condição existir
    //é para que as perguntas que se sigam só sejam feitas caso o conjunto não es-
    //teja vazio
    if (mySet->empty())
        cout << "ERRO: O conjunto está vazio!" << endl;
    else
    {  
        string lim = "";
        cout << "Quantos elementos você deseja excluir?" << endl;
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, lim);

        try
        {
            if ((int)lim.size() == 0)
                throw invalid_argument(insufficientParameters());
            else if (haveMoreThanOneParameter(lim))
                throw invalid_argument(excessiveParameters());
            else if (!areNumbers(lim))
                throw invalid_argument(illegalCharacters());
            else
            {
                lim = removeWhiteSpaces(lim);
                int lim2 = stoi(lim);
                if (lim2 < 1)
                    throw invalid_argument(negativeSuperiorLimit());
                //begin printing messages
                else if (lim2 == 1)
                    cout << "Qual é o elemento ";
                else if (lim2 > 1)
                    cout << "Quais são os elementos ";
                cout << "que você deseja remover?" << endl;
                //end printing messages
                string num = "";
                for (int i = 0; i < lim2; i++)
                {
                    cin >>num;

                    if ((int)num.size() == 0)
                        throw invalid_argument(insufficientParameters());
                    else if (!areNumbers(num))
                        throw invalid_argument(illegalCharacters());
                    else
                    {
                        mySet->erase(stoi(num));
                    }
                }
            }
        }
        catch(exception& erro)
        {
            cout << erro.what() << endl;
        }
    }
}

void _displayPreOrder(Node<int>*root)
{
    if (root == nullptr)
        return;
    cout << root->info << endl;
    _displayPreOrder(root->left);
    _displayPreOrder(root->right);
}

void _displayInOrder(Node<int>*root)
{
    if (root == nullptr)
        return;
    _displayInOrder(root->left);
    cout << root->info << endl;
    _displayInOrder(root->right);
    
}

void _displayPostOrder(Node<int>* root)
{
    if (root == nullptr)
        return;
    _displayPostOrder(root->left);
    _displayPostOrder(root->right);
    cout << root->info << endl;
}

void displayInOrder(Set<int>*mySet)
{
    if (!mySet->root)
        cout << "O set está vazio!" << endl;
    _displayInOrder(mySet->root);
}

void displayPreOrder(Set<int>*mySet)
{
    if (!mySet->root)
        cout << "O set está vazio!" << endl;
    _displayPreOrder(mySet->root);
}

void displayPostOrder(Set<int>* mySet)
{
    if (!mySet->root)
        cout << "O set está vazio!" << endl;
    _displayPostOrder(mySet->root);
}

#endif