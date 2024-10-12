#ifndef READ_FILE_H
#define READ_FILE_H

#define MAX_SIZE 1024

#include <unicode/unistr.h>
#include <unicode/uchar.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

using namespace std;
using namespace icu;


/*
Esta função irá ler o conteúdo de um arquivo de texto
e retornar um vector de palavras codificadas em unicode.
*/
vector<UnicodeString> getContent(string titleFile)
{
    ifstream inputFile(titleFile);
    if (!inputFile.is_open())
        throw invalid_argument("ERROR! The fiel couldn't be opened!");

    /*
    All the words are going to be store inside "words". Meanwhile, the
    "word" will be a single word that will be inserted to "words". Also
    the current line will be the line that is being analysed. Unforuna-
    tly, it will have to be a string and not a UnicodeString, because
    "getline" can't handle UnicodeString's. So it will be needed to con-
    vert it later.
    */
    vector<UnicodeString> words;
    UnicodeString word;

    string currentLineStd;

    while (getline(inputFile, currentLineStd))
    {
        //Conversion from std::string to a UnicodeString
        UnicodeString currentLine = UnicodeString::fromUTF8(currentLineStd);
        
        /*
        For every line that is being analysed, it is needed to be sure that the
        maximum limit of words were not violated
        */
        if (words.size() == 1024)
            break;

        /*
        The reasoning now will be to read every character individually and
        append it to the "word" defined of line 39. When the character is
        a separator, such as a white space or a comma, the word will be
        appended into "words" and the "word" will be cleared to keep inser-
        ting elements.
        */
        
        UChar hyphen = static_cast<UChar>('-'); 
        UChar space = static_cast<UChar>(' ');

        for (int i = 0; i < currentLine.length(); i++)
        {
            if (words.size() == 1024)
                break;

            UChar currentChar = currentLine.charAt(i);

            /*
            Adds the hyphen to the word.
            */
            if (currentChar == hyphen)
            {
                if (i < currentLine.length() && i != 0 && u_isalpha(currentLine.charAt(i-1)))
                {
                    UChar nextChar = currentLine.charAt(i+1);
                    if (u_isalpha(nextChar))
                    {
                        word.append(currentChar);
                    }
                }
            }
            
            /*
            When the character is alphanumeric it will be always wishful
            to append it to the "word", otherwise, it will be a separator.
            */
            else if (u_isalpha(currentChar))
            {
                UChar lowerChar = u_tolower(currentChar);
                word.append(lowerChar);
            }
            else
            {
                //The word can only be inserted if it not an empty word
                if (!word.isEmpty())
                {
                    words.push_back(word);
                    word.remove();
                }
            }
        }

        /*
        There is still the possibility the loop was breaked, but there is still information
        inside "word", so it needs to be inserted.
        */
        if (!word.isEmpty() && words.size() < 1024)
        {
            words.push_back(word);
            word.remove();
        }
    }
    return words;
}


#endif