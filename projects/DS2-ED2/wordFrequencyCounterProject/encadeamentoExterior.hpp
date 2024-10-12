#ifndef HASH_TABLE_ENCADEAMENTO_EXTERIOR
#define HASH_TABLE_ENCADEAMENTO_EXTERIOR

#include <unicode/unistr.h>
#include <utility>
#include <stdexcept>
#include <functional>
#include <cmath>

using namespace std;

template <typename keyType, typename valueType>
class NodeLinked
{
public:
    std::pair<keyType,valueType>info;
    NodeLinked<keyType,valueType>* next;

    NodeLinked(keyType key, valueType value)
    {
        this->info = std::make_pair(key,value);
        this->next = nullptr;
    }
};

/*
Em relação ao contador da tabela hash com encadeamento
exterior, será necessário que, após cada inserção
inserção, o contador seja resetado, pois, caso um novo
elemento seja inserido novamente na mesma lista encadea-
da, o seu contador não respeito a aquela única inserção
mas esta a aquela mais todas as outras inserções que hou-
veram. O reset é feito na classe "hashEncadeamentoExt"
*/
template <typename keyType, typename valueType>
class linkedList
{
public :
    NodeLinked<keyType,valueType>* head;
    int counterList;

    linkedList()
    {
        this->head = nullptr;
        this->counterList = 0;
    }

    ~linkedList()
    {
        while (this->head != nullptr)
        {
            NodeLinked<keyType,valueType>* temp = this->head;
            this->head = this->head->next;
            delete temp;
        }
        this->head == nullptr;
    }

    void addLinked(keyType key, valueType value)
    {
        NodeLinked<keyType,valueType>* newNode = new NodeLinked<keyType,valueType>(key,value);
        if (this->head == nullptr)
        {
            this->head = newNode;
        }
        else
        {
            /*This node will traverse the linked list in order to insert the element
            Everytime it gives "a step" it increments its counter*/
            NodeLinked<keyType,valueType>* runnerNode = this->head;
            while (runnerNode->next != nullptr && runnerNode->info.first != key)
            {
                runnerNode = runnerNode->next;
                this->counterList++;
            }
            runnerNode->next = newNode;
        }
    }

    bool removeLinked(keyType key)
    {
        //If head is empty, then the linked list is also empty and there is no way the removal
        //to be done
        if (this->head == nullptr)
        {
            return false;
        }
        /*If the node to be removed is the head, them it is just a matter
        of it point to the next element and deleting it by saving it on a temporary
        Node before moving on to the next*/
        else if (this->head->info.first == key)
        {
            NodeLinked<keyType,valueType>* temp = this->head;
            this->head = temp->next;
            delete temp;
            return true;
        }
        //The node to be removed is looked for
        NodeLinked<keyType,valueType>* runnerNode = this->head;
        while (runnerNode->next != nullptr && runnerNode->next->info.first != key)
        {
            runnerNode = runnerNode->next;
        }
        //In the case the runner->next is ends up being a
        //nullptr, this means the element doesn't exist
        if (runnerNode->next == nullptr)
            return false;
        //Otherwise, it is deleted
        else
        {
            NodeLinked<keyType,valueType>* temp = runnerNode->next;
            runnerNode->next = temp->next;
            delete temp;
            return true;
        }
    }


    void displayLinked()
    {
        NodeLinked<keyType,valueType>* runnerNode = this->head;
        while (runnerNode != nullptr)
        {
            std::cout << runnerNode->info.first << ":" << runnerNode->info.second << std::endl;
            runnerNode = runnerNode->next;
        }
    }

    int getCounterList()
    {
        return this->counterList;
    }
};

/*
Since it will be needed to hash "UnicodeString's" and the standard std::hash
doesn't provide any functionalities for performing such a thing, it is needed
to implement a special hash function only for this case. It will work by 
defining a structure and overloading the "()" operator, so that the structure
can be used as a function. A lighweight and good hash function is the DJB2.
*/
struct hashUnicodeString
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
class hashEncadeamentoExt
{
public:
    linkedList<keyType,valueType>** extHashTable;
    size_t maxSize;
    size_t amountElements;
    float loudFactorMaximum;
    float loudFactorCurrent;
    int counter;
public:
    hashEncadeamentoExt(int maxSize=19)
    {
        this->maxSize = getNextPrime(maxSize);
        this->amountElements = 0;
        this->counter = 0;
        this->extHashTable = new linkedList<keyType,valueType>*[maxSize];
        this->loudFactorCurrent = 0.75;
        this->loudFactorMaximum = 1.0;
        for (int i = 0; i < this->maxSize; i++)
        {
            this->extHashTable[i] = new linkedList<keyType,valueType>();
        }
    }

