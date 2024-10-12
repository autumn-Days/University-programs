#ifndef HASH_ADDR_ABERTO_H
#define HASH_ADDR_ABERTO_H

#include <unicode/unistr.h>
#include <utility>
#include <functional>
#include <string>
#include <list>

#define EMPTY 0
#define ACTIVE 1
#define DELETED 2

using namespace std;

template <typename keyType,typename valueType>
class Cell
{
public:
    std::pair<keyType, valueType> info;
    int status;

    Cell() : status(EMPTY) {}
};

/*
Since it will be needed to hash "UnicodeString's" and the standard std::hash
doesn't provide any functionalities for performing such a thing, it is needed
to implement a special hash function only for this case. It will work by 
defining a structure and overloading the "()" operator, so that the structure
can be used as a function. A lighweight and good hash function is the DJB2.

This struct is ends with the suffix 2, because there is also an equivalent
implementation of it defined in the "encadeamentoExterior.h".
*/
struct hashUnicodeString2
{
    unsigned long operator()(icu::UnicodeString justString)
    {
        unsigned long hash = 5381;
        size_t length = justString.length();
        for (size_t i = 0; i < length; i++)
        {
            UChar ch = justString.charAt(i);
            hash = ((hash << 5) + hash) + (static_cast<unsigned long>(ch)%128);
        }
        return hash;
    }
};
template <typename keyType, typename valueType, typename hashAll = std::hash<keyType>>
class HashAddrAberto
{
public:
    Cell<keyType,valueType>** myHashTable;
    int maxSize;
    int amountElements;
    int amountElementsDeleted;
    int counter;

    HashAddrAberto(int initialMaxSize =10)
    {
        this->maxSize = initialMaxSize;
        this->amountElements =0;
        this->amountElementsDeleted = 0;
        this->counter =0;
        this->myHashTable = new Cell<keyType, valueType>*[maxSize];
        for (int i=0; i < maxSize; i++)
        {
            this->myHashTable[i] = new Cell<keyType, valueType>();
        }
    }

    ~HashAddrAberto()
    {
        for (int i=0; i < maxSize; i++)
        {
            delete myHashTable[i];
        }
        delete[] myHashTable;
    }

    int getCounter()
    {
        return this->counter;
    }

    bool add(keyType key, valueType value)
    {
        /*
        If the amount of elements reached half the maximum size
        of the hash table, then it is needed to make it larger.
        */
        if (this->amountElements >= this->maxSize/2)
            allocateMore();
        int index = hashFunction(key, this->maxSize);
        /*
        It is needed to keep looking for a free cell, while the the current cell that is being
        visited is not empty, neither can be overwritten 
        */
        while (myHashTable[index]->status != EMPTY && myHashTable[index]->status != DELETED)
        {
            /*
            While we are still trying to find a cell to insert the element, there is the
            possibility the element is already in the hash table, so, since is not a legal to
            have two keys that are equal to each other, we simply return "false" indicating the
            insertion failled*/
            this->counter++;
            if (myHashTable[index]->status == ACTIVE && myHashTable[index]->info.first == key)
                return false;
            index = (index+1)%maxSize;
        }
        /*
        If the while loop is completed, this means that a free cell was found and it possible to
        insert the pair <key,value> in it and update the counters.
        */
        this->myHashTable[index]->info= std::make_pair(key, value);
        this->myHashTable[index]->status = ACTIVE;
        this->amountElements++;
        return true;
    }

    /*
    The same logic of the "_add" method, but without updating the counters regarding
    the amount of elements.
    */
    bool modify(keyType key, valueType newValue)
    {
        int index = hashFunction(key, this->maxSize);
        while (myHashTable[index]->status != EMPTY && myHashTable[index]->status != DELETED)
        {
            this->counter++;
            if (myHashTable[index]->status == ACTIVE && myHashTable[index]->info.first == key)
            {
                myHashTable[index]->info.second = newValue;
                return true;
            }
            index = (index+1)%maxSize;
        }
        return false;

    }

    bool remove(keyType key)
    {
        int index = hashFunction(key, this->maxSize);
        /*
        After finding out the index of the element of the element that is wished to be deleted,
        it is needed to check if it is really located on that cell, if this isn't the case, the li-
        near probing is performed until the element is found.
        */
        while (myHashTable[index]->status != EMPTY)
        {
            //the element was found.
            if (myHashTable[index]->status == ACTIVE && myHashTable[index]->info.first == key)
            {

                this->myHashTable[index]->status = DELETED;
                this->amountElements--;
                this->amountElementsDeleted++;
                //if there are too many elements with the "DELETED" flag, then its time to make
                //the hash table smaller. The second condition is only for preveting seg. faults
                if (amountElementsDeleted > this->amountElementsDeleted/4 && amountElements != 0)
                    allocateLess();
                return true;
            }
            index = (index+1)%maxSize;
        }
        return false;
    }

    valueType get(keyType key)
    {
        int index = hashFunction(key, this->maxSize);
        //Keep looking for the key in question using linear probing while it wasn't found
        while (this->myHashTable[index]->status != EMPTY && this->myHashTable[index]->status!= DELETED)
        {
            this->counter++;
            if (this->myHashTable[index]->status == ACTIVE && this->myHashTable[index]->info.first == key)
                return this->myHashTable[index]->info.second;
            index = (index+1)%(this->maxSize);
        }
        //if the loop ended without returning the value associated with the key, the pair <key,value> doesn't
        //exist
        throw std::invalid_argument("GET ERROR! NO SUCH A KEY!");
    }

