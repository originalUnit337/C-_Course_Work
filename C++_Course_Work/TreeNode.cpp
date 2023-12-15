#include "TreeNode.h"

TreeNodeUser::TreeNodeUser(User* data)
{
	this->data = data;
	left = nullptr;
	right = nullptr;
}

TreeNodeOrder::TreeNodeOrder(Order* data)
{
	this->data = data;
	left = nullptr;
	right = nullptr;
}