    size_t getNextPrime(size_t previousPrime)
    {
        size_t nextPrime = previousPrime;
        if (nextPrime<=2)
            return 3;
        nextPrime = (nextPrime%2 == 0)? nextPrime+1 : nextPrime;
        bool notPrime = true;
        while (notPrime)
        {
            notPrime = false;
            for (int i = 2;i <= sqrt(nextPrime); ++i)
            {
                if (nextPrime%i == 0)
                {
                    notPrime = true;
                    break;
                }
            }
            nextPrime +=2;
        }
        return nextPrime - 2;
    }
    
    int size()
    {
        return this->amountElements;
    }

    int getCounter()
    {
        return this->counter;
    }
    int hashFunctionExt(keyType key, size_t size)
    {
        hashAll myHash;
        return myHash(key)%size;
    }

    bool add(keyType key, valueType value)
    {
        if ( (static_cast<float>(this->amountElements)/static_cast<float>(this->maxSize)) > this->loudFactorCurrent)
            allocateMore(2*this->maxSize);
        int index = hashFunctionExt(key, this->maxSize);

        this->extHashTable[index]->addLinked(key,value);
        this->amountElements ++;
        /*update the value of the counter of the hash table
        and reset the counter of the linked list*/
        linkedList<keyType,valueType>*& copy = extHashTable[index];
        this->counter += extHashTable[index]->counterList;
        extHashTable[index]->counterList = 0;
        return true;
    }


    void allocateMore(size_t newSize)
    {
        if (newSize > this->maxSize)
        {
            //It gets new prime number that will be used for setting the
            //table size
            size_t newSize = getNextPrime(this->maxSize);
            linkedList<keyType, valueType>** newHashTable = new linkedList<keyType,valueType>*[newSize];
            //aloca mais memória
            for (size_t i = 0; i < newSize; i++)
            {
                newHashTable[i] = new linkedList<keyType,valueType>();
            }
            //move todos os pares para suas novas posições na memória
            for (size_t i = 0; i < this->maxSize; i++)
            {
                NodeLinked<keyType,valueType>* runnerNode = this->extHashTable[i]->head;
                while (runnerNode != nullptr)
                {
                    size_t index = hashFunctionExt(runnerNode->info.first, newSize);
                    newHashTable[index]->addLinked(runnerNode->info.first,runnerNode->info.second);
                    /*the counter of the linked list keeps incrementing everytime the adition is done
                    so it needs to be reseted after every*/
                    newHashTable[index]->counterList = 0; 
                    runnerNode = runnerNode->next;
                }
            }
            //libera a memória
            for (size_t i =0; i < this->maxSize; i++)
            {
                this->extHashTable[i]->counterList = 0;
                delete this->extHashTable[i];
            }

            //atualiza a tabela hash
            delete this->extHashTable;
            this->extHashTable = newHashTable;
            this->maxSize = newSize;
        }
    }

    
    valueType get(keyType key)
    {
        if (this->amountElements <= 0)
            throw std::invalid_argument("Get error! Can not get from an empty hash table");
        int index = hashFunctionExt(key, this->maxSize);
        
        /*The runner Node will "run" through the linked list of the i-th slot and then
         will update will get the value of the key in question if it exists, otherwise,
         will throw an error. The same ideia is applied to the "contains" and the "modify"*/
        NodeLinked<keyType,valueType>* runnerNode = this->extHashTable[index]->head;

        while (runnerNode != nullptr && runnerNode->info.first != key)
        {
            runnerNode = runnerNode->next;
            this->counter++;
        }
        if (runnerNode != nullptr)
            return runnerNode->info.second;
        else
            throw std::invalid_argument("Get error! No such a key");
    }

    bool contains(keyType key)
    {
        int index = hashFunctionExt(key, this->maxSize);
        NodeLinked<keyType,valueType>* runnerNode = this->extHashTable[index]->head;

        while (runnerNode != nullptr && runnerNode->info.first != key)
        {
            runnerNode = runnerNode->next;
            this->counter++;
        }
        if (runnerNode == nullptr)
            return false;
        return true;
    }

