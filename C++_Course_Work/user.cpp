//#include "user.h"
//#include "order.h"
#include "binary_tree.h"


User::User(const string& name, const string& password, bool isAdmin)
	: name(name), password(password), isAdmin(isAdmin)
{

};

User::User() = default;

//void Admin::AddNewOrder(BinaryTreeOrder* tree)
//{
//	Order* order = new Order();
//	std::cout << "¬ведите данные" << std::endl;
//	cin >> *order;
//	//BinaryTreeOrder* tree = new BinaryTreeOrder();
//	//tree->LoadOrdersFromFile("../data/orders.bin");
//	tree->Insert(order);
//	tree->PrintOrders();
//}

void Admin::AddNewOrder(BinaryTreeOrder* tree)
{
	Order* order = new Order();
	std::cout << "¬ведите данные" << std::endl;
	cin >> *order;
	//BinaryTreeOrder* tree = new BinaryTreeOrder();
	//tree->LoadOrdersFromFile("../data/orders.bin");
	tree->Insert(order);
	tree->PrintOrders();
}
