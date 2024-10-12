#ifndef AVL_H
#define AVL_H

#include <unicode/unistr.h>
#include <string>
#include <type_traits>
#include <algorithm>
#include <stdexcept>
#include <iostream>

template <typename keyType, typename valueType>
class NodeAVLtree
{
public:
	keyType key;
	valueType value;
	int height;
	NodeAVLtree* left;
	NodeAVLtree* right;
	NodeAVLtree(keyType key, valueType value)
	{
		this->key = key;
		this->value = value;
		this->height = 1;
		this->left = nullptr;
		this->right = nullptr;
	}

	valueType getValue()
	{
		return this->value;
	}
	keyType getKey()
	{
		return this->key;
	}
	void setKey(keyType key)
	{
		this->key = key;
	}
	void setValue(valueType value)
	{
		this->value = value;
	}

};

template <typename keyType, typename valueType>
class AVLtree
{
public:
	NodeAVLtree<keyType,valueType>* root;
	int counter;
public:
	AVLtree()
	{
		this->root = nullptr;
		this->counter = 0;
	}
	~AVLtree()
	{
		clear();
	}
	bool contains(keyType key)
	{
		return _contains(key, this->root);
	}
	void clear()
	{
		_clear(this->root);
		root = nullptr;
	}
	int size()
	{
		return _size(root);
	}
	valueType get(keyType key)
	{
		return _get(root, key);
	}
	
	void remove(keyType key)
	{
		if (this->root == nullptr)
			throw std::invalid_argument("ERROR! Can't delete from empty dictionary!");
		this->root = _remove(this->root, key);	
	}

	void modify(keyType key, valueType newValue)
	{
		_modify(this->root,key,newValue);
	}

	void add(keyType key, valueType value)
	{
		this->root = _add(this->root, key, value);
	}
	int getCounter()
	{
		return this->counter;
	}

	//Overloaded method for printing the inOrder of UnicodeStrings
	//defined by ICU
	void inOrderUni()
	{
		_inOrderUni(this->root);
	}
	//All types contained in the std
	void inOrder()
	{
		_inOrder(this->root);
	}

private:

