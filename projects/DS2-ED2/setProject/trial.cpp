#include "set.hpp"
#include <iostream>
#include <queue>

using namespace std;

void inOrder(Node<string>* mySet)
{
    if (mySet != nullptr)
    {
        inOrder(mySet->left);
        cout << mySet->info << "|" << endl;
        inOrder(mySet->right);
        
    }
}

/*
void preOrder(Node<string>* mySet)
{
    if (mySet != nullptr)
    {
        cout << mySet->info << "|" << mySet->height << endl;
        inOrder(mySet->left);
        inOrder(mySet->right);
        
    }
}
*/
void BFS(Node<string>* node)
{
    if (node == nullptr)
        return;
    queue<Node<string>*> nodes;
    nodes.push(node);

    while (!nodes.empty())
    {
        Node<string>* myNode = nodes.front();
        nodes.pop();

        cout << myNode-> info << "|" << myNode->height << endl;

        if (myNode->left !=nullptr)
            nodes.push(myNode->left);
        if (myNode->right != nullptr)
            nodes.push(myNode->right);
    }
}

int main()
{
    Set<string>* set1 = new Set<string>();
    Set<string>* set2 = new Set<string>();
    set1->insert("Ane");
    set1->insert("Mary");
    set1->insert("Joseph");

    set2->insert("Emanuel");
    set2->insert("Mary");
    set2->insert("John");
    set1->intersection(set1,set2);
    set1->difference(set1,set2);
    set1->union2(set1,set2);
    BFS(set1->root);
    //BFS(set2->root);
    /*
    mySet->insert("Luis");
    mySet->insert("Mari");
    mySet->insert("Nest");
    mySet->insert("Albe");
    mySet->insert("Bren");
    mySet->insert("Carl");
    mySet->insert("Dian");
    //mySet->insert("Gabriel");
    mySet->insert("Hect");
    mySet->insert("Isab");
    mySet->insert("Elen");
    mySet->insert("Fern");
    mySet->insert("Olga");
    
        //LL
        //mySet->insert("John");
        //mySet->insert("Paul");
        //mySet->insert("Saul");
    //mySet->insert("Mary");
    //mySet->insert("John");
    //mySet->insert("Carl");
    BFS(mySet->root);
    mySet->update("Albe", "Albi");
    cout << "-=-=-=" << endl;
    BFS(mySet->root);
    cout << "-=-=-=" << endl;
    //cout << mySet->root->info << endl;

    mySet->erase("Zumira");
    mySet->erase("Hector");
    mSet->erase("Karla");
    mySet->erase("Fernanda");
    mySet->erase("Nestor");
    //cout << "-=-=-=-=-=-=" << endl;
    BFS(mySet->root);
    */
/*
    cout << mySet->root->height << endl;
    cout << mySet->size() << endl;
    cout << mySet->root->info << endl;
    */
}