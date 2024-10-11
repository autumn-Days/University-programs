#ifndef SET_HPP
#define SET_HPP

#include "node.hpp"

#include <iostream> //tira isso mais tarde
#include <algorithm>
#include <stdexcept>

template <typename myType>

class Set
{
public:
	Node<myType>* root;
	//creates an empty set
	Set()
	{
		root = nullptr;
	}
	~Set()
	{
		clear();
	}
	//it says if a value is contained in the set
	bool contains(myType info)
	{
		return _contains(info, root);
	}
	//it deletes all the elements of the SET
	void clear()
	{
		_clear(root);
        root = nullptr;
        /*If I do not set nullptr to root, it would
        still point to that very memory cell which was
        freed. This causes security*/ 
	}
	myType minimum()
	{
		return _minimum(root);
	}
	myType maximum()
	{
		return _maximum(root);
	}
	bool empty()
	{
		return _empty(root);
	}
	int size()
	{
		return _size(root);
	}
	myType sucessor(myType predecessorOfSuccessor)
	{
		if (root == nullptr)
			throw std::invalid_argument("O set está vazio!");
		else if (!contains(predecessorOfSuccessor))
			throw std::invalid_argument("O elemento que você inseriu não está no conjunto!");
		Node<myType>* tempSuccessor = nullptr;  // Create a temporary pointer
		tempSuccessor = _sucessor(root, predecessorOfSuccessor, tempSuccessor);
		if (tempSuccessor == nullptr)
			throw std::invalid_argument("Não existe sucessor para este número!");
		return tempSuccessor->info;
	}

	myType predecessor(myType successorOfPredecessor)
	{
		if (root == nullptr)
			throw std::invalid_argument ("O set está vazio");
		else if (!contains(successorOfPredecessor))
			throw std::invalid_argument("O elemento que você inseriu não está no conjunto!");

		Node<myType>* currentPredecessor = nullptr;
		currentPredecessor = _predecessor(root,successorOfPredecessor, currentPredecessor);
		if (currentPredecessor == nullptr)
			throw std::invalid_argument("Não existe predecessor para este número!");
		return currentPredecessor->info;
	}
	void swap(Set<myType>*&otherSet)
	{
		_swap(otherSet);
	}
	void insert(myType info)
	{
		bool isFirstRecursiveCall = true;
		root = _insert(root, info, isFirstRecursiveCall);
	}
	/*
	Usage:
		Set<int> A;
		Set<int> B;
		Set<int> mySet = new Set<int>();

		mySet->intersection(A,B);
	*/

	void intersection(Set<myType>* A, Set<myType>*B)
	{
		/*This is the case of the type C->intersection(A/B, B/A)
		In this case, I just need to insert All the values that belong
		to A/B and B/A into C*/
		if (this->root != A->root && B->root != this->root)
		{
			if (!empty())
				clear();
			_intersection(A->root, B);
		}
		/*This is the case of the type C->intersection(C/set, set/C)
		In this case, I just need to delete all the elements of C that
		doesn't belong to "set"*/
		else if (this->root == A->root || this->root == B->root)
		{
			Set<myType>* tempSet = new Set<myType>();
			if ((A->root == this->root) && (B->root != this->root))
				_intersectionSecondType(A->root, B, tempSet);
			else if ((B->root == this->root) && (A->root != this->root))
				_intersectionSecondType(B->root,A,tempSet);
			//the case where someone do set->intersection(set,set)
			else
				return;
			this->clear();
			this->root = tempSet->root;
		}
	}

	void difference(Set<myType>* A, Set<myType>*B)
	{	
		//set1 - set2
		if (this->root != A->root && B->root != this->root)
		{
			if (!empty())
				clear();
			_difference(A->root, B);
		}
		//C-C
		else if (A->root == this->root && B->root == this->root)
			clear();
		else
		{
			Set<myType>* tempSet = new Set<myType>();
			_differenceSecondType(A->root, B, tempSet);
			this->clear();
			this->root = tempSet->root;
		}
	}
	//A "union" keyword already existed in C++
	void union2 (Set<myType>* A, Set<myType>* B)
	{
		if (A->root != this->root && B->root != this->root)
		{
			if (!empty())
				clear();
			_union(A->root, B->root);
		}
		else
			_union(A->root, B->root);
	}

	void inserter(Set<myType>* mySet)
	{
		_inserter(mySet->root);
	}

	void erase(myType target)
	{
		if (root == nullptr)
			throw std::invalid_argument("O conjunto está vazio!");
		root = _erase(root, target);
	}

	void update(myType oldValue, myType newValue)
	{
		_erase(this->root, oldValue);
		bool isFirstRecursiveCall = true;
		_insert(this->root, newValue, isFirstRecursiveCall);
	}
//those are the methods that serve as wrapper
private:
	bool _contains(myType info, Node<myType>* root)
	{
        if (root == nullptr)
            return false;
		else if (root->info == info)
			return true;
		else if (info > root->info)
			return _contains(info, root->right);
		else
			return _contains(info, root->left);
	}
	//delete all the data
	void _clear(Node<myType>* root)
	{
        if (root == nullptr)
            return;
        _clear(root->left);
        _clear(root->right);
        delete root;
	}
	myType _minimum(Node<myType>* root)
	{
		if (root == nullptr)
			throw std::invalid_argument("O conjunto está vazio!");
		return (minimumReference(root))->info;
	}