	void _clear(NodeAVLtree<keyType,valueType>*& root)
	{
        if (root == nullptr)
            return;
        _clear(root->left);
        _clear(root->right);
        delete root;
	}
	void _modify(NodeAVLtree<keyType,valueType>*& root, keyType key, valueType newValue)
	{
		this->counter++;
		if (root == nullptr)
			throw std::invalid_argument("ERROR! Key not found!");
		else if (root->key == key)
		{
			root->value = newValue;
		}
		else if (key > root->key)
		{
			_modify(root->right, key, newValue);
		}
		else if (key < root->key)
		{
			_modify(root->left, key, newValue);
		}
	}
	valueType _get(NodeAVLtree<keyType,valueType>*root, keyType key)
	{	
		this->counter ++;
		if (root == nullptr)
			throw std::invalid_argument("ERROR! Key not found!");
		else if (root->key == key)
		{
			return root->value;
		}
		else if (key > root->key)
		{
			return _get(root->right, key);
		}
		return _get(root->left, key);
	}
	bool _contains(keyType key, NodeAVLtree<keyType,valueType>* root)
	{
		this->counter ++;
		if (root == nullptr)
			return false;
		else if (root->key == key)
		{
			return true;
		}
		else if (key > root->key)
		{
			return _contains(key, root->right);
		}
		else
			return _contains(key, root->left);
	}
    int _size(NodeAVLtree<keyType,valueType>* root)
    {
		if (root == nullptr)
			return 0;
        return 1 + _size(root->left) + _size(root->right);
    }
	NodeAVLtree<keyType, valueType>* _add(NodeAVLtree<keyType,valueType>* root, keyType key, valueType value)
	{
		this->counter++;
		if (root == nullptr)
			return new NodeAVLtree(key, value);
		else if (key > root->key)
		{
			root->right = _add(root->right, key, value);
		}
		else if (key < root->key)
		{
			root->left = _add(root->left, key, value);
		}
		_setHeight(root);
		if (_balacingFactor(root) > 1 && _balacingFactor(root->left) < 0)
			_leftRightRotation(root);
		else if (_balacingFactor(root) > 1 && _balacingFactor(root->left) > 0)
			_rightRotation(root);
		else if (_balacingFactor(root) < -1 && _balacingFactor(root->right) > 0)
			_rightLeftRotation(root);
		else if (_balacingFactor(root) < -1 && _balacingFactor(root->right) < 0)
			_leftRotation(root);
		return root;
	}
	/*
	This method is used to recalculate the height of each node ot the AVL tree
	in the subtree the insertion or the deletion took place. The height needs
	to be updated in order to obtain the right balance factor. Since it is 
	needed to update an information that is already "consolidated" inseided
	the AVL tree, a reference to a point need to be passed.
	*/
	void _setHeight(NodeAVLtree<keyType,valueType>*& node)
	{
		if (node == nullptr)
			return;
		else
		{
			int rightHeight = _getHeight(node->right);
			int leftHeight = _getHeight(node->left);
			int maxHeight = std::max(rightHeight, leftHeight);
			int newHeight = 1 + maxHeight;
			node->height =  newHeight;
		}
			  
	}
	int _getHeight(NodeAVLtree<keyType, valueType>* node)
	{
		if (node == nullptr)
			return 0; 
		return node->height;
	}
	int _balacingFactor(NodeAVLtree<keyType, valueType>* node)
	{
		return _getHeight(node->left) - _getHeight(node->right);
	}
	void _rightRotation(NodeAVLtree<keyType, valueType>* &root)
	{
		NodeAVLtree<keyType, valueType>* temp = root->left;
		root->left = root->left->right;
		temp->right = root;
		_setHeight(root);
		_setHeight(temp);
		root = temp;
	}
	void _leftRotation(NodeAVLtree<keyType, valueType>* &root)
	{
		NodeAVLtree<keyType, valueType>* temp = root->right;
		root->right = root->right->left;
		temp->left = root;
		_setHeight(root);
		_setHeight(temp);
		root = temp;
	}
	/*
	Since leftRightRotation is  defined by the usage of the
	already defined "_rightRotation" and "_leftRotation", they are
	used internally in it. The same applies to the "rightLeftRota-"
	tion, 
	*/
	void _rightLeftRotation(NodeAVLtree<keyType, valueType>* &root)
	{
		NodeAVLtree<keyType, valueType>* rightChild = root->right;
		_rightRotation(rightChild);
		/*Once the rightChild was changed during the call of "_right
		rotations", it is needed to update it.*/
		root->right = rightChild;
		_leftRotation(root);
	}
	void _leftRightRotation(NodeAVLtree<keyType, valueType>* &root)
	{
		NodeAVLtree<keyType, valueType>* leftChild = root->left;
		_leftRotation(leftChild);
		/*
		The same logic applied for the the comment of the "_rightLeftRotation"
		applies for explaining this atribution. 
		*/
		root->left = leftChild;
		_rightRotation(root);
	}
	/*
	The deletion happens just like the regular BST, just with the difference that, after the removal,
	the structure of the AVL tree will be checked for imbalances
	*/
	NodeAVLtree<keyType,valueType>* _remove(NodeAVLtree<keyType,valueType>* root, keyType target)
	{
		if (root == nullptr)
			return root;
		else if (target == root->key)
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
				NodeAVLtree<keyType,valueType>* rightChild = root->right;
				delete root;
				return rightChild;
			}
			else if (root->right == nullptr)
			{
				NodeAVLtree<keyType,valueType>* leftChild = root->left;
				delete root;
				return leftChild;
			}
			//3° case: 2 children
			else if (root->left != nullptr && root->right != nullptr)
			{
				NodeAVLtree<keyType,valueType>* sucessor = minimumReference(root->right);
				root->key = sucessor->key;
				root->value = sucessor->value;
				root->right = _remove(root->right, sucessor->key);
				return root;
			}
		}
		/*
		If the key wasn't found, keep loking for it recursivelu
		*/
		else if (target > root->key)
			root->right = _remove(root->right, target);
		else if (target < root->key)
			root->left = _remove(root->left, target);
		
		//this comparation severs to prevent segmentation fails from hapenning
		if (root != nullptr)
		{
			//recalculate the heights
			_setHeight(root);
			if (_balacingFactor(root) > 1 && _balacingFactor(root->left) >= 0)
				_rightRotation(root);
			else if (_balacingFactor(root) >1 && _balacingFactor(root->left) < 0)
				_leftRightRotation(root);
			else if (_balacingFactor(root) < -1 && _balacingFactor(root->right) <= 0)
				_leftRotation(root);
			else if (_balacingFactor(root) < -1 && _balacingFactor(root->right) > 0)
				_rightLeftRotation(root);
		}
		return root;
	}
	NodeAVLtree<keyType, valueType>*& minimumReference(NodeAVLtree<keyType,valueType>*& node)
	{
		if (node == nullptr || node->left == nullptr)
		{
			return node;
		}
		return minimumReference(node->left);
	}

	/*The two methods bellow attend the same purpose: Making the inOrder traversal of an AVL tree,
	the only difference between one and the other is that the one that "Uni" by suffix is deals
	with unicode keys, while the last with all the other types defined in the std*/
	void _inOrderUni(NodeAVLtree<icu::UnicodeString, valueType>* node)
	{
		if (node != nullptr)
		{
			_inOrderUni(node->left);

			/*converts the uniCode "node->key"*/
			std::string convertedKey;
			node->key.toUTF8String(convertedKey);
			std::cout << convertedKey << ":" << node->value << std::endl;

			_inOrderUni(node->right);
		}
	}
	void _inOrder(NodeAVLtree<keyType, valueType>* node)
	{
		if (node != nullptr)
		{
			_inOrder(node->left);

			/*converts the uniCode"node->key"*/
			std::cout << node->key << ":" << node->value << std::endl;

			_inOrder(node->right);
		}
	}
};
#endif