    bool modify(keyType key, valueType newValue)
    {
        if (this->amountElements <= 0)
            throw std::invalid_argument("Error! Can not modify from empty hash!");
        int index = hashFunctionExt(key, this->maxSize);

        NodeLinked<keyType,valueType>* runnerNode  = this->extHashTable[index]->head;

        while (runnerNode != nullptr && runnerNode->info.first != key)
        {
            runnerNode = runnerNode->next;
            this->counter++;
        }
        if (runnerNode == nullptr)
            return false;
        else
        {
            runnerNode->info.second = newValue;
            return true;
        }
    }

    /*
    This method uses by interface the remove method of the linked list. This increases
    the legibility.
    */
    void remove(keyType key)
    {
        if (this->amountElements <= 0)
            throw std::invalid_argument("Error!Can not remove from empty hash table!");
        int index = hashFunctionExt(key, this->maxSize);
        try 
        {
            this->extHashTable[index]->removeLinked(key);
            this->amountElements --;
        }
        catch (const std::invalid_argument&)
        {
            throw std::invalid_argument("REMOVE ERROR! No such a key!");
        }
    }

    /*
    similarly, the clear method also makes usage of the remove of the liked list
    */
    void clear()
    {
        if (this->amountElements <= 0)
            throw std::invalid_argument("Error! The hash table is already empty!");
        for (int i = 0; i < this->maxSize; i++)
        {
            while(this->extHashTable[i]->head != nullptr)
            {
                this->extHashTable[i]->removeLinked(this->extHashTable[i]->head->info.first);
            }
        }
        this->amountElements = 0;
    }

    ~hashEncadeamentoExt()
    {
        for (int i = 0; i < this->maxSize; i++)
        {
            delete this->extHashTable[i];
        }
        delete[] this->extHashTable;
    }

    //prints the sorted content of the hash table with unicode strings
    void inOrderUni()
    {
        if (this->amountElements <= 0)
            throw invalid_argument("Error! Cannot display elements of an empty hash table!");

        list<pair<icu::UnicodeString, valueType>> pairs;

        for (int i = 0; i < this->maxSize; i++)
        {
            NodeLinked<icu::UnicodeString, valueType>* runnerNode = this->extHashTable[i]->head;
            while (runnerNode != nullptr)
            {
                pairs.push_back(runnerNode->info);
                runnerNode = runnerNode->next;
            }
        }

        // calls the isLessUniMethod
        pairs.sort(isLessUni);

        // Iterate over the sorted pairs and print them
        for (auto itPair = pairs.begin(); itPair != pairs.end(); itPair++)
        {
            std::string convertedKey;
            itPair->first.toUTF8String(convertedKey);
            std::cout << convertedKey << ":" << itPair->second << std::endl;
        }
    }
    //prints the sorted content of the hash table with std types.
    void inOrder()
    {
        if (this->amountElements <= 0)
            throw invalid_argument("Error! Cannot display elements of an empty hash table!");

        list<pair<keyType, valueType>> pairs;

        for (int i = 0; i < this->maxSize; i++)
        {
            NodeLinked<keyType, valueType>* runnerNode = this->extHashTable[i]->head;
            while (runnerNode != nullptr)
            {
                pairs.push_back(runnerNode->info);
                runnerNode = runnerNode->next;
            }
        }

        // calls the isLessUniMethod
        pairs.sort(isLess);

        // Iterate over the sorted pairs and print them
        for (auto itPair = pairs.begin(); itPair != pairs.end(); itPair++)
        {
            std::cout << itPair->first << ":" << itPair->second << std::endl;
        }
    }

private:

    /*
    Those functions are auxiliary for the process of displaying the pairs contained
    in the dicionaries implemented with hash tables. The basic idea is that each pair
    will be saved into a std::list and them they will be sorted by using the sort()
    method defined in the std::list. Since by default the sort() only sorts primi-
    time times, it is needed to create static methods that will handle the comparation,
    because, it is possible to pass such methods as parameter for the sort() and
    defines how it shall sort the elements inside the list.

    The first "isLess" is used for standard types and the second for keys that have
    by type "UnicodeString", for those, there is no way to compare keys natively with
    the "<" operator, so it is necessary to use the methods "compare" defined by ICU,
    if it returns a negative value, this means the key of the first pair is less than
    the key of the second pair.
    */
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