	myType _maximum(Node<myType>* root)
	{
		if (root == nullptr)
			throw std::invalid_argument("O conjunto está vazio!");
		return (maximumReference(root))->info;
	}

	bool _empty(Node<myType>* root)
	{
		return (root == nullptr);
	}
	int _size(Node<myType>* root)
	{
		if (root == nullptr)
			return 0;
		return 1 + _size(root->left) + _size(root->right);
	}
	/*
	Possíveis casos:
		-O elemento que o usuário quer não está contido no SET
		-O elemento que o usuário quer está contido no SET
			-O sucessor do elemento não está no SET
			-O sucessor do elemento está no SET
	*/
	Node<myType>*& _sucessor(Node<myType>* root, myType predecessorOfSuccessor, Node<myType>*& currentSuccessor)
	{
		if (root == nullptr)
			return currentSuccessor;
		else
		{
			if (predecessorOfSuccessor < root->info)
			{
				currentSuccessor = root;
				return _sucessor(root->left, predecessorOfSuccessor, currentSuccessor);
			}
			else if (predecessorOfSuccessor > root->info)
				return _sucessor(root->right, predecessorOfSuccessor, currentSuccessor);
			//if you finally found the predecessor of the successor, go one time to the right and all the way to the left
			else if (root->right != nullptr)
				currentSuccessor = minimumReference(root->right);
			return currentSuccessor;
		}
	}

	Node<myType>*& _predecessor(Node<myType>* root, myType successorOfPredecessor, Node<myType>*& currentPredecessor)
	{
		if (root == nullptr)
			return currentPredecessor;
		else
		{
			if (successorOfPredecessor > root->info)
			{
				currentPredecessor = root;
				_predecessor(root->right, successorOfPredecessor, currentPredecessor);
			}
			else if (successorOfPredecessor < root->info)
			{//aqui era root->info
				_predecessor(root->left, successorOfPredecessor, currentPredecessor);
			}
			//if you finally found out the successor of the predecessor, this means you must go on time to the left and then all the way to the right
			else if (root->left != nullptr)
				currentPredecessor = maximumReference(root->left);
			return currentPredecessor;
		}
	}
	void _swap(Set<myType>* &otherSet)
	{
		Node<myType>* aux = this->root;
		this->root = otherSet->root;
		otherSet->root = aux;
	}

	/*We first need to add the element to the tree and then check if
	the tree is balanced. If not, we will balance it.
	*/
	Node<myType>* _insert(Node<myType>* root, myType info, bool &isFirstRecursiveCall)
	{
		/*If the value already exist, them is not needed to insert it*/
		if (isFirstRecursiveCall && this->contains(info))
		{
			isFirstRecursiveCall = false;
			return root;
		}
		else
		{
			/*Insertion*/
			if (root == nullptr)
				return new Node<myType>(info);
			else if (info > root->info)
				root->right = _insert(root->right, info, isFirstRecursiveCall);
			else
				root->left = _insert(root->left, info, isFirstRecursiveCall);
			/*Since we just added an element, now we must udpate the heights recursively*/
			setHeight(root);
			/*Checks for balacing*/
			if (balacingFactor(root) > 1 && balacingFactor(root->left) < 0)
				leftRightRotation(root);
			else if (balacingFactor(root) > 1 && balacingFactor(root->left) > 0)
				rightRotation(root);
			else if (balacingFactor(root) < -1 && balacingFactor(root->right) > 0)
				rightLeftRotation(root);
			else if (balacingFactor(root) < -1 && balacingFactor(root->right) < 0)
				leftRotation(root);
			//at the end, the node must return itself
			return root;
		}
	}

	void _intersection(Node<myType>* A, Set<myType>*B)
	{
		if (A == nullptr || B->root == nullptr) 
			return;
		else
		{
			if (B->contains(A->info))
			{
				insert(A->info);
			}
			_intersection(A->left, B);
			_intersection(A->right, B);
		}
	}
	//minuend in this case is this->root and tempSet is gonna be the final result
	void _intersectionSecondType(Node<myType>* minuend, Set<myType>* subtraend, Set<myType>*& tempSet)
	{
		if (minuend == nullptr || subtraend == nullptr)
			return;
		else if (subtraend->contains(minuend->info))
			tempSet->insert(minuend->info);
		_intersectionSecondType(minuend->left, subtraend, tempSet);
		_intersectionSecondType(minuend->right, subtraend, tempSet);
	}

	void _difference(Node<myType>* A, Set<myType>*B)
	{
		if (A == nullptr)
			return;
		else if (B->root == nullptr)
			this->root = A;
		else
		{
			if (!B->contains(A->info))
			{
				insert(A->info);
			}
			_difference(A->left,B);
			_difference(A->right,B);
		}
	}

