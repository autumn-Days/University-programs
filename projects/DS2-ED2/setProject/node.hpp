#ifndef NODE_HPP
#define NODE_HPP

template <typename myType>

class Node
{
public:
	myType info;
	int height;
	Node* left;
	Node* right;

	Node(myType info)
	{
		this->info = info;
		height = 1;
		left = nullptr;
		right = nullptr;
	}
};
#endif
