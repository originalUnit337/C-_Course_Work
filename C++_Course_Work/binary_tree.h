#pragma once
#include "order.h"
//#include <iostream>
#include <fstream>
#include <string>

struct Node
{
	Order data;
	Node* left;
	Node* right;
};

Node* CreateNode(const Order& order);
Node* InsertNode(Node* root, Order& order);
void PrintOrdersByAcceptanceDate(Node* root);
void PrintRepairingOrders(Node* root);
void SearchOrdersByProductName(Node* root, const std::string& _product_name);
void SaveOrdersToFile(Node* root, const std::string& filename);
Node* LoadOrdersFromFile(const std::string& filename);