	/*
		I know it is hard to belive on the first sight, but it is really needed to have 2 distinct
		functions. The first one is regarding the case A/B-C and the second the case C-A/B
	*/

	void _differenceSecondType(Node<myType>* minuend, Set<myType>* subtraend, Set<myType>*& tempSet)
	{
		if (minuend == nullptr)
			return;
		else if (subtraend->root == nullptr)
		{
			tempSet->root = minuend;
			return;
		}
		//the middle case
		else
		{
			if (!subtraend->contains(minuend->info))
				tempSet->insert(minuend->info);
			_differenceSecondType(minuend->left, subtraend, tempSet);
			_differenceSecondType(minuend->right, subtraend, tempSet);
		}
	}

	void _union(Node<myType>*A, Node<myType>* B)
	{
		_inserter(A);
		_inserter(B);
	}

	Node<myType>* _erase(Node<myType>* root, myType target)
	{
		if (root == nullptr)
			return root;
		else if (target == root->info)
		{
			//1° case: leafs
			if (root->left == nullptr && root->right == nullptr)
			{
				delete root;
				return nullptr;
			}
			//2° case: only one child
			else if (root->left == nullptr && root->right != nullptr)
			{
				Node<myType>* rightChild = root->right;
				delete root;
				return rightChild;
			}
			else if (root->right == nullptr) //if your function go wrong, look at this if-statement
			{
				Node<myType>* leftChild = root->left;
				delete root;
				return leftChild;
			}
			//3° case: 2 children
			else if (root->left != nullptr && root->right != nullptr)
			{
				Node<myType>* sucessor = minimumReference(root->right);
				root->info = sucessor->info;
				root->right = _erase(root->right, sucessor->info);
				return root; //comment this if it go wrong
			}
		}
		else if (target > root->info)
			root->right = _erase(root->right, target);
		else if (target < root->info)
			root->left = _erase(root->left, target);

		//I am cheacking for nulity just for precaution
		if (root != nullptr)
		{
			//recalculate the heights
			setHeight(root);

			if (balacingFactor(root) > 1 && balacingFactor(root->left) >= 0)
				rightRotation(root);
			else if (balacingFactor(root) >1 && balacingFactor(root->left) < 0)
				leftRightRotation(root);
			else if (balacingFactor(root) < -1 && balacingFactor(root->right) <= 0)
				leftRotation(root);
			else if (balacingFactor(root) < -1 && balacingFactor(root->right) > 0)
				rightLeftRotation(root);
		}
		return root;
	}

//those are the auxiliary methods for the wrappers
private:
	Node<myType>*& findNodeReference(myType info, Node<myType>* root)
	{
		if (root == nullptr || root->info == info)
			return root;
		else if (info > root->info)
			return findNodeReference(info, root->right);
		else
			return findNodeReference(info, root->left);
	}
	Node<myType>*& minimumReference(Node<myType>*& root)
	{
		if (root == nullptr || root->left == nullptr)
			return root;
		return minimumReference(root->left);
	}
	Node<myType>*& maximumReference(Node<myType>*& root)
	{
		if (root == nullptr || root->right == nullptr)
			return root;
		return maximumReference(root->right);
	}
	int getHeight(Node<myType>* root)
	{
		return (root == nullptr) ? 0 : root->height;
	}

	void setHeight(Node<myType>* &root)
	{
		if (root == nullptr)
			root->height = 0;
		else
			root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
	}

	int balacingFactor(Node<myType>* root)
	{
		return getHeight(root->left) - getHeight(root->right);
	}

	void rightRotation(Node<myType>* &root)
	{
		Node<myType>* temp = root->left;
		root->left = root->left->right;
		temp->right = root;
		//Now we just need to update the heights
		setHeight(root);
		setHeight(temp);
		//It is needed to update the root node
		root = temp;
	}

	void leftRotation(Node<myType>* &root)
	{
		Node<myType>* temp = root->right;
		root->right = root->right->left;
		temp->left = root;
		setHeight(root);
		setHeight(temp);
		root = temp;
	}

	void rightLeftRotation(Node<myType>* &root)
	{
		Node<myType>* rightChild = root->right;
		//the right Child makes a right Rotation
		rightRotation(rightChild);
		/*Since the riht child of the root node was changed
		on the the call of 'rightRotation', now we must update it*/
		root->right = rightChild;
		leftRotation(root);
	}


	void leftRightRotation(Node<myType>* &root)
	{
		Node<myType>* leftChild = root->left;
		//the left child must suffer a left rotation
		leftRotation(leftChild);
		/*Since the left child of the root node was changed,
		it needs to be updated before the final right rotation*/
		root->left = leftChild;
		rightRotation(root);
	}
	void _inserter(Node<myType>* rootMySet)
	{
		if (rootMySet == nullptr)
			return;
		this->insert(rootMySet->info);
		_inserter(rootMySet->left);
		_inserter(rootMySet->right);
	}
};

#endif
/*
1° solução: criar um método auxiliar "findPai"
	-chama findNodeReference
	-verifica se findNodeRefernce é maior que findPai, se for findPai->right == nullptr, se não findPai->left == nullptr
	-free findNodeReference 
*/