    //The same logic applied to the "get", but returning a boolean instead
    bool contains(keyType key)
    {
        int index = hashFunction(key, this->maxSize);
        while (this->myHashTable[index]->status != EMPTY && this->myHashTable[index]->status!= DELETED)
        {
            this->counter++;
            if (this->myHashTable[index]->status == ACTIVE && this->myHashTable[index]->info.first == key)
                return true;
            index = (index+1)%(this->maxSize);
        }
        return false;
    }

    int size()
    {
        return this->amountElements;
    }

    void clear()
    {
        for (int i = 0; i < this->maxSize; i++)
        {
            delete this->myHashTable[i];
        }
        this->amountElements = 0;
        this->amountElementsDeleted = 0;
        this->counter = 0;
    }
    
    /*The two methods bellow attend the same purpose: Making the inOrder traversal of an AVL tree,
	the only difference between one and the other is that the one that "Uni" by suffix is deals
	with unicode keys, while the last with all the other types defined in the std*/
    void inOrderUni()
    {
        if (this->amountElements <= 0)
            throw invalid_argument("Error! Can not display elements with empty hash table!");
        list<pair<icu::UnicodeString,valueType>> pairs;
        for (int i = 0; i < this->maxSize; i++)
        {
            if (this->myHashTable[i]->status == ACTIVE)
            {
                pairs.push_back(this->myHashTable[i]->info);
            }
        }
        pairs.sort(isLessUni);
        
        auto itPair = pairs.begin();
        while (itPair != pairs.end())
        {
            string convertedKey;
            itPair->first.toUTF8String(convertedKey);
            cout << convertedKey << ":" << itPair->second << endl;
            itPair ++;
        }
    }
    void inOrder()
    {
        if (this->amountElements <= 0)
            throw invalid_argument("Error! Can not display elements with empty hash table!");
        list<pair<keyType,valueType>> pairs;
        for (int i = 0; i < this->maxSize; i++)
        {
            if (this->myHashTable[i]->status == ACTIVE)
            {
                pairs.push_back(this->myHashTable[i]->info);
            }
        }
        pairs.sort(isLess);
        
        auto itPair = pairs.begin();
        while (itPair != pairs.end())
        {
            cout << itPair->first << ":" << itPair->second << endl;
            itPair ++;
        }
    }
private:
    /*
    A função hash recebe a chave que se deseja obter seu código
    e o tamanho máximo da tabela hash. É necessário fornecer o 
    tamanho máximo, pois, quando as operações de "resizing" forem
    feitas, todos os códigos hash da lista necessitarão ser recal-
    culados, pois um dos operados para da "função de comprensão"
    acaba de mudar - no caso, o tamanho máximo da tabela hash. 
    */
    int hashFunction(keyType key, int maxSize)
    {
        hashAll myHash;
        return myHash(key)%maxSize;
    }

    void allocateMore()
    {
        //the new size will be twice the maximum size of the current maximum size
        int newMaxSize = this->maxSize*2;
        Cell<keyType,valueType>** newHashTable = new Cell<keyType,valueType>*[newMaxSize];
        for (int i=0;i < newMaxSize; i++)
        {
            newHashTable[i]= new Cell<keyType,valueType>();
        }

        //It it needed to move all the pairs that are active to the new hash table
        for (int i=0; i< this->maxSize; i++)
        {
            if (this->myHashTable[i]->status ==ACTIVE)
                _add(newHashTable, newMaxSize, this->myHashTable[i]->info.first, this->myHashTable[i]->info.second);
        }
        //Once the elements were moved, it is needed to clear up the memory by deleting
        //all the pairs of the old hash table and deleting the hash table itself.
        for (int i=0; i <maxSize;i++)
        {
            delete this->myHashTable[i];
        }
        delete[] this->myHashTable;

        this->myHashTable = newHashTable;
        maxSize= newMaxSize;
    }

    void _add(Cell<keyType, valueType>** newHashTable, int newMaxSize, keyType key, valueType value)
    {
        int index = hashFunction(key, newMaxSize);
        //The same logic applied on the public "add" method
        while (newHashTable[index]->status != EMPTY && newHashTable[index]->status != DELETED)
        {
            this->counter++;
            index = (index+1)%newMaxSize;
        }
        newHashTable[index]->info = std::make_pair(key, value);
        newHashTable[index]->status = ACTIVE;
    }

    void allocateLess()
    {
        int newMaxSize = maxSize-amountElementsDeleted;
        /*
        We need to make sure that the newSize is a positive integer,
        otherwise we would get a segmentation fault. If this condition is true,
        than we can keep up with the current size and just delete the elements
        that are marked with the flag "DELETED".
        */
        if (newMaxSize<= 0)
        {
            newMaxSize =maxSize;
        }
        Cell<keyType, valueType>** newHashTable = new Cell<keyType, valueType>*[newMaxSize];
        for (int i=0; i < newMaxSize; i++)
        {
            newHashTable[i] = new Cell<keyType, valueType>();
        }
        //move the elements that are active in the old hash table to the new hash table
        for (int i=0; i <maxSize; i++)
        {
            if (myHashTable[i]->status == ACTIVE)
                _add(newHashTable, newMaxSize, myHashTable[i]->info.first, myHashTable[i]->info.second);
        }

        for (int i=0; i < maxSize; i++)
        {
            delete myHashTable[i];
        }
        delete[] myHashTable;

        myHashTable = newHashTable;
        maxSize = newMaxSize;
        amountElementsDeleted = 0;
    }

    //auxiliary method for the "inOrder"
    static bool isLess(const pair<keyType, valueType>& firstPair, const pair<keyType, valueType>& secondPair)
    {
        return firstPair.first < secondPair.first;
    }
    //The method needs to be a static type to be passed as parameter of a function
    static bool isLessUni(const pair<icu::UnicodeString, valueType>& firstPair, const pair<icu::UnicodeString, valueType>& secondPair)
    {
        return firstPair.first.compare(secondPair.first) < 0;
    }
};

#endif