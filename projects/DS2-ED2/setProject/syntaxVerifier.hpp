#ifndef SYNTAX_VERIFIER
#define SYNTAX_VERIFIER

#include <string>

string removeWhiteSpaces(string myString)
{
    string string4replace = "";
    for (int i = 0; i < (int) myString.size(); i++)
    {
        if (myString[i] != ' ')
            string4replace += myString[i];
    }
    return string4replace;
}

bool isAlphabetic(string myString)
{
    bool notAlphabetic = false;

    for (int i = 0; i < (int) myString.size(); i++)
    {
        if (!((myString[i] >= 'a' && myString[i] <= 'z') || (myString[i] >= 'A' && myString[i] <= 'Z')))
        {
            notAlphabetic = true;
            break;
        }
    }
    return !notAlphabetic;
}

bool areNumbers(string myString)
{
    bool areNotNumbers = false;
    for (int i = 0; i < (int) myString.size(); i++)
    {
        if (myString[i] < '0' || myString[i] > '9')
        {
            areNotNumbers = true;
            break;
        }
    }
    return !areNotNumbers;
}

bool haveMoreThanOneParameter(string myNum)
{
    int lastIndex = (int)myNum.size() - 1;
    for (int i = 0; i < (int)myNum.size(); i++)
    {
        if (myNum[i] == ' ' && i != lastIndex && myNum[i+1] != ' ')
            return true;
    }
    return false;
}

#